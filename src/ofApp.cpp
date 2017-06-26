#include "ofApp.h"
#include "ofxVoid/ui/ui.h"
#include "ofxVoid/ui/Rectangle.h"
//#include "ofxVoid/ui/Circle.h"
#include "ofxVoid/ui/Button.h"
#include "ofxVoid/ui/Slider.h"
//#include "ofxVoid/ui/RangeSlider.h"
#include "ofxVoid/ui/Label.h"
#include "ofxVoid/ui/FpsLabel.h"
#include "ofxVoid/ui/ValueLabel.h"
//#include "ofxVoid/ui/Circle.h"
#include "ofxVoid/ui/Toggle.h"
#include "ofxVoid/ui/Spacer.h"
//#include "ofxVoid/ui/StarDiagram.h"
#include "ofxVoid/ui/ColorPicker.h"

using namespace ofxVoid;

//--------------------------------------------------------------
void ofApp::setup(){
    
    // global variables
    
    numTilesX = 9;
    numTilesY = 7;
    
    pixelPerTile = 16;
	pixelPitch = 10;
    radius = 3;
	
	ofDisableSmoothing();
	ofSetFrameRate(60);
	
    // font loading
    font.load("fonts/hooge06_55.ttf", 6);
	headerFont.load("fonts/header17_68.ttf", 6);
	
	
    // allocate FBOs
	
    screen.allocate(numTilesX * pixelPerTile, numTilesY * pixelPerTile);
    
    screen.begin();
    ofClear(0,0,0,255);
    screen.end();
    
    
    preview.allocate(screen.getWidth() * pixelPitch, screen.getHeight() * pixelPitch);
    
    preview.begin();
    ofClear(0, 0, 0, 255);
    preview.end();
	
	
	
	// setup camera
	cam.setDistance(2000);
	
	
	// setup UI
	
	ui::init(2.0f); // 2.0 if retina display (plist high res YES)
	
	_stage = ui::DisplayObject::create();
	_stage->makeRootObject();
	_stage->disableAutoUpdate();
	_stage->disableAutoDraw();
	
	_panel = ui::Panel::create(ofRectangle(0, 0, 300 * ui::scale, 500 * ui::scale));
	
	_vcell = ui::CellLayout::create(true);
	_hcell = ui::CellLayout::create(false);
	_hcell->addComponent(_panel, ui::ResizeRule(ui::RESIZE_RULE_TYPE_STATIC, 200.0f * ui::scale));
	_hcell->addComponent(_vcell);
	_stage->addChild(_hcell);
	
	
	
	// add UI components
	
	_panel->addComponent(ui::Spacer::create(6));
	
	auto label = ui::Label::create("Nasjonalmuseet 2020");
	_panel->addComponent(label);
	
	auto fps = ui::FpsLabel::create();
	_panel->addComponent(fps);
	
	_panel->addComponent(ui::Spacer::create(1));
	
	_showCursor = true;
	_panel->addComponent(ui::Toggle<bool>::create("Show cursor", &_showCursor));
	
	_panel->addComponent(ui::Spacer::create(1));
	
	_bgcolor = ofFloatColor(.4f, .4f, .4f);
	_panel->addComponent(ui::ColorPicker<ofFloatColor>::create("Background color", &_bgcolor));
	
	_boxcolor.set(.05f, .05f, .05f);
	_panel->addComponent(ui::ColorPicker<ofFloatColor>::create("Box color", &_boxcolor));
	
	_plexiTransparency = 5;
	auto plexiSlider = ui::Slider<float>::create("Plexi transparency", &_plexiTransparency, 0, 255);
	_panel->addComponent(plexiSlider);
	
	_panel->addComponent(ui::Spacer::create(1));
	
	_panel->addComponent(ui::Toggle<bool>::create("Seq 1", &_sequenceOne));
	_panel->addComponent(ui::Toggle<bool>::create("Seq 2", &_sequenceTwo));
	_panel->addComponent(ui::Toggle<bool>::create("Seq 3", &_sequenceThree));
	
	
	
	//
	// FILE SCAN SYSTEM
	//
	
	//scan area directory and fill arrays
	path = "areas";
	
	//scan png images
	imgDir.open(path);
	imgDir.allowExt("png");
	imgDir.listDir();
	
	for(int i = 0; i < imgDir.size(); i++){
		//ofLogNotice(imgDir.getPath(i));
		ofImage img;
		img.load(imgDir.getPath(i));
		areaImages.push_back(img);
		Area area;
		areaImageList.push_back(area);
	}
	
	// scan txt files
	txtDir.open(path);
	txtDir.allowExt("txt");
	txtDir.listDir();
	
	for(int i = 0; i < txtDir.size(); i++){
		ofLogNotice(txtDir.getPath(i));
		ofBuffer buffer = ofBufferFromFile(txtDir.getPath(i));
		string text = buffer.getText();
		areaTextStrings.push_back(text);
		Text title;
		areaTextList.push_back(title);
	}
	
	//calculate text width
	for (int i = 0; i < areaTextList.size(); i++) {
		areaTextList[i].calculate(font, areaTextStrings[i]);
	}

}

//--------------------------------------------------------------
void ofApp::update(){
	
	// update UI elements
	_stage->update(ofGetElapsedTimef(), 0.0f);
	
	
	// control coordinates (switch with Kinect)
	gx = (ofGetMouseX() / ui::scale) - 28;
	gy = (ofGetMouseY() / ui::scale) - 28;
	
	
	// disable UI and camera interruption
	if (mouseX <= 200 * ui::scale) {
		cam.disableMouseInput();
	} else {
		cam.enableMouseInput();
	}
	
	
	//loop through images in dir
	for(int i = 0; i < imgDir.size(); i++){
		areaImageList[i].detect(areaImages[i], gx, gy);
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundColor(_bgcolor);
    
    
    // draw to FBO
    
    screen.begin();
        ofBackground(0);
	
		// draw areas
		for(int i = 0; i < imgDir.size(); i++){
			//if (areaImageList[i].isBusy() == true) {
				areaImageList[i].draw(0,0);
				areaTextList[i].draw(screen.getWidth()/2, screen.getHeight() - 9);
			//}
		}
	
		drawSequences();
	
		if (_showCursor) {
			drawCursor(gx, gy);
		}
	
    screen.end();
    
    
    // draw to preview
    
    preview.begin();
    
        screen.getTexture().readToPixels(p);
        ofPushStyle();
	
			glPointSize(radius);
			glEnable(GL_POINT_SMOOTH);
			glBegin(GL_POINTS);
            for (int x = 0; x < p.getWidth(); x++)
            {
                for (int y = 0; y < p.getHeight(); y++)
                {
                    ofColor c = p.getColor(x, y);
                    ofSetColor(c);
					glVertex2f(pixelPitch * x + (pixelPitch/2), pixelPitch * y + (pixelPitch/2));
                }
            }
	
		glEnd();
	
        ofPopStyle();
    
    preview.end();
    
    
	
	
    // display preview
    
    cam.begin();

		ofPushMatrix();
			ofTranslate(-preview.getWidth()/2, -preview.getHeight()/2);
			ofPushStyle();
	
				// draw valchromat box
				ofSetColor(_boxcolor);
				ofDrawBox(preview.getWidth()/2, preview.getHeight()/2, (-preview.getWidth()/2.4)/2, preview.getWidth(), preview.getHeight(), -preview.getWidth()/2.4);
	
				// draw plexi top
				ofSetColor(255, 255, 255, _plexiTransparency);
				ofDrawBox(preview.getWidth()/2, preview.getHeight()/2, 10, preview.getWidth(), preview.getHeight(), 20);
	
			ofPopStyle();
			preview.draw(0,0, preview.getWidth(), preview.getHeight());
	
		ofPopMatrix();
		
		ofPushStyle();
		
			// draw vertical plexi
			ofSetColor(255, 255, 255, _plexiTransparency);
			ofTranslate(0, preview.getHeight()/2 + 5);
			for (int i = 0; i < 26; i++) {
				int startY = -19 * pixelPitch;
				int yStep = 3 * pixelPitch;
				int height = 150; //millimeters
				int thickness = 5; //millimeters
				ofDrawBox(0, startY - (yStep * i), height/2, 104 * pixelPitch, thickness, height);
			}
		
		ofPopStyle();
	
    cam.end();
    
	
	// display UI
	_stage->draw();
	
	// display actual pixels preview (corner)
	screen.draw(28 * ui::scale, 28 * ui::scale, screen.getWidth() * ui::scale, screen.getHeight() * ui::scale);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
	// calculate UI size
	_hcell->setWidth(w);
	_hcell->setHeight(h);

}


void ofApp::drawCursor(int x, int y){
	
	ofPushStyle();
	
		ofSetColor(255,255,255,255);
		
		//top left
		ofDrawRectangle(x-2, y-2, 1, 1);
		ofDrawRectangle(x-1, y-1, 1, 1);
		
		//top right
		ofDrawRectangle(x+2, y-2, 1, 1);
		ofDrawRectangle(x+1, y-1, 1, 1);
		
		//low left
		ofDrawRectangle(x-2, y+2, 1, 1);
		ofDrawRectangle(x-1, y+1, 1, 1);
		
		//low right
		ofDrawRectangle(x+2, y+2, 1, 1);
		ofDrawRectangle(x+1, y+1, 1, 1);
	
	ofPopStyle();
	
	
	
}

void ofApp::drawSequences(){
	
	if (_sequenceOne == true) {
		ofSetColor(255);
		ofSetLineWidth(2);
		ofDrawLine(0, s1y, screen.getWidth(), s1y);
		
		if (s1y >= screen.getHeight()) {
			s1y = 0;
		}
		s1y++;
	}
	
	
	if (_sequenceTwo == true) {
		string dateString = ofToString(ofGetSeconds());
		headerText.calculate(headerFont, dateString);
		ofSetColor(255);
		headerText.draw(screen.getWidth()/2, screen.getHeight()/2);
	}
	
	
	if (_sequenceThree == true) {
		
		for (int y = 0; y < 26; y++) {
			int startX = 20;
			int startY = 18;
			int yStep = 3 * y;
			
			for (int x = 0; x < 104; x++) {
				
				int yPos = y * 5;
				int xPos = x * 5;
				
				float noiseX = ofNoise(xPos/100.0f, yPos/100.0f, ofGetElapsedTimef()) * 200;
				noiseX += ofNoise(xPos/50.0f, yPos/50.0f, ofGetElapsedTimef()/1.5f) * 25;
				noiseX += ofNoise(xPos/50.0f, yPos/50.0f, ofGetElapsedTimef()/0.75f) * 10;
				if (noiseX <= 0) { noiseX = 0; }
				if (noiseX >= 255) { noiseX = 255; }
//
//				cout << noiseX << endl;
//				
//				float cutOffThreshold = 0.8;
//				float randomNumber = ofRandom(1);
//
//				if (randomNumber <= cutOffThreshold) {
//					noiseX = 0;
//				}
				
				glPointSize(1.0);
				glBegin(GL_POINTS);
				
					ofSetColor(noiseX);
					glVertex2f((startX + x) + 0.5, (startY + yStep) + 0.5);
				
				glEnd();
				
			}
			

		}
		
	}
	
}


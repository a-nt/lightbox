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
	
	ui::init(1.0f); // 2.0 if retina display (plist high res YES)
	
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
	
	_bgcolor = ofFloatColor(.1f, .1f, .1f);
	_panel->addComponent(ui::ColorPicker<ofFloatColor>::create("Background color", &_bgcolor));
	
	_boxcolor.set(.05f, .05f, .05f);
	_panel->addComponent(ui::ColorPicker<ofFloatColor>::create("Box color", &_boxcolor));
	
	_plexiTransparency = 5;
	auto plexiSlider = ui::Slider<float>::create("Plexi transparency", &_plexiTransparency, 0, 255);
	_panel->addComponent(plexiSlider);
	
	_panel->addComponent(ui::Spacer::create(1));
	
	_panel->addComponent(ui::Toggle<bool>::create("Seq 1", &_sequenceOne));
	_panel->addComponent(ui::Toggle<bool>::create("Seq 2", &_sequenceTwo));
	
	
	
	// paths testing
	
	path.moveTo(10,20);
	path.lineTo(40,20);
	path.lineTo(40,40);
	path.lineTo(20,40);
	path.close();
	
	
	// png testing
	area.load("areas/screen.png");

	

}

//--------------------------------------------------------------
void ofApp::update(){
	
	// update UI elements
	_stage->update(ofGetElapsedTimef(), 0.0f);
	
	// control coordinates (switch with Kinect)
	gx = ofGetMouseX() - 28;
	gy = ofGetMouseY() - 28;
	
	// disable UI and camera interruption
	if (mouseX <= 200) {
		cam.disableMouseInput();
	} else {
		cam.enableMouseInput();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundColor(_bgcolor);
    
    
    // draw to FBO
    
    screen.begin();
        ofBackground(0);
	
//		ofPoint outline1;
//		outline1.set(17, 21);
//		if (ofDist(outline1.x, outline1.y, gx, gy) <= 40) {
//			area.draw(0,0);
//			string areaString = "440sqm";
//			areaText.calculate(font, areaString);
//			ofSetColor(255);
//			areaText.draw(40, 20);
//			
//		}
	
	
		// get bounds of image
		area.getTexture().readToPixels(areaP);
		
		for (int x = 0; x < areaP.getWidth(); x++)
		{
			for (int y = 0; y < areaP.getHeight(); y++)
			{
				ofColor c = areaP.getColor(x, y);
				if (c.getLightness() > 150) {
					if (ofDist(x, y, gx, gy) <= 0) {
						area.draw(0,0);
					}
				}
				
			}
			cout << boundsY.size() << endl;
		}

	
	
//		//SIMPLE GRADIENT
//		glBegin(GL_QUADS);
//		glColor3f( 1.0f, 0.0f, 0.0f );
//		glVertex3f( 0.0f, 0.0f, 0.0f );
//		glVertex3f( screen.getWidth(), 0.0f, 0.0f );
//		glColor3f( 0.0f, 0.0f, 1.0f );
//		glVertex3f( screen.getWidth(), screen.getHeight(), 0.0f );
//		glVertex3f( 0.0f, screen.getHeight(), 0.0f );
//		glEnd();
	
		//path.draw();
	
		if (_sequenceOne == true) {
			ofSetColor(255);
			ofSetLineWidth(2);
			ofDrawLine(0, s1y, screen.getWidth(), s1y);
			
			if (s1y >= screen.getHeight()) {
				s1y = 0;
			}
			s1y++;
		}
	
        ofSetColor(255);
	
		string testString2 = "NASJONALMUSEET 2020";
		text.calculate(font, testString2);
	
		text.draw(screen.getWidth()/2,screen.getHeight() - 9);
	
	
		if (_sequenceTwo == true) {
			string dateString = ofToString(ofGetSeconds());
			headerText.calculate(headerFont, dateString);
			ofSetColor(255);
			headerText.draw(screen.getWidth()/2, screen.getHeight()/2);
		}
	
	
	

	
	
		if (_showCursor) {
			drawCursor(gx, gy);
		}
	
    screen.end();
    
    
    
    
    // draw to preview
    
    preview.begin();
    
        screen.getTexture().readToPixels(p);
        ofPushStyle();
	
			glPointSize(radius);
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
    
    
    
    
    // aspect ratio calculation
    
    int side = ofGetWidth();
    if (ofGetHeight() < side) {
        side = ofGetHeight();
    }
    
    
    
    
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
	screen.draw(28, 28, screen.getWidth(), screen.getHeight());

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
	
}


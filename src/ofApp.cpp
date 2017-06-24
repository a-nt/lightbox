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
    
    
    // variables
    
    numTilesX = 9;
    numTilesY = 7;
    
    pixelPitch = 16;
    radius = 5;
    
    
    // font loading
    font.load("fonts/hooge05_53.ttf", 6);
    
    area.load("areas/screen.png");
    
    
    // allocate FBOs
    
    screen.allocate(numTilesX * pixelPitch, numTilesY * pixelPitch);
    
    screen.begin();
    ofClear(0,0,0,255);
    screen.end();
    
    
    preview.allocate(screen.getWidth() * pixelPitch, screen.getHeight() * pixelPitch);
    
    preview.begin();
    ofClear(0, 0, 0, 255);
    preview.end();
    
    
    // paths
    
    path.moveTo(10,20);
    path.lineTo(40,20);
    path.lineTo(40,40);
    path.lineTo(20,40);
    path.close();
	
	
	
	
	
	// setup UI
	//
	//
	
	ui::init(1.0f);
	
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

	
	auto slider0 = ui::Slider<float>::create("Float Slider", &_myFloat, 10.0f, 200.0f);
	_panel->addComponent(slider0);
	
	auto label = ui::Label::create("lightBox");
	_panel->addComponent(label);
	
	auto fps = ui::FpsLabel::create();
	_panel->addComponent(fps);
	
	_panel->addComponent(ui::Spacer::create(1));
	
	_panel->addComponent(ui::Toggle<bool>::create("My toggle", &_boolValue));
	
	// color
	_bgcolor = ofFloatColor(.1f, .1f, .1f);
	_panel->addComponent(ui::ColorPicker<ofFloatColor>::create("Background color", &_bgcolor));
	
	// define parameters
	_myFloatParam.set("floatparam 222", 1.0f, 0.0f, 10.0f);
	

	// add all parameters
	_params.add(_myFloatParam);
	
	vector<ui::ComponentPtr> components = ui::createComponentsForParameterGroup(_params);
	_panel->addComponents(components);
	
    

}

//--------------------------------------------------------------
void ofApp::update(){
	
	// update UI elements
	_stage->update(ofGetElapsedTimef(), 0.0f);

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundColor(_bgcolor);
    
    
    // draw to FBO
    
    screen.begin();
        ofBackground(0);
    
        area.draw(0,0);
	
	
//		SIMPLE GRADIENT
//		glBegin(GL_QUADS);
//		glColor3f( 1.0f, 0.0f, 0.0f );
//		glVertex3f( 0.0f, 0.0f, 0.0f );
//		glVertex3f( screen.getWidth(), 0.0f, 0.0f );
//		glColor3f( 0.0f, 0.0f, 1.0f );
//		glVertex3f( screen.getWidth(), screen.getHeight(), 0.0f );
//		glVertex3f( 0.0f, screen.getHeight(), 0.0f );
//		glEnd();
	
        ofSetColor(255);
	
		string testString2 = "Nasjonalmuseet";
		text.calculate(font, testString2);
		text.draw(ofGetMouseX() - (ofGetWidth() - screen.getWidth()),ofGetMouseY());
	
	
        //ofDrawRectangle(60, 60, 30, 30);
    
        //path.draw();
    

    
    
//        for (int x = 0; x < screen.getWidth(); x++) {
//            for (int y = 0; y < screen.getHeight(); y++) {
//                ofSetColor(ofRandom(255));
//                ofDrawRectangle(x, y, 1, 1);
//            }
//        }
    
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
                    //ofDrawCircle(pixelPitch * x + (pixelPitch/2), pixelPitch * y + (pixelPitch/2), radius);
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
    
    //cam.begin();
    
        //preview.draw(ofGetWidth()/2 - side/2,ofGetHeight()/2 - side/2, screen.getWidth() * 10, screen.getHeight() * 10);
        preview.draw(0,0, screen.getWidth() * 10, screen.getHeight() * 10);
    
    //cam.end();
    
    
    
    
    // display actual pixels preview (corner)
    
    screen.draw(ofGetWidth()-screen.getWidth(), 0, screen.getWidth(), screen.getHeight());
    
    
    
    
    //display fps
    
    char fpsStr[255]; // an array of chars
    sprintf(fpsStr, "FPS %f", ofGetFrameRate());
    ofPushStyle();
    ofSetColor(65);
    font.drawString(fpsStr, 15,20);
    ofPopStyle();
	
	_stage->draw();
	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
	// calculate UI size
	_hcell->setWidth(w);
	_hcell->setHeight(h);

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

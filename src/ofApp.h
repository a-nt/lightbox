#pragma once

#include "ofMain.h"
#include "Text.hpp"
#include "ofxVoid/ui/DisplayObject.h"
#include "ofxVoid/ui/Panel.h"
#include "ofxVoid/ui/CellLayout.h"
#include "ofxVoid/ui/Scene3D.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofFbo screen;
    ofFbo preview;

    ofEasyCam cam;
    
    int pixelPitch;
    
    float radius;
    
    ofPixels p;
    
    ofPath path;
    
    //fonts
    ofTrueTypeFont font;
	Text text;
    
    ofImage area;
    
    int numTilesX;
    int numTilesY;
	
	float _myFloat;
	
	
	// UI

	shared_ptr<ofxVoid::ui::CellLayout> _hcell;
	shared_ptr<ofxVoid::ui::CellLayout> _vcell;
	
	ofxVoid::ui::DisplayObjectPtr _stage;
	ofxVoid::ui::PanelPtr _panel;
	
	ofParameterGroup _params;
	
	ofParameter<float> _myFloatParam;
	
	ofFloatColor _bgcolor;
	
	bool _boolValue;

	
		
};

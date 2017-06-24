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
		void windowResized(int w, int h);
	
		void drawCursor(int x, int y);

    
    ofFbo screen;
    ofFbo preview;

    ofEasyCam cam;
    
    int pixelPerTile;
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
	
	// UI variables
	ofFloatColor _bgcolor;
	ofFloatColor _boxcolor;
	float _plexiTransparency;
	
	
	bool _sequenceOne;
	
	
	int y;

	
		
};

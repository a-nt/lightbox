#pragma once

#include "ofMain.h"
#include "Text.hpp"
#include "Area.hpp"
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

	
	int gx;
	int gy;
    
    ofFbo screen;
    ofFbo preview;
	ofPixels p;

    ofEasyCam cam;
	
	int numTilesX;
	int numTilesY;
	
    int pixelPerTile;
	int pixelPitch;
    float radius;
	
	
    
    //fonts
    ofTrueTypeFont font;
	ofTrueTypeFont headerFont;
	
	Text text;
	Text areaText;
	Text headerText;
	
	
	// UI

	shared_ptr<ofxVoid::ui::CellLayout> _hcell;
	shared_ptr<ofxVoid::ui::CellLayout> _vcell;
	ofxVoid::ui::DisplayObjectPtr _stage;
	ofxVoid::ui::PanelPtr _panel;
	
	// UI variables
	ofFloatColor _bgcolor;
	ofFloatColor _boxcolor;
	float _plexiTransparency;
	
	bool _showCursor;
	
	
	bool _sequenceOne;
	bool _sequenceTwo;
	bool _sequenceThree;
	
	
	// temporary
	
	int s1y;


	
	
	// directory area check
	string path;
	ofDirectory dir;
	
	vector<ofImage> areaImages;
	vector<Area> areaList;
	
	
	
	
	
	
	
		
};

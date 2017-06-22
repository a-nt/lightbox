#pragma once

#include "ofMain.h"
#include "Text.hpp"

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

		
};

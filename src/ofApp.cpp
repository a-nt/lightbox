#include "ofApp.h"

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
    

}

//--------------------------------------------------------------
void ofApp::update(){
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundColor(30);
    
    
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

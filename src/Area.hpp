#include "ofMain.h"

class Area {
public:
	
	void detect(ofImage tex, int distX, int distY);
	void draw(int x, int y);
	
	Area();
	
	ofImage _texture;
	int _distX;
	int _distY;
	ofPixels p;
	
	bool inReach;
	int numPxInBounds;
	
	float alpha;
	
};

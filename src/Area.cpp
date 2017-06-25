//
//  Area.cpp
//  Calculate bounding box of ofImage
//	Created by Anders NT - Void Studio
//

#include "Area.hpp"

Area::Area(){
	//inReach = false;
	
}

void Area::detect(ofImage tex, int distX, int distY) {
	
	_texture = tex;
	_distX = distX;
	_distY = distY;
	
	_texture.getTexture().readToPixels(p);
	
	numPxInBounds = 0;
	
	
	// calculate bounds
	for (int x = 0; x < p.getWidth(); x++)
	{
		for (int y = 0; y < p.getHeight(); y++)
		{
			ofColor c = p.getColor(x, y);
			if (c.getLightness() > 150) {
				if (ofDist(x, y, _distX, _distY) <= 0) {
					numPxInBounds++;
				}
			}
		}
	}
	
	// define number of pixels in bound
	if (numPxInBounds >= 1) {
		inReach = true;
	} else if (numPxInBounds == 0) {
		inReach = false;
	}
	
	
}

void Area::draw(int x, int y) {
	
	if (inReach == true) {
		_texture.draw(x,y);
	}

	
}

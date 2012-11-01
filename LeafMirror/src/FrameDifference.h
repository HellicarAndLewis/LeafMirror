/*
 * FrameDifference.h
 *
 *  Created on: Nov 1, 2012
 *      Author: arturo
 */

#ifndef FRAMEDIFFERENCE_H_
#define FRAMEDIFFERENCE_H_

#include "ofPixels.h"
#include "ofxCv.h"

class FrameDifference {
public:
	FrameDifference();

	void update(ofPixels & frame);
	void drawDebug(float x, float y);

	vector<ofVec2f> & getPointsMovement();

	ofParameter<float> minAreaMovement;
private:
	ofPixels prevFrame,diff;
	ofxCv::ContourFinder contourFinder;
	vector<ofVec2f> pointsMovement;
	ofTexture tex;
};

#endif /* FRAMEDIFFERENCE_H_ */

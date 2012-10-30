/*
 * KinectController.h
 *
 *  Created on: Oct 29, 2012
 *      Author: arturo
 */

#ifndef KINECTCONTROLLER_H_
#define KINECTCONTROLLER_H_

#include "ofxKinect.h"
#include "ofParameter.h"

class KinectController {
public:
	KinectController();

	void setup();
	void update();
	bool isFrameNew();
	void drawDebug(float x, float y);

	vector<ofPath> & getBlobs();

	ofParameter<int> near, far;
	ofParameter<int> minX, maxX;
	ofParameter<int> minArea, maxArea;
	ofParameter<int> tilt;
	ofParameter<float> resampling;
	ofParameter<float> smoothing;
	ofParameter<float> smoothingShape;
	ofParameter<int> maxHoleSize;
	ofParameterGroup parameters;

	ofxKinect kinect;

private:
	ofPixels grayThresNear, grayThresFar, mask;
	ofPixels contourCopy;
	ofImage thresholdImg;
	ofPixels gray;
	ofTexture grayTex;
	vector<ofPath> paths;
	bool bNewFrame;

	void findContours();
	void maskChanged(int & param);
	void tiltChanged(int & tilt);
};

#endif /* KINECTCONTROLLER_H_ */

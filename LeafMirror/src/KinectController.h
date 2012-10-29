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
#include "ofxCv.h"
#include "ofxKinectInpainter.h"

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
	ofPixels fillmask;
	ofImage thresholdImg;
	ofPixels gray;
	ofTexture grayTex;
	ofxCv::ContourFinder contourFinder;
	vector<ofPath> paths;
	bool bNewFrame;
	ofxKinectInpainter kinectInPaint;

	void findContours();
	void maskChanged(int & param);
	void tiltChanged(int & tilt);
};

#endif /* KINECTCONTROLLER_H_ */

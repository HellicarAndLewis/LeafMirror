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
#include <queue>

class KinectController {
public:
	KinectController();

	void setup();
	void update();
	bool isFrameNew();
	void drawDebug(float x, float y);

	vector<ofPath> & getBlobs();

	ofParameter<int> near, far;
	ofParameter<int> minArea, maxArea;
	ofParameter<int> minHoleArea,maxHoleArea;
	ofParameter<int> tilt;
	ofParameter<float> resampling;
	ofParameter<float> smoothing;
	ofParameter<float> smoothingShape;
	ofParameter<int> innerBandThreshold;
	ofParameter<int> outerBandThreshold;
	ofParameter<int> kernelSize;
	ofParameterGroup parameters;

	ofxKinect kinect;

private:
	ofPixels grayThresNear, grayThresFar;
	ofPixels contourCopy;
	ofImage thresholdImg;
	ofPixels gray;
	ofTexture grayTex,smoothDepthTex;
	vector<ofPath> paths;
	bool bNewFrame;
	vector<unsigned char> depthLookupTable;
	ofShortPixels smoothDepthArray;


	void findContours();
	void smoothDepth();
	void maskChanged(int & param);
	void tiltChanged(int & tilt);

	void updateDepthLookupTable();
};

#endif /* KINECTCONTROLLER_H_ */

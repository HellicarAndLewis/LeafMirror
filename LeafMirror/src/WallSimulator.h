/*
 * WallSimulator.h
 *
 *  Created on: Oct 30, 2012
 *      Author: arturo
 */

#ifndef WALLSIMULATOR_H_
#define WALLSIMULATOR_H_

#include "ofFbo.h"
#include "ofParameter.h"
#include "ofParameterGroup.h"

class WallSimulator {
public:
	WallSimulator();

	void setup();

	void begin();
	void end();

	void drawSimulation(float xW, float yW);
	void drawOutput(float x, float y, float w, float h);

	ofParameter<ofVec2f> wallSize;
	ofParameter<ofVec2f> ledSeparation;
	ofParameter<int> ledRadius;
	ofParameterGroup parameters;

private:
	void wallSizeChanged(ofVec2f & wallSize);
	ofFbo fbo;
	ofPixels pixels;
};

#endif /* WALLSIMULATOR_H_ */

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
#include "ofVboMesh.h"
#include "Glow.h"

class WallSimulator {
public:
	WallSimulator();

	void setup();

	void begin();
	void end();

	void drawSimulation(float xW, float yW);
	void drawOutput(float x, float y, float w, float h);

	ofParameter<int> wallHeight,wallWidth;
	ofParameter<float> ledSeparationX,ledSeparationY;
	ofParameter<int> ledRadius;
	ofParameter<bool> outputTexFilter;
	ofParameterGroup parameters;

private:
	void wallSizeChanged(int & wallSize);
	void outputTexFilterChanged(bool & outputTexFilter);
	void ledSeparationChanged(float & ledSeparation);
	ofFbo fbo;
	ofPixels pixels;
	ofVboMesh mesh;
	Glow glow;
};

#endif /* WALLSIMULATOR_H_ */

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
#include "ParticleSystem.h"
#include "KinectController.h"

class WallSimulator {
public:
	WallSimulator();

	void setup(KinectController & kinect);

	void update();

	void drawBackground(float x, float y);
	void drawSimulation(float xW, float yW);
	void drawOutput(float x, float y, float w, float h);
	void drawBlobs(float x, float y);
	void drawFbos(float x, float y);

	ofParameter<int> wallHeight,wallWidth;
	ofParameter<float> ledSeparationX,ledSeparationY;
	ofParameter<int> ledRadius;
	ofParameter<bool> outputTexFilter;
	ofParameter<ofColor> backgroundColor;
	ofParameterGroup parameters;
	ParticleSystem particles;

private:
	void wallSizeChanged(int & wallSize);
	void outputTexFilterChanged(bool & outputTexFilter);
	void ledSeparationChanged(float & ledSeparation);
	ofPixels pixels;
	ofVboMesh mesh;
	Glow glowParticles,glowBlobs;
	ofFbo fbo;
	ofShader filterShader;
	KinectController * kinect;
	u_long lastTimeParticles;

};

#endif /* WALLSIMULATOR_H_ */

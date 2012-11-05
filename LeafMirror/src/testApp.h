#pragma once

#include "ofMain.h"
#include "KinectController.h"
#include "ofxGui.h"
#include "WallSimulator.h"
#include "FrameDifference.h"
#include "ParticleSystem.h"
#include "Particle.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		KinectController kinect;
		ofxPanel gui;
		ofParameter<bool> fill;
		ofParameter<int> debugView;
		ofParameter<int> outputOffsetX,outputOffsetY;
		ofParameter<int> outputSizeX,outputSizeY;
		ofParameter<bool> useParticles;
		ofParameter<bool> renderFill;
		ofParameter<ofColor> fillColor;
		ofParameter<ofColor> bgColor;
		WallSimulator wall;
		FrameDifference frameDifference;
		ofColor currentColor;

		bool showGui;
};

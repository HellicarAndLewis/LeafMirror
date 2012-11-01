/*
 * Particle.cpp
 *
 *  Created on: Nov 1, 2012
 *      Author: arturo
 */

#include "Particle.h"
#include "ofAppRunner.h"

ofParameter<float> Particle::acc;
int Particle::screenHeight=35;


ofColor niceRandomColor(){
	ofColor c;
	unsigned char hue = ofRandom(255);
	unsigned char sat = ofRandom(190,256);
	unsigned char bri = ofRandom(190,256);
	c.setHsb(hue,sat,bri);
	return c;
}

Particle::Particle(const ofVec2f & pos)
:pos(pos)
,alive(true)
,color(niceRandomColor())
{
}

void Particle::update(){
	vel.y += float(acc)*ofGetLastFrameTime();
	pos += ofVec2f(vel)*ofGetLastFrameTime();
	if(pos.y>screenHeight) alive=false;
}

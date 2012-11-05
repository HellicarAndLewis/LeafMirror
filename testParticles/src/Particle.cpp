/*
 * Particle.cpp
 *
 *  Created on: Nov 1, 2012
 *      Author: arturo
 */

#include "Particle.h"
#include "ofAppRunner.h"

ofParameter<float> Particle::acc=900;
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
,originalColor(color)
,timeCreated(ofGetElapsedTimeMillis())
{
}

void Particle::update(u_long now){
	u_long timeDiff = now - timeCreated;
	if(timeDiff<1000){
		float pct = 1-double(timeDiff)/1000.;
		color.set(ofLerp(originalColor.r,0,pct),
			ofLerp(originalColor.g,33,pct),
			ofLerp(originalColor.b,67,pct));
	}else if(timeDiff>2000 && timeDiff<=4000){
		float pct = 1-double(4000-timeDiff)/2000.;
		color.set(ofLerp(originalColor.r,0,pct),
				ofLerp(originalColor.g,33,pct),
				ofLerp(originalColor.b,67,pct));
	}else if(timeDiff>6000){
		alive = false;
	}
	//vel.y += acc*ofGetLastFrameTime();
	//pos += vel*ofGetLastFrameTime();
}

/*
 * Particle.cpp
 *
 *  Created on: Nov 1, 2012
 *      Author: arturo
 */

#include "Particle.h"
#include "ofAppRunner.h"
#include "ofGraphics.h"

ofParameter<float> Particle::acc=900;
int Particle::screenHeight=35;



Particle::Particle(const ofVec2f & pos, const ofColor & color)
:pos(pos)
,size(0)
,alive(true)
,color(color)
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
	}else if(timeDiff>4000 && timeDiff<=7000){
		float pct = 1-double(7000-timeDiff)/3000.;
		color.set(ofLerp(originalColor.r,0,pct),
				ofLerp(originalColor.g,33,pct),
				ofLerp(originalColor.b,67,pct));
	}else if(timeDiff>7000){
		alive = false;
	}
	size = double(timeDiff)/1000.;
	//vel.y += acc*ofGetLastFrameTime();
	//pos += vel*ofGetLastFrameTime();
}

void Particle::draw(){
	ofFill();
	ofSetColor(color);
	ofCircle(pos,size*.5*640./20.);
}

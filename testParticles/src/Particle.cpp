/*
 * Particle.cpp
 *
 *  Created on: Nov 1, 2012
 *      Author: arturo
 */

#include "Particle.h"
#include "ofAppRunner.h"
#include "ofGraphics.h"

ofParameter<float> Particle::acc;
ofParameter<int> Particle::msGrow;
ofParameter<int> Particle::msStay;
ofParameter<int> Particle::msDissolve;
ofParameter<float> Particle::sizePerSecond;
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
	if(timeDiff<msGrow){
		float pct = 1-double(timeDiff)/(double)msGrow;
		color.set(ofLerp(originalColor.r,0,pct),
			ofLerp(originalColor.g,33,pct),
			ofLerp(originalColor.b,67,pct));
	}else if(timeDiff>msGrow+msStay && timeDiff<=msGrow+msStay+msDissolve){
		float pct = 1-double(msGrow+msStay+msDissolve-timeDiff)/(double)msDissolve;
		color.set(ofLerp(originalColor.r,0,pct),
				ofLerp(originalColor.g,33,pct),
				ofLerp(originalColor.b,67,pct));
	}else if(timeDiff>msGrow+msStay+msDissolve){
		alive = false;
	}
	u_long totalTime = msGrow+msStay+msDissolve;
	float pct = double(timeDiff)/double(totalTime);
	pct=sqrt(pct);
	size = pct*double(totalTime)*double(sizePerSecond)/1000.;
	//vel.y += acc*ofGetLastFrameTime();
	//pos += vel*ofGetLastFrameTime();
}

void Particle::draw(){
	ofFill();
	ofSetColor(color);
	ofEllipse(pos,size*.5*640./20.,size*.5*480./10.);
}

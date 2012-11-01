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

Particle::Particle(const ofVec2f & pos)
:pos(pos)
,alive(true)
{

}

void Particle::update(){
	vel.y += float(acc)*ofGetLastFrameTime();
	pos += ofVec2f(vel)*ofGetLastFrameTime();
	if(pos.y>screenHeight) alive=false;
}

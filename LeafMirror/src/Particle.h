/*
 * Particle.h
 *
 *  Created on: Nov 1, 2012
 *      Author: arturo
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "ofVec2f.h"
#include "ofParameter.h"

class Particle {
public:
	Particle(const ofVec2f & pos);

	void update();

	static ofParameter<ofVec2f> acc;
	static int screenHeight;
	ofVec2f pos;
	ofVec2f vel;
	bool alive;


};

#endif /* PARTICLE_H_ */

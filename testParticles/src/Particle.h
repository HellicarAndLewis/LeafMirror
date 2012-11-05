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

	void update(u_long now);

	static ofParameter<float> acc;
	static int screenHeight;
	ofVec2f pos;
	ofVec2f vel;
	bool alive;
	ofColor color,originalColor;
	u_long timeCreated;

};

#endif /* PARTICLE_H_ */

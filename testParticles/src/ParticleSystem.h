/*
 * ParticleSystem.h
 *
 *  Created on: Nov 1, 2012
 *      Author: arturo
 */

#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

#include "Particle.h"
#include "ofMesh.h"
#include "ofParameterGroup.h"
#include <list>

class ParticleSystem {
public:
	ParticleSystem();

	void addParticle(const ofVec2f & pos, const ofColor & color);
	void update(u_long now);
	void draw(float x, float y);

	bool empty(){
		return particles.empty();
	}

	ofParameterGroup parameters;

private:
	list<Particle> particles;
	ofMesh renderMesh;
};

#endif /* PARTICLESYSTEM_H_ */

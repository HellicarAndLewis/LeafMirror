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
#include <list>

class ParticleSystem {
public:
	ParticleSystem();

	void addParticle(const ofVec2f & pos);
	void update();
	void draw(float x, float y);

private:
	list<Particle> particles;
	ofMesh renderMesh;
};

#endif /* PARTICLESYSTEM_H_ */

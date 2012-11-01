/*
 * ParticleSystem.cpp
 *
 *  Created on: Nov 1, 2012
 *      Author: arturo
 */

#include "ParticleSystem.h"
#include "ofGraphics.h"

ParticleSystem::ParticleSystem() {
	renderMesh.setMode(OF_PRIMITIVE_POINTS);
	Particle::acc.set("accel",40,-300,300);
}

void ParticleSystem::update(){
	renderMesh.getVertices().resize(particles.size());
	renderMesh.getColors().resize(particles.size());
	list<Particle>::iterator it;
	int i=0;
	for(it=particles.begin();it!=particles.end();++it, ++i){
		it->update();
		if(!it->alive){
			list<Particle>::iterator itToDelete = it;
			it--;
			particles.erase(itToDelete);
		}
		renderMesh.getVertices()[i]=it->pos;
		renderMesh.getColors()[i]=it->color;
	}
}

void ParticleSystem::draw(float x, float y){
	ofPushMatrix();
	ofTranslate(x,y);
	glPointSize(1);
	renderMesh.draw();
	ofPopMatrix();
}

void ParticleSystem::addParticle(const ofVec2f & pos){
	particles.push_back(Particle(pos));
}

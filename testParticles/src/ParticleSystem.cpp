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
	Particle::msGrow.set("msGrow",1000,1,5000);
	Particle::msStay.set("msStay",3000,1,6000);
	Particle::msDissolve.set("msDissolve",3000,1,6000);
	Particle::sizePerSecond.set("sizePerSecond",1,.01,3);

	parameters.setName("particles");
	parameters.add(Particle::acc);
	parameters.add(Particle::msGrow);
	parameters.add(Particle::msStay);
	parameters.add(Particle::msDissolve);
	parameters.add(Particle::sizePerSecond);
}

void ParticleSystem::update(){
	u_long now = ofGetElapsedTimeMillis();
	/*renderMesh.getVertices().resize(particles.size());
	renderMesh.getColors().resize(particles.size());
	renderMesh.getNormals().resize(particles.size());*/
	list<Particle>::iterator it;
	int i=0;
	for(it=particles.begin();it!=particles.end();++it, ++i){
		it->update(now);
		if(!it->alive){
			list<Particle>::iterator itToDelete = it;
			it--;
			particles.erase(itToDelete);
		}
		/*renderMesh.getVertices()[i]=it->pos;
		renderMesh.getColors()[i]=it->color;
		renderMesh.getNormals()[i].set(it->size,0);*/
	}
}

void ParticleSystem::draw(float x, float y){
	ofPushMatrix();
	ofTranslate(x,y);
	//glPointSize(5);
	//renderMesh.draw();
	list<Particle>::iterator it;
	for(it=particles.begin();it!=particles.end();++it){
		it->draw();
	}
	ofPopMatrix();
}

void ParticleSystem::addParticle(const ofVec2f & pos, const ofColor & color){
	particles.push_back(Particle(pos,color));
}

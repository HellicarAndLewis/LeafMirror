/*
 * ParticlesEffect.h
 *
 *  Created on: Nov 4, 2012
 *      Author: arturo
 */

#ifndef PARTICLESEFFECT_H_
#define PARTICLESEFFECT_H_

#include "ofFbo.h"
#include "ofShader.h"

class ParticlesEffect {
public:
	ParticlesEffect();
	virtual ~ParticlesEffect();

	void setup();

	void begin();
	void end();

	ofFbo fbo1,fbo2;
	ofShader shader;
};

#endif /* PARTICLESEFFECT_H_ */

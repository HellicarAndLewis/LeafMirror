/*
 * ParticlesEffect.cpp
 *
 *  Created on: Nov 4, 2012
 *      Author: arturo
 */

#include "ParticlesEffect.h"

// Set up texture sampling offset storage
const GLint tcOffsetColumns = 3;
const GLint tcOffsetRows    = 3;
GLfloat	texCoordOffsets[tcOffsetColumns * tcOffsetRows * 2];

ParticlesEffect::ParticlesEffect() {
	// TODO Auto-generated constructor stub

}

ParticlesEffect::~ParticlesEffect() {
	// TODO Auto-generated destructor stub
}


void ParticlesEffect::setup(){

	shader.load("","particles.frag");

	float xInc = 1;
	float yInc = 1;
	for (int i = 0; i < tcOffsetColumns; i++)
	{
		for (int j = 0; j < tcOffsetRows; j++)
		{
			texCoordOffsets[(((i*tcOffsetColumns)+j)*2)+0] = (-2.0f * xInc) + ((GLfloat)i * xInc);
			texCoordOffsets[(((i*tcOffsetRows)+j)*2)+1] = (-2.0f * yInc) + ((GLfloat)j * yInc);
		}
	}
	fbo1.allocate(114,35);
	fbo2.allocate(114,35);
}

void ParticlesEffect::begin(){
	fbo1.begin();
}

void ParticlesEffect::end(){
	fbo1.end();

	fbo2.begin();
	shader.begin();
	shader.setUniformTexture("src_tex_unit0",fbo1.getTextureReference(),0);
	shader.setUniform2fv("tcOffset",texCoordOffsets,tcOffsetColumns * tcOffsetRows);
	fbo1.draw(0,0);
	shader.end();
	fbo2.end();
}

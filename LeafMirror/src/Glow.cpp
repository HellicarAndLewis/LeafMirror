/*
 * Glow.cpp
 *
 *  Created on: 15/02/2012
 *      Author: arturo
 */

#include "Glow.h"
#include "ofAppRunner.h"
#include "ofGraphics.h"

Glow::Glow() {
	passes.set("passes",5,0,10);
	brightness.set("brightness",1,0,4);

}

Glow::~Glow() {
	// TODO Auto-generated destructor stub
}

void Glow::setup(float w, float h,string vertShader){
	shader.load(vertShader,"glow.frag");

	ofFbo::Settings settings;
	settings.depthStencilAsTexture = true;
	settings.useDepth = true;
	settings.width = w;
	settings.height = h;
	settings.internalformat = GL_RGBA;
	settings.depthStencilInternalFormat = GL_DEPTH_COMPONENT32;
	settings.useStencil = false;
	//settings.numSamples = 4;

	fbo1.allocate(settings);
	fbo2.allocate(settings);

	bgAuto = false;
	bgColor = ofColor(0,0);
}

void Glow::setBackgroundAuto(bool _bgAuto){
	bgAuto = _bgAuto;
}

void Glow::setBackgroundColor(const ofColor & color){
	bgColor = color;
}

void Glow::begin(bool setPerspective){
	fbo1.begin(setPerspective);
	if(bgAuto) ofClear(bgColor);
}

void Glow::end(){
	fbo1.end();

	ofSetColor(255);
	for(int i=0;i<passes;i++){
		fbo2.begin();
		if(bgAuto) ofClear(bgColor);
		shader.begin();
		shader.setUniformTexture("src_tex_unit0",fbo1.getTextureReference(),0);
		shader.setUniform1i("direction",0);
		shader.setUniform1f("brightness",brightness);
		fbo1.draw(0,0);
		shader.end();
		fbo2.end();

		fbo1.begin();
		if(bgAuto) ofClear(bgColor);
		shader.begin();
		shader.setUniformTexture("src_tex_unit0",fbo2.getTextureReference(),0);
		shader.setUniform1i("direction",1);
		shader.setUniform1f("brightness",brightness);
		fbo2.draw(0,0);
		shader.end();
		fbo1.end();
	}
}

ofTexture & Glow::getDepthTexture(){
	return fbo1.getDepthTexture();
}

ofTexture & Glow::getTextureReference(){
	return fbo1.getTextureReference();
}

void Glow::readToPixels(ofPixels & pixels){
	fbo1.readToPixels(pixels);
}

void Glow::draw(float x, float y){
	fbo1.draw(x,y);
}

void Glow::draw(float x, float y, float w, float h){
	fbo1.draw(x,y,w,h);
}

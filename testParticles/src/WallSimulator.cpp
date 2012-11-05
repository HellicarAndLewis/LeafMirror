/*
 * WallSimulator.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: arturo
 */

#include "WallSimulator.h"
#include "ofGraphics.h"


WallSimulator::WallSimulator() {
	// TODO Auto-generated constructor stub

}

void WallSimulator::setup(){

	parameters.setName("wall");
	parameters.add(wallWidth.set("wallWidth",114,1,200));
	parameters.add(wallHeight.set("wallHeight",35,1,200));
	parameters.add(ledSeparationX.set("ledSeparationX",14,0,20));
	parameters.add(ledSeparationY.set("ledSeparationY",14,0,20));
	parameters.add(ledRadius.set("ledRadius",5,1,20));
	parameters.add(outputTexFilter.set("outputTexFilter",false));
	parameters.add(glow.passes);
	//parameters.add(glow.brightness);

	wallWidth.addListener(this,&WallSimulator::wallSizeChanged);
	wallHeight.addListener(this,&WallSimulator::wallSizeChanged);
	outputTexFilter.addListener(this,&WallSimulator::outputTexFilterChanged);
	ledSeparationX.addListener(this,&WallSimulator::ledSeparationChanged);
	ledSeparationY.addListener(this,&WallSimulator::ledSeparationChanged);

	int w = wallWidth;
	wallSizeChanged(w);
	bool texFilter = outputTexFilter;
	outputTexFilterChanged(texFilter);

	mesh.setMode(OF_PRIMITIVE_POINTS);
	particlesEffect.setup();
}

void WallSimulator::outputTexFilterChanged(bool & outputTexFilter){
	if(outputTexFilter){
		glow.getTextureReference().setTextureMinMagFilter(GL_LINEAR,GL_LINEAR);
		fbo.getTextureReference().setTextureMinMagFilter(GL_LINEAR,GL_LINEAR);
	}else{
		glow.getTextureReference().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
		fbo.getTextureReference().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
	}
}

void WallSimulator::wallSizeChanged(int & wallSize){
	glow.setup((int)wallWidth,(int)wallHeight);
	fbo.allocate((int)wallWidth,(int)wallHeight);
	float sep = ledSeparationX;
	ledSeparationChanged(sep);
}

void WallSimulator::ledSeparationChanged(float & ledSeparation){
	mesh.getVertices().resize(wallWidth*wallHeight);
	mesh.getColors().resize(wallWidth*wallHeight);
	for(int y=0;y<wallHeight;++y){
		for(int x=0;x<wallWidth;++x){
			mesh.getVertices()[y*wallWidth+x].set(x*ledSeparationX,y*ledSeparationY);
		}
	}
}


void WallSimulator::beginGlow(){
	glow.begin(true);
	drawBackground(0,0);
	ofPushMatrix();
	ofScale(wallWidth/640.,wallHeight/480.,1);
}

void WallSimulator::endGlow(){
	ofPopMatrix();
	glow.end();
}

void WallSimulator::begin(){
	particlesEffect.begin();
	glow.draw(0,0);
	ofPushMatrix();
	ofScale(wallWidth/640.,wallHeight/480.,1);
}

void WallSimulator::end(){
	ofPopMatrix();
	particlesEffect.end();
	particlesEffect.fbo2.readToPixels(pixels);
	for(int y=0;y<wallHeight;++y){
		for(int x=0;x<wallWidth;++x){
			mesh.getColors()[y*wallWidth+x]=pixels.getColor(x,y);
		}
	}
}


void WallSimulator::drawBackground(float x, float y){
	ofSetColor(0,33,67);
	ofRect(x,y,640,480);
	ofSetColor(255);
}

void WallSimulator::drawSimulation(float xW, float yW){
	glPointSize(ledRadius*2);
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(xW,yW+ledRadius);
	mesh.draw();
	ofPopMatrix();
}

void WallSimulator::drawOutput(float x, float y, float w, float h){
	particlesEffect.fbo2.draw(x,y,w,h);
}
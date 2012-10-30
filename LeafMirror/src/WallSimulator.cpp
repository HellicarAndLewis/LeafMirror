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
	wallSize.addListener(this,&WallSimulator::wallSizeChanged);
	outputTexFilter.addListener(this,&WallSimulator::outputTexFilterChanged);
	ledSeparation.addListener(this,&WallSimulator::ledSeparationChanged);

	parameters.setName("wall");
	parameters.add(wallSize.set("wallSize",ofVec2f(37,28),ofVec2f(0,0),ofVec2f(200,200)));
	parameters.add(ledSeparation.set("ledSeparation",ofVec2f(14,14),ofVec2f(0,0),ofVec2f(20,20)));
	parameters.add(ledRadius.set("ledRadius",5,1,20));
	parameters.add(outputTexFilter.set("outputTexFilter",false));

	mesh.setMode(OF_PRIMITIVE_POINTS);
}

void WallSimulator::outputTexFilterChanged(bool & outputTexFilter){
	if(outputTexFilter){
		fbo.getTextureReference().setTextureMinMagFilter(GL_LINEAR,GL_LINEAR);
	}else{
		fbo.getTextureReference().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
	}
}

void WallSimulator::wallSizeChanged(ofVec2f & wallSize){
	fbo.allocate((int)wallSize.x,(int)wallSize.y,GL_RGBA);
	mesh.getVertices().resize(wallSize.x*wallSize.y);
	mesh.getColors().resize(wallSize.x*wallSize.y);
	ofVec2f sep = ledSeparation;
	ledSeparationChanged(sep);
}

void WallSimulator::ledSeparationChanged(ofVec2f & ledSeparation){
	for(int y=0;y<wallSize->y;++y){
		for(int x=0;x<wallSize->x;++x){
			mesh.getVertices()[y*wallSize->x+x].set(x*ledSeparation.x,y*ledSeparation.y);
		}
	}
}


void WallSimulator::begin(){
	fbo.begin();
	ofPushMatrix();
	ofScale(wallSize->x/640.,wallSize->y/480.,1);
}

void WallSimulator::end(){
	ofPopMatrix();
	fbo.end();
	fbo.readToPixels(pixels);
	for(int y=0;y<wallSize->y;++y){
		for(int x=0;x<wallSize->x;++x){
			mesh.getColors()[y*wallSize->x+x]=pixels.getColor(x,y);
		}
	}
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
	fbo.draw(x,y,w,h);
}

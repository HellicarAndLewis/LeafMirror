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
	parameters.setName("wall");
	parameters.add(wallSize.set("wallSize",ofVec2f(37,28),ofVec2f(0,0),ofVec2f(200,200)));
	parameters.add(ledSeparation.set("ledSeparation",ofVec2f(7,7),ofVec2f(0,0),ofVec2f(20,20)));
	parameters.add(ledRadius.set("ledRadius",3,1,10));
}

void WallSimulator::wallSizeChanged(ofVec2f & wallSize){
	fbo.allocate((int)wallSize.x,(int)wallSize.y,GL_RGBA);
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
}

void WallSimulator::drawSimulation(float xW, float yW){
	for(int y=0;y<pixels.getHeight();++y){
		for(int x=0;x<pixels.getWidth();++x){
			ofSetColor(pixels.getColor(x,y));
			ofCircle(x*ledSeparation->x+xW,y*ledSeparation->y+yW,ledRadius);
		}
	}
	ofSetColor(255);
}

void WallSimulator::drawOutput(float x, float y, float w, float h){
	fbo.draw(x,y,w,h);
}

/*
 * FrameDifference.cpp
 *
 *  Created on: Nov 1, 2012
 *      Author: arturo
 */

#include "FrameDifference.h"
using namespace ofxCv;

FrameDifference::FrameDifference() {
	minAreaMovement.set("minAreaMovement",100,1,1000);
	contourFinder.setMinArea(300);
}

void FrameDifference::update(ofPixels & frame){
	pointsMovement.clear();
	if(prevFrame.isAllocated()){
		absdiff(frame,prevFrame,diff);
		//threshold(diff,80);
		contourFinder.findContours(diff);
		for(u_int i=0;i<contourFinder.getContours().size();++i){
			if(contourFinder.getContourArea(i)>minAreaMovement){
				pointsMovement.push_back(toOf(contourFinder.getCentroid(i)));
			}
		}
		tex.loadData(diff);
	}else{
		tex.allocate(frame);
	}

	prevFrame = frame;
}


vector<ofVec2f> & FrameDifference::getPointsMovement(){
	return pointsMovement;
}

void FrameDifference:: drawDebug(float x, float y){
	tex.draw(x,y,320,240);

	ofPushMatrix();
	ofTranslate(x+330,y);
	ofScale(.5,.5);
	contourFinder.draw();
	ofPopMatrix();
}

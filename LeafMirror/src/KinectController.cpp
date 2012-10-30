/*
 * KinectController.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: arturo
 */

#include "KinectController.h"
#include <set>
#include "ofxCv.h"

using namespace ofxCv;

KinectController::KinectController() {
	bNewFrame = false;

}


void KinectController::setup(){
	kinect.init(false,true,true);
	kinect.open();
	grayThresFar.allocate(640,480,OF_IMAGE_GRAYSCALE);
	grayThresNear.allocate(640,480,OF_IMAGE_GRAYSCALE);
	thresholdImg.allocate(640,480,OF_IMAGE_GRAYSCALE);
	gray.allocate(640,480,OF_IMAGE_GRAYSCALE);
	grayTex.allocate(640,480,GL_LUMINANCE);

	tilt.addListener(this,&KinectController::tiltChanged);

	parameters.setName("kinect");
	parameters.add(near.set("near",255,0,255));
	parameters.add(far.set("far",0,0,255));
	parameters.add(minArea.set("minArea",640.*480./10,0,1000));
	parameters.add(maxArea.set("maxArea",640.*480.,640.*480./10,640*480));
	parameters.add(minHoleArea.set("minHoleArea",50,0,1000));
	parameters.add(maxHoleArea.set("maxHoleArea",100,0,10000));
	parameters.add(tilt.set("tilt",0,-30,30));
	parameters.add(resampling.set("resampling",3,1,20));
	parameters.add(smoothing.set("smoothing",0.01,0,0.05));
	parameters.add(smoothingShape.set("smoothingShape",0,0,1));
}


void KinectController::tiltChanged(int & tilt){
	kinect.setCameraTiltAngle(tilt);
}

void KinectController::findContours(){
	vector<vector<cv::Point> > allContours;
	vector<Vec4i> hierarchy;
	vector<cv::Point> simplifiedContour;
	contourCopy = thresholdImg;
	cv::Mat threshodlMat = toCv(contourCopy);
	cv::findContours(threshodlMat, allContours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	map<int,int> index;
	int p = 0;
	paths.resize(hierarchy.size());
	for(u_int i=0;i<hierarchy.size();++i){
		double curArea = contourArea(Mat(allContours[i]));
		if(hierarchy[i][3]==-1){
			if(curArea >= minArea && curArea <= maxArea){
				paths[p].clear();
				ofPolyline polyline = toOf(allContours[i]);
				polyline = polyline.getResampledBySpacing(resampling);
				polyline = polyline.getSmoothed(smoothing*polyline.size(),smoothingShape);
				ofPath & path = paths[p];
				for(u_int j=0;j<polyline.size();j++){
					path.lineTo(polyline[j]);
				}
				path.close();
				index[i] = p;
				p++;
			}
		}else if(curArea >= minHoleArea && curArea <= maxHoleArea
				&& index.find(hierarchy[i][3])!=index.end()){
			ofPolyline polyline = toOf(allContours[i]);
			polyline = polyline.getResampledBySpacing(resampling);
			polyline = polyline.getSmoothed(smoothing*polyline.size(),smoothingShape);
			paths[index[hierarchy[i][3]]].moveTo(polyline[0]);
			for(u_int j=1;j<polyline.size();j++){
				paths[index[hierarchy[i][3]]].lineTo(polyline[j]);
			}
		}
	}
	paths.resize(p);

}

void KinectController::update(){
	kinect.update();
	if(kinect.isFrameNew()){
		gray = kinect.getDepthPixelsRef();
		threshold(gray,grayThresFar,far);
		threshold(gray,grayThresNear,near,true);
		cv::Mat thresholdMat = toCv(thresholdImg);
		cv::bitwise_and(toCv(grayThresNear), toCv(grayThresFar), thresholdMat);
		findContours();
		thresholdImg.update();
		grayTex.loadData(gray);
		bNewFrame = true;
	}else{
		bNewFrame = false;
	}
}

bool KinectController::isFrameNew(){
	return bNewFrame;
}

void KinectController::drawDebug(float x, float y){
	kinect.draw(x,y,320,240);
	kinect.drawDepth(x+330,y,320,240);
	thresholdImg.draw(x,y+250,320,240);
	grayTex.draw(x+330,y+250,320,240);
}


vector<ofPath> & KinectController::getBlobs(){
	return paths;
}

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	kinect.setup();
	wall.setup();
	ofSetVerticalSync(true);
	ofBackground(0);

	gui.setup("settings");
	gui.add(fill.set("fill",false));
	gui.add(debugView.set("debugView",0,0,3));
	gui.add(outputOffsetX.set("outputOffsetX",1280,0,2500));
	gui.add(outputOffsetY.set("outputOffsetY",0,0,1280));
	gui.add(outputSizeX.set("outputSizeX",1024,1,1920));
	gui.add(outputSizeY.set("outputSizeY",768,1,1280));
	gui.add(Particle::acc);
	gui.add(kinect.parameters);
	gui.add(wall.parameters);

	gui.loadFromFile("settings.xml");
	Particle::screenHeight = 480;

	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
}

//--------------------------------------------------------------
void testApp::update(){
	kinect.update();
	if(kinect.isFrameNew()){
		frameDifference.update(kinect.getThreshold());
		for(u_int i=0;i<frameDifference.getPointsMovement().size();++i){
			particles.addParticle(frameDifference.getPointsMovement()[i]);
		}
		for(u_int i=0;i<kinect.getBlobs().size();++i){
			if(fill){
				kinect.getBlobs()[i].setStrokeWidth(0);
				kinect.getBlobs()[i].setFillColor(ofColor(251,231,0));
				kinect.getBlobs()[i].setFilled(true);
			}else{
				kinect.getBlobs()[i].setStrokeWidth(1);
				kinect.getBlobs()[i].setStrokeColor(ofColor(251,231,0));
				kinect.getBlobs()[i].setFilled(false);
			}
		}
	}
	particles.update();
	wall.begin();
	drawBlobs(0,0);
	wall.end();
}

void testApp::drawBlobs(float x, float y){
	ofSetColor(0,33,67);
	ofRect(x,y,640,480);
	for(u_int i=0;i<kinect.getBlobs().size();i++){
		kinect.getBlobs()[i].draw(x,y);
	}
	ofSetColor(ofColor(251,231,0));
	particles.draw(x,y);
	ofSetColor(255);
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	switch(debugView){
	case 0:
		kinect.drawDebug(240,10);
		break;
	case 1:
		wall.drawSimulation(240,10);
		break;
	case 2:
		drawBlobs(240,10);
		break;
	case 3:
		frameDifference.drawDebug(240,10);
	default:
		break;
	}

	gui.draw();
	wall.drawOutput(outputOffsetX,outputOffsetY,outputSizeX,outputSizeY);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

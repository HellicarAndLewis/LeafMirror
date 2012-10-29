#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	kinect.setup();
	gui.setup();
	gui.add(fill.set("fill",false));
	gui.add(kinect.parameters);
}

//--------------------------------------------------------------
void testApp::update(){
	kinect.update();
	if(kinect.isFrameNew()){
		paths.clear();
		for(u_int i=0;i<kinect.getBlobs().size();++i){
			if(fill){
				kinect.getBlobs()[i].setStrokeWidth(0);
				kinect.getBlobs()[i].setFillColor(ofColor(251,231,0));
				kinect.getBlobs()[i].setFilled(true);
			}else{
				kinect.getBlobs()[i].setStrokeWidth(3);
				kinect.getBlobs()[i].setStrokeColor(ofColor(251,231,0));
				kinect.getBlobs()[i].setFilled(false);
			}

			kinect.getBlobs()[i].close();
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	kinect.drawDebug(220,10);
	gui.draw();

	ofSetColor(0,33,67);
	ofRect(200+320*2+10*3,10,640,480);
	for(u_int i=0;i<kinect.getBlobs().size();i++){
		kinect.getBlobs()[i].draw(200+320*2+10*3,10);
	}

	ofSetColor(255);

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

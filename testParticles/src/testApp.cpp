#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	wall.setup();
	ofBackground(0);
	ofEnableAlphaBlending();
	wall.beginGlow();
	wall.drawBackground(0,0);
	wall.endGlow();
}

//--------------------------------------------------------------
void testApp::update(){
	particles.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	//unsigned long now = ofGetElapsedTimeMillis();
	//drawBackground(0,0);
	wall.beginGlow();
	particles.draw(0,0);
	wall.endGlow();

	wall.begin();
	//particles.draw(0,0);
	wall.end();
	wall.drawSimulation(0,0);

	wall.drawOutput(0,600,wall.wallWidth,wall.wallHeight);
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
	particles.addParticle(ofVec2f(x,y)/ofVec2f((wall.ledSeparationX)*wall.wallWidth,(wall.ledSeparationY)*wall.wallHeight)*ofVec2f(640,480));
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	particles.addParticle(ofVec2f(x,y)/ofVec2f((wall.ledSeparationX)*wall.wallWidth,(wall.ledSeparationY)*wall.wallHeight)*ofVec2f(640,480));
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

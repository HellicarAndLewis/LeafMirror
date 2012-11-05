#include "testApp.h"

ofColor niceRandomColor(){
	ofColor c;
	unsigned char hue = ofRandom(255);
	unsigned char sat = ofRandom(190,256);
	unsigned char bri = ofRandom(190,256);
	c.setHsb(hue,sat,bri);
	return c;
}

//--------------------------------------------------------------
void testApp::setup(){
	kinect.setup();
	wall.setup(kinect);
	ofSetVerticalSync(true);
	ofBackground(0);

	gui.setup("settings");
	gui.add(fill.set("fill",false));
	gui.add(debugView.set("debugView",0,0,3));
	gui.add(outputOffsetX.set("outputOffsetX",1280,0,2500));
	gui.add(outputOffsetY.set("outputOffsetY",0,0,1280));
	gui.add(outputSizeX.set("outputSizeX",1024,1,1920));
	gui.add(outputSizeY.set("outputSizeY",768,1,1280));
	gui.add(useParticles.set("useParticles",true));
	gui.add(kinect.parameters);
	gui.add(wall.parameters);
	gui.add(wall.particles.parameters);
	gui.add(renderFill.set("renderFill",false));
	gui.add(fillColor.set("fillColor",ofColor(251,231,0),ofColor(0,0,0,0),ofColor(255,255,255)));
	gui.add(bgColor.set("bgColor",ofColor(0,33,67),ofColor(0,0,0,0),ofColor(255,255,255)));

	currentColor = niceRandomColor();

	gui.loadFromFile("settings.xml");
	Particle::screenHeight = 480;

	showGui = true;

	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glEnable(GL_POINT_SMOOTH);

	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::update(){
	kinect.update();
	if(kinect.isFrameNew()){
		frameDifference.update(kinect.getThreshold());
		if(useParticles){
			for(u_int i=0;i<frameDifference.getPointsMovement().size();++i){
				wall.particles.addParticle(frameDifference.getPointsMovement()[i],currentColor);
			}
			if(frameDifference.getPointsMovement().empty()){
				currentColor = niceRandomColor();
			}
		}
		for(u_int i=0;i<kinect.getBlobs().size();++i){
			if(fill){
				kinect.getBlobs()[i].setStrokeWidth(0);
				kinect.getBlobs()[i].setFillColor(fillColor);
				kinect.getBlobs()[i].setFilled(true);
			}else{
				kinect.getBlobs()[i].setStrokeWidth(1);
				kinect.getBlobs()[i].setStrokeColor(fillColor);
				kinect.getBlobs()[i].setFilled(false);
			}
		}
	}

	wall.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	if(showGui){
		switch(debugView){
		case 0:
			kinect.drawDebug(240,10);
			break;
		case 1:
			wall.drawSimulation(240,10);
			break;
		case 2:
			/*wall.drawBackground(240,10);
			wall.drawBlobs(240,10);
			wall.particles.draw(240,10);*/
			wall.drawFbos(240,10);
			break;
		case 3:
			frameDifference.drawDebug(240,10);
			break;
		default:
			break;
		}

		gui.draw();
	}
	wall.drawOutput(outputOffsetX,outputOffsetY,outputSizeX,outputSizeY);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='h'){
		showGui = !showGui;
	}

	if(key=='f'){
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	wall.particles.addParticle(ofVec2f(x-240,y-10)/ofVec2f((wall.ledSeparationX)*wall.wallWidth,(wall.ledSeparationY)*wall.wallHeight)*ofVec2f(640,480)
				,currentColor);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(button==2){
		currentColor = niceRandomColor();
	}else{
		wall.particles.addParticle(ofVec2f(x-240,y-10)/ofVec2f((wall.ledSeparationX)*wall.wallWidth,(wall.ledSeparationY)*wall.wallHeight)*ofVec2f(640,480)
			,currentColor);
	}
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

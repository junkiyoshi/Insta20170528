#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);
	ofBackground(0);
	ofSetWindowTitle("Sphere");

	this->radius = 250;
}

//--------------------------------------------------------------
void ofApp::update(){
	this->light.setPosition(this->cam.getPosition());
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	//ofEnableLighting();
	//this->light.enable();

	ofVec3f r_location;
	ofVec3f l_location;

	Leap::Frame frame = leap.frame();
	Leap::HandList hands = frame.hands();
	for (int i = 0; i < hands.count(); i++) {
		this->drawHand(hands[i]);
		if (hands[i].isRight()) {
			r_location = ofVec3f(hands[i].palmPosition().x, hands[i].palmPosition().y - ofGetHeight() / 2, hands[i].palmPosition().z);
			r_location.normalize();
			r_location *= 300;
		} else {
			l_location = ofVec3f(hands[i].palmPosition().x, hands[i].palmPosition().y - ofGetHeight() / 2, hands[i].palmPosition().z);
			l_location.normalize();
			l_location *= 300;
		}
	}

	vector<ofVec3f> locations;
	
	int span = 10;
	for (int i = 0; i < 360; i += span) {
		for (int j = 0; j < 180; j += span) {
			int x = radius * cos(i * DEG_TO_RAD) * sin(j * DEG_TO_RAD);
			int y = radius * sin(i * DEG_TO_RAD) * sin(j * DEG_TO_RAD);
			int z = radius * cos(j * DEG_TO_RAD);

			ofVec3f location = ofVec3f(x, y, z);
			
			ofVec3f r_distance = r_location - location;
			ofVec3f l_distance = l_location - location;
			int red = 0;
			int blue = 0;
			if (r_distance.length() < this->radius * 0.8 || l_distance.length() < this->radius * 0.5) { location *= 1.5; }
		
			locations.push_back(location);
		}
	}

	for (ofVec3f& location : locations) {
		for (ofVec3f& s_location : locations) {
			float distance = location.distance(s_location);
			if (location.length() < this->radius && distance < 50) {
				ofLine(location, s_location);
			}
			else if (location.length() > this->radius && distance < 100) {
				ofLine(location, s_location);
			}
		}
		//ofSphere(location, 5);
	}

	cam.end();
}

//--------------------------------------------------------------
void ofApp::drawHand(Leap::Hand hand) {
	Leap::FingerList fingers = hand.fingers();
	for (int j = 0; j < fingers.count(); j++) {
		this->drawFinger(fingers[j]);
	}

	ofPushMatrix();
	ofVec3f palm_point = ofVec3f(hand.palmPosition().x, hand.palmPosition().y - ofGetHeight() / 2, hand.palmPosition().z);
	ofTranslate(palm_point);
	ofSphere(10);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawFinger(Leap::Finger finger) {

	ofVec3f tip_point = ofVec3f(finger.tipPosition().x, finger.tipPosition().y - ofGetHeight() / 2, finger.tipPosition().z);
	ofPushMatrix();
	ofTranslate(tip_point);
	ofSphere(5);
	ofPopMatrix();

	ofVec3f base_point = ofVec3f(tip_point.x + finger.direction().x * finger.length(),// * -1,
		tip_point.y + finger.direction().y * finger.length() - 1,
		tip_point.z + finger.direction().z * finger.length() - 1);
	ofPushMatrix();
	ofTranslate(base_point);
	ofSphere(5);
	ofPopMatrix();

	ofLine(tip_point, base_point);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	int radius = 80;
	bool flag = true;
	for (int x = -225; x <= 225; x += 225) {

		for (int y = -225; y <= 225; y += 225) {

			ofPushMatrix();
			ofTranslate(x, y);

			float noise_seed_x = ofRandom(1000);
			float noise_seed_y = ofRandom(1000);
			float noise_seed_z = ofRandom(1000);
			for (int deg = 0; deg < 360; deg += 10) {

				auto location_1 = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
				auto location_2 = glm::vec3(radius * 0.3 * cos(deg * DEG_TO_RAD), radius * 0.3 * sin(deg * DEG_TO_RAD), 0);

				auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_z, location_1.x * 0.0015, location_1.y * 0.0015, ofGetFrameNum() * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 0, 1));
				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, location_1.x * 0.0015, location_1.y * 0.0015, ofGetFrameNum() * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, location_1.x * 0.0015, location_1.x * 0.0015, ofGetFrameNum() * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
				

				if (true) {

					location_2 = glm::vec4(location_2, 0) * rotation_y * rotation_x;
				}
				else {

					location_1 = glm::vec4(location_1, 0) * rotation_y * rotation_x;
				}

				ofDrawLine(location_1, location_2);

				ofDrawCircle(location_1, 3);
				ofDrawCircle(location_2, 2);
			}

			ofPopMatrix();

			flag = !flag;
		}
	}
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
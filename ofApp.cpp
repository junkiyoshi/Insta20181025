#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");
	
	ofBackground(0);
	ofSetColor(255);

	ofTrueTypeFont font;
	int font_size = 230;
	font.loadFont("fonts/Kazesawa-Bold.ttf", font_size, true, true, true);

	ofFbo fbo;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	string word = "GRID";
	font.drawString(word, font.stringWidth(word) * -0.5, font.stringHeight(word) * 0.5);
	
	fbo.end();

	ofPixels pixels;
	fbo.readToPixels(pixels);

	int span = 10;
	for (int x = 0; x < fbo.getWidth(); x += span) {

		for (int y = 0; y < fbo.getHeight(); y += span) {

			if (pixels.getColor(x, y) != ofColor(0, 0)) {

				this->locations.push_back(ofPoint(x, fbo.getHeight() - y));
			}
		}
	}

	for (int i = 0; i < this->locations.size(); i++) {

		vector<int> next_index = vector<int>();
		for (int j = 0; j < this->locations.size(); j++) {

			if (i == j) { continue; }

			float distance = this->locations[i].distance(this->locations[j]);
			if (distance <= span) {

				next_index.push_back(j);
			}
		}

		this->next_indexes.push_back(next_index);
	}

	this->number_of_targets = 200;
	for (int i = 0; i < this->number_of_targets; i++) {

		this->particles.push_back(Particle(this->locations, this->next_indexes));
	}

	this->src.allocate(ofGetWidth(), ofGetHeight());
	this->dst.allocate(ofGetWidth(), ofGetHeight());
	this->shader.load("shader/shader.vert", "shader/shader.frag");
}
//--------------------------------------------------------------
void ofApp::update() {

	for (Particle& particle : this->particles) { particle.Upate(); }
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<glm::vec2> targets;
	for (int i = 0; i < this->number_of_targets; i++) { targets.push_back(glm::vec2(this->particles[i].location.x, this->particles[i].location.y)); }

	this->dst.begin();
	this->shader.begin();

	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform2fv("targets", &targets[0].x, this->number_of_targets);
	this->shader.setUniformTexture("fbo", this->src.getTexture(), 1);
	this->src.draw(0, 0);

	this->shader.end();
	this->dst.end();

	this->dst.draw(0, 0);
	std::swap(this->src, this->dst);
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
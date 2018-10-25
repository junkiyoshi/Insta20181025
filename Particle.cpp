#include "Particle.h"

//--------------------------------------------------------------
Particle::Particle(vector<ofPoint> locations, vector<vector<int>> next_indexes) {

	this->locations = locations;
	this->next_indexes = next_indexes;

	while (true) {

		this->locations_index = (int)ofRandom(this->locations.size());
		if (this->next_indexes[this->locations_index].size() > 0) {

			this->next_index = this->next_indexes[this->locations_index][(int)ofRandom(this->next_indexes[this->locations_index].size())];
			break;
		}
	}

}

//--------------------------------------------------------------
Particle::~Particle() {

}

//--------------------------------------------------------------
void Particle::Upate() {

	int frame_span = 5;

	if (ofGetFrameNum() % frame_span == 0) {

		this->locations_index = this->next_index;
		this->next_index = this->next_indexes[this->locations_index][(int)ofRandom(this->next_indexes[this->locations_index].size())];
	}

	ofPoint distance = this->locations[this->next_index] - this->locations[this->locations_index];
	this->location = this->locations[this->locations_index] + distance / frame_span * (ofGetFrameNum() % frame_span);
}

//--------------------------------------------------------------
void Particle::Draw() {

}
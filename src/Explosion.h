#pragma once
#include "ofMain.h"

class Explosion {
public:
	bool started_1;
	bool started_2;
	bool started_3;
	bool started_4;
	float timeStamp;
	ofVec2f pos;
	Explosion();
	void start(ofVec2f p);
	void draw(ofImage img_1, ofImage img_2, ofImage img_3, ofImage img_4);
	void update();
};
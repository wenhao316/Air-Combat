#include "Explosion.h"

Explosion::Explosion() {
	started_1 = false;
	started_2 = false;
	started_3 = false;
	started_4 = false;
}

void Explosion::draw(ofImage img_1, ofImage img_2, ofImage img_3, ofImage img_4) {
	if(started_1)
		img_1.draw(pos);
	else if(started_2)
		img_2.draw(pos);
	else if (started_3)
		img_3.draw(pos);
	else if (started_4)
		img_4.draw(pos);
}

void Explosion::update() {
	if (started_1 && ofGetElapsedTimeMillis() - timeStamp > 100) {
		started_1 = false;
		timeStamp = ofGetElapsedTimeMillis();
		started_2 = true;
	}
	else if(started_2 && ofGetElapsedTimeMillis() - timeStamp > 100)
	{
		started_2 = false;
		timeStamp = ofGetElapsedTimeMillis();
		started_3 = true;
	}
	else if (started_3 && ofGetElapsedTimeMillis() - timeStamp > 100)
	{
		started_3 = false;
		timeStamp = ofGetElapsedTimeMillis();
		started_4 = true;
	}
	else if (started_4 && ofGetElapsedTimeMillis() - timeStamp > 100)
	{
		started_4 = false;
		timeStamp = ofGetElapsedTimeMillis();
	}
}

void Explosion::start(ofVec2f p) {
	timeStamp = ofGetElapsedTimeMillis();
	pos = p;
	started_1 = true;
}
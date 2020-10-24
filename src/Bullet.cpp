#include "Bullet.h"

BaseObject::BaseObject() {
	trans = ofVec3f(0,0,0);
	scale = ofVec3f(1, 1, 1);
	rot = 0;
}

void BaseObject::setPosition(ofVec3f pos) {
	trans = pos;
}


// Basic Bullet Object
Bullet::Bullet() {
	speed = 0;
	velocity = ofVec3f(0, 0, 0);
	lifespan = -1;
	birthtime = 0;
	bSelected = false;
	haveImage = false;
	haveSound = false;
	name = "UnamedSprite";
	width = 20;
	height = 20;
}


float Bullet::age() {
	return (ofGetElapsedTimeMillis() - birthtime);
}

void Bullet::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = image.getWidth();
	height = image.getHeight();
}

void Bullet::setSound(ofSoundPlayer s) {
	sound = s;
	haveSound = true;
}

//draw one bullet
void Bullet::draw() {

	ofSetColor(255, 255, 255, 255);

	// draw image centered and add in translation amount
	if (haveImage) {
		image.draw(-width / 2.0 + trans.x, -height / 2.0 + trans.y);
	}
	else {
		// in case no image is supplied, draw something.
		ofNoFill();
		ofSetColor(255, 0, 0);
		ofDrawRectangle(-width / 2.0 + trans.x, -height / 2.0 + trans.y, width, height);
	}
}


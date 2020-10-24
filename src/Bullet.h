#pragma once

#include "ofMain.h"
// This is a base object that all drawable object
class BaseObject {
public:
	BaseObject();
	ofVec2f trans, scale;
	float	rot;
	bool	bSelected;
	void setPosition(ofVec3f);
};

//  Shooter shoot bullet
//	set image sound and velocity
class Bullet : public BaseObject {
public:
	Bullet();
	void draw();
	float age();
	void setImage(ofImage);
	void setSound(ofSoundPlayer);
	float speed;    //   in pixels/sec
	ofVec3f velocity; // in pixels/sec
	ofImage image;
	ofSoundPlayer sound;
	float birthtime;
	float lifespan;
	string name;
	bool haveImage;
	bool haveSound;
	float width, height;
};


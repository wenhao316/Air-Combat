#pragma once
//----------------------------------------------------------------------------------
#include "Bullet.h"
#include "BulletSystem.h"


class Shooter : public BaseObject {
public:
	Shooter(BulletSystem *);
	void draw();
	void update_enemy();
	void update_player();
	void start();
	void stop();
	void setLifespan(float); 
	void setVelocity(ofVec3f);  // pixel/sec
	void setChildImage(ofImage);
	void setChildSound(ofSoundPlayer);
	void setChildSize(float w, float h) { childWidth = w; childHeight = h; }
	void setImage(ofImage);
	void setSound(ofSoundPlayer);
	void setRate(float);
	float maxDistPerFrame();
	BulletSystem *sys;
	float rate;
	ofVec3f velocity;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	ofSoundPlayer childSound;
	ofSoundPlayer sound;
	ofPoint pos;
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	bool haveChildSound;
	bool haveSound;
	float width, height;
	float childWidth, childHeight;
};

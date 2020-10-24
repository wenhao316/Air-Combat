#pragma once
#include "Bullet.h"
#include "Explosion.h"

class BulletSystem {
public:
	void add(Bullet);
	void remove(int);
	void update();
	int removeNear(ofVec3f point, float dist, Explosion *explosion);
	void draw();
	vector<Bullet> bullets;
};

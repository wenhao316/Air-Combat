#include "BulletSystem.h"

//  add a bullet
void BulletSystem::add(Bullet b) {
	bullets.push_back(b);
}

// delete a bullet
// deleted when exceeds lifespan
void BulletSystem::remove(int i) {
	bullets.erase(bullets.begin() + i);
}

// delete bullet after collision
int BulletSystem::removeNear(ofVec3f point, float dist, Explosion *explosion) {
	vector<Bullet>::iterator s = bullets.begin();
	vector<Bullet>::iterator tmp;
	int count = 0;
	while (s != bullets.end()) {
		ofVec3f v = s->trans - point;
		if (v.length() < dist) {
			tmp = bullets.erase(s);
			count++;
			s = tmp;
		}
		else s++;
	}
	if(count)
		explosion->start(point);
	return count;
}


// move bullet
void BulletSystem::update() {

	if (bullets.size() == 0) return;
	vector<Bullet>::iterator s = bullets.begin();
	vector<Bullet>::iterator tmp;
    
	while (s != bullets.end()) {
		if (s->lifespan != -1 && s->age() > s->lifespan) {
			tmp = bullets.erase(s);
			s = tmp;
		}
		else s++;
	}

	//  Move bullets
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].trans += bullets[i].velocity / ofGetFrameRate();
	}
}

//  draw all bullets
void BulletSystem::draw() {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].draw();
	}
}

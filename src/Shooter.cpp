#include "ofMain.h"
#include "Shooter.h"


Shooter::Shooter(BulletSystem *bulletSys) {
	sys = bulletSys;
	lifespan = 3000;    // milliseconds
	started = false;
	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	haveImage = false;
	haveChildSound = false;
	haveSound = false;
	velocity = ofVec3f(100, 100, 0);
	drawable = true;
	width = 50;
	height = 50;
	childWidth = 10;
	childHeight = 10;
}

void Shooter::draw() {
	if (drawable) {
		image.draw(-image.getWidth() / 2.0 + trans.x, -image.getHeight() / 2.0 + trans.y);
	}

	sys->draw();
}

//  Update enemy shooter
void Shooter::update_enemy() {
	if (!started) return;
	
	float time = ofGetElapsedTimeMillis();
	if ((time - lastSpawned) > (1000.0 / rate)) {
		// load a bullet
		Bullet bullet;
		if (haveChildImage) bullet.setImage(childImage);
		if (haveChildSound) {
			bullet.setSound(childSound);
			bullet.sound.play();
		}
		bullet.velocity = velocity;
		bullet.lifespan = lifespan;
		bullet.setPosition(trans);
		bullet.birthtime = time;
		bullet.width = childWidth;
		bullet.height = childHeight;
		sys->add(bullet);
		lastSpawned = time;
	}
	
	sys->update();
}

//  Update player.
void Shooter::update_player() {
	if (!started) return;

	// load a bullet
	Bullet bullet;
	if (haveChildImage) bullet.setImage(childImage);
	if (haveChildSound) {
		bullet.setSound(childSound);
		bullet.sound.play();
	}
	bullet.velocity = velocity;
	bullet.lifespan = lifespan;
	bullet.setPosition(trans);
	bullet.birthtime = ofGetElapsedTimeMillis();
	bullet.width = childWidth;
	bullet.height = childHeight;
	sys->add(bullet);

	sys->update();
}


// Start/Stop the Shooter.
void Shooter::start() {
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
}

void Shooter::stop() {
	started = false;
}


void Shooter::setLifespan(float life) {
	lifespan = life;
}

void Shooter::setVelocity(ofVec3f v) {
	velocity = v;
}

void Shooter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
	childWidth = img.getWidth();
	childHeight = img.getHeight();
}

void Shooter::setChildSound(ofSoundPlayer s) {
	childSound = s;
	haveChildSound= true;
}

void Shooter::setImage(ofImage img) {
	image = img;
	haveImage = true;
}

void Shooter::setSound(ofSoundPlayer s) {
	sound = s;
}

void Shooter::setRate(float r) {
	rate = r;
}

float Shooter::maxDistPerFrame() {
	return  velocity.length() / ofGetFrameRate();
}

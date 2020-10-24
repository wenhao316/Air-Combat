#include "ofApp.hpp"

void ofApp::setup() {
	//update screen
	ofSetVerticalSync(true);
    game_state = "start";
    score = 0;


	player_image.load("images/player.png");
	enemy_1_image.load("images/enemy_1.png");
	enemy_2_image.load("images/enemy_2.png");
	invader_emitter_image.load("images/death_star.png");
	player_bullet_image.load("images/player_bullet.png");
	life.load("images/life.png");

	intro_music.load("sounds/intro_music.wav");
	player_bullet_sound.load("sounds/laser.wav");
	player_bullet_sound.setMultiPlay(true);
	enemy_bullet_sound.load("sounds/Ror_laser.wav");
	
	enemy1_down1.load("images/enemy1_down1.png");
	enemy1_down2.load("images/enemy1_down2.png");
	enemy1_down3.load("images/enemy1_down3.png");
	enemy1_down4.load("images/enemy1_down4.png");

	enemy2_down1.load("images/enemy2_down1.png");
	enemy2_down2.load("images/enemy2_down2.png");
	enemy2_down3.load("images/enemy2_down3.png");
	enemy2_down4.load("images/enemy2_down4.png");

	//initialize player at the center of the screen
	player_start.set(ofGetWidth() / 2, ofGetHeight() / 2);
	player_1.setup(&player_image, player_start);

	start_screen.load("images/start_screen.png");
	end_screen.load("images/end_screen.png");
	score_font.load("fonts/steelworks_vintage.otf", 48);

	// Record when the game starts
	gameStartTime = ofGetElapsedTimeMillis();

	// create player shooter
	player_1Gun = new Shooter(new BulletSystem());


	player_1Gun->setPosition(ofPoint(player_1.pos));
	player_1Gun->setVelocity(ofVec3f(0, -1000, 0));
	player_1Gun->setRate(1);
	player_1Gun->setLifespan(1000);
	player_1Gun->setChildImage(player_bullet_image);
	player_1Gun->setChildSound(player_bullet_sound);

	//enemy_1
	enemy_1 = new Shooter(new BulletSystem());
	enemy_1->setImage(invader_emitter_image);
	enemy_1->setChildImage(enemy_1_image);

	enemy_1->setPosition(ofVec3f(ofGetWindowWidth() / 2, 50, 0));
	enemy_1->velocity.set(0, 400, 0);
	enemy_1->setLifespan(5000);
	enemy_1->setRate(1);
	enemy_1->setChildSize(20, 20);


	enemy_2 = new Shooter(new BulletSystem());
	enemy_2->setImage(invader_emitter_image);
	enemy_2->setChildImage(enemy_2_image);

	enemy_2->setPosition(ofVec3f(ofGetWindowWidth() / 2, 50, 0));
	enemy_2->velocity.set(0, 600, 0);
	enemy_2->setRate(10);
	enemy_2->setLifespan(5000);
	enemy_2->setChildSize(20, 20);

	enemy_2->start();

	//create explosion
	Explosion explosion_1 ;
	Explosion explosion_2 ;
	Explosion explosion_p ;

	// start
	enemy_1->start();
	player_1Gun->start();

	background.setup();
	
	ofBackground(0, 0, 0); 
}

//--------------------------------------------------------------
void ofApp::update() {
    if (game_state == "start") {
        
    } else if (game_state == "game") {

	//update player's bullet system
	player_1Gun->sys->update();
	player_1Gun->setPosition(ofPoint(player_1.pos));

	//update enemy's bullet system
	enemy_1->update_enemy();
	if (score > 20)
		enemy_2->update_enemy();

	
	//check Collision and explosion
	checkCollisions();
	explosion_1.update();
	explosion_2.update();
	

	ofVec3f v = enemy_1->velocity;
	enemy_1->setVelocity(ofVec3f(ofRandom(-v.y /2, v.y /2), v.y, v.z));
	enemy_2->setVelocity(ofVec3f(ofRandom(-v.y / 2, v.y / 2), v.y, v.z));

        for (int i = 1; i < 20; i++) {
            if (score % 5 == i) {
                enemy_1 -> setRate(i + 1); player_1Gun -> setRate(i + 1);
            }
        }
        if (score > 100) {
            enemy_1 -> setRate(10000000);
        }
//    if (score > 5) { enemy_1->setRate(2); player_1Gun->setRate(2); }
//    if (score > 10) { enemy_1->setRate(3); }
//    if (score > 20) { enemy_1->setRate(4); player_1Gun->setRate(3);}
//    if (score > 30) { enemy_1->setRate(5); }
//    if (score > 40) { enemy_1->setRate(6); player_1Gun->setRate(4); }
//    if (score > 50) { enemy_1->setRate(7); }
//    if (score > 60) { enemy_1->setRate(8); }
//    if (score > 70) { enemy_1->setRate(9); player_1Gun->setRate(5); }
//    if (score > 80) { enemy_1->setRate(10); }
//    if (score > 90) { enemy_1->setRate(11); }
//    if (score > 100) { enemy_1->setRate(12); player_1Gun->setRate(6); }
//    if (score > 200) { enemy_1->setRate(14); player_1Gun->setRate(7); }

		
	player_1.update();
    withinBounds(&player_1.pos);
    } else if (game_state == "end") { 
        
    }
               
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (game_state == "start") {
        start_screen.draw(0, 0);
    } else if (game_state == "game") {
		
		background.draw();
		
		player_1Gun->draw();
		enemy_1->draw();
		if (score > 20)
			enemy_2->draw();
		

        player_1.draw();

		explosion_1.draw(enemy1_down1, enemy1_down2, enemy1_down3, enemy1_down4);
		explosion_2.draw(enemy2_down1, enemy2_down2, enemy2_down3, enemy2_down4);

        drawScore();
        drawLives();
    } else if (game_state == "end") {
        end_screen.draw(0, 0);
		drawScore();
    }
}


void ofApp::checkCollisions() {


	float collisionDist = player_1Gun->childHeight / 2 + enemy_1->childHeight / 2;
	float nearPlayer = player_1.img->getHeight() / 2 + enemy_1->childHeight / 2;
	float nearPlayer2 = player_1.img->getHeight() / 2 + enemy_2->childHeight / 2;
	vector<Bullet>::iterator i = enemy_1->sys->bullets.begin();


	// remove bullets within removeNear range
	for (auto g = player_1Gun->sys->bullets.begin(); g != player_1Gun->sys->bullets.end(); ++g) {
		int n = enemy_1->sys->removeNear(g->trans, collisionDist, &explosion_1) + enemy_2->sys->removeNear(g->trans, collisionDist, &explosion_2);
		if (n > 0) {
			score += n;
		}
	}

	for (int i = 0; i < enemy_1->sys->bullets.size(); i++) {
		int n = enemy_1->sys->removeNear(player_1.pos, nearPlayer, &explosion_1) + enemy_2->sys->removeNear(player_1.pos, nearPlayer2, &explosion_2);
		if (n > 0) {
			player_1.lives -= n;
		}
		if (player_1.lives == 0) {
			game_state = "end";
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (game_state == "game") {
        if (key == OF_KEY_LEFT)
            player_1.is_left_pressed = true;
        if (key == OF_KEY_RIGHT)
            player_1.is_right_pressed = true; 
        if (key == OF_KEY_UP)
            player_1.is_up_pressed = true;
        if (key == OF_KEY_DOWN)
            player_1.is_down_pressed = true;
        if (key == ' ') {
			player_1Gun->update_player();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (game_state == "start" && key == ' ') {
        game_state = "game";
        //level_controller.setup(ofGetElapsedTimeMillis());
    } else if (game_state == "game") {
        if (key == OF_KEY_LEFT)
            player_1.is_left_pressed = false;
        if (key == OF_KEY_RIGHT)
            player_1.is_right_pressed = false;
        if (key == OF_KEY_UP)
            player_1.is_up_pressed = false;
        if (key == OF_KEY_DOWN)
            player_1.is_down_pressed = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
	button_last = ofPoint(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	ofPoint mouse_cur = ofPoint(x, y);

	if (this->player_1.clickable.inside(x, y)) {
		ofVec2f delta = (mouse_cur - button_last);
		player_1.pos += delta;
		button_last = mouse_cur;
	}
}

//--------------------------------------------------------------
void ofApp::withinBounds(ofPoint* point) {

	if (0 > point->x) {
		point->x = 0;
	}
	if (point->x > ofGetWidth()) {
		point->x = ofGetWidth();
	}
	if (0 > point->y) {
		point->y = 0;
	}
	if (point->y > ofGetWindowHeight()) {
		point->y = ofGetWindowHeight();
	}
}

//--------------------------------------------------------------
void ofApp::drawLives() {
	for (int i = 0; i < player_1.lives; i++) {
		life.draw(ofGetWidth() - (i * player_image.getWidth()) - 100, 900);
	}
}

//--------------------------------------------------------------
void ofApp::drawScore() {
	if (game_state == "game") {
		score_font.drawString(ofToString(score), 30, 72);
	}
	else if (game_state == "end") {
		float w = score_font.stringWidth(ofToString(score));
		score_font.drawString(ofToString(score), ofGetWidth() / 2 - w / 2, ofGetHeight() / 2 + 100);
	}
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::resetGame() {
    
}

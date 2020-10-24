#include "ofApp.hpp"

//http://openframeworks.cc/ofBook/chapters/game_design.html

int main( ){
	ofSetupOpenGL(540, 960, OF_WINDOW);			// <-------- setup the GL context

	ofRunApp(new ofApp());
}

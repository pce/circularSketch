#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    kickSound.load("kick.wav");
    snareSound.load("snare.wav");
    hihatSound.load("hihat.wav");
    openHihatSound.load("openhihat.wav");
    rimSound.load("rim.wav");
    
    
    // Assuming a sequencer with 16 steps, centered at (ofGetWidth() / 2, ofGetHeight() / 2), with a radius of 100
    beatSequencer = CircularSequencer(16, ofPoint(ofGetWidth() / 2, ofGetHeight() / 2), 100);

    std::vector<ofSoundPlayer*> soundPlayers = { &kickSound, &snareSound, &hihatSound };
    beatSequencer.setup(soundPlayers);
    
    beatSequencer.setBPM(130);
    
    // Set up steps for each track
    // Kick: 1,0,0,0,1,0,0,0,1 ...
    beatSequencer.setStep(0, 0, true);
    beatSequencer.setStep(0, 4, true);
    beatSequencer.setStep(0, 8, true);

    // Snare: 0,0,0,0,1,0,0,0,0 ...
    beatSequencer.setStep(1, 4, true);

    // HiHat: 0,0,1,0,0, ...
    for (int i = 2; i < 16; i += 2) {
        beatSequencer.setStep(2, i, true);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    beatSequencer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    beatSequencer.draw();
    chordSequencer.draw();
    bassSequencer.draw();
    melodySequencer.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    beatSequencer.mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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

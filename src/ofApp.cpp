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
        
    gui.setup("Euclidean Rhythms");
    gui.add(kickK.setup("Kick K", 1, 1, 16)); // Default value, min, max
    gui.add(kickN.setup("Kick N", 8, 1, 16));
    gui.add(snareK.setup("Snare K", 1, 1, 16));
    gui.add(snareN.setup("Snare N", 8, 1, 16));
    gui.add(hihatK.setup("HiHat K", 1, 1, 16));
    gui.add(hihatN.setup("HiHat N", 8, 1, 16));
    
    // Euclidean parameters
    kickK.addListener(this, &ofApp::onKickKChange);
    kickN.addListener(this, &ofApp::onKickNChange);
    snareK.addListener(this, &ofApp::onSnareKChange);
    snareN.addListener(this, &ofApp::onSnareNChange);
    hihatK.addListener(this, &ofApp::onHihatKChange);
    hihatN.addListener(this, &ofApp::onHihatNChange);
}

//--------------------------------------------------------------
void ofApp::update(){
    float currentTime = ofGetElapsedTimef();
    if (updatePending && currentTime - lastSliderAdjustmentTime > debounceDelay) {
        // Perform rhythm updates for all tracks
        beatSequencer.updateRhythm(0, kickK, kickN); // For kick
        beatSequencer.updateRhythm(1, snareK, snareN); // For snare
        beatSequencer.updateRhythm(2, hihatK, hihatN); // For hi-hat

        updatePending = false; // Reset the flag
    }
    beatSequencer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    beatSequencer.draw();
    chordSequencer.draw();
    bassSequencer.draw();
    melodySequencer.draw();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
    kickK.removeListener(this, &ofApp::onKickKChange);
    kickN.removeListener(this, &ofApp::onKickNChange);
    snareK.removeListener(this, &ofApp::onSnareKChange);
    snareN.removeListener(this, &ofApp::onSnareKChange);
    hihatK.removeListener(this, &ofApp::onHihatKChange);
    hihatN.removeListener(this, &ofApp::onHihatNChange);
}

//--------------------------------------------------------------

void ofApp::onSliderChange() {
    lastSliderAdjustmentTime = ofGetElapsedTimef();
    updatePending = true;
}

void ofApp::onKickKChange(int& k) {
    onSliderChange();
}

void ofApp::onKickNChange(int& n) {
    onSliderChange();
}

void ofApp::onSnareKChange(int& k) {
    onSliderChange();
}

void ofApp::onSnareNChange(int& n) {
    onSliderChange();
}

void ofApp::onHihatKChange(int& k) {
    onSliderChange();
}

void ofApp::onHihatNChange(int& n) {
    onSliderChange();
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

#include "ofApp.h"


// opApp is the ViewModel

//--------------------------------------------------------------
void ofApp::setup(){

    // Beat Sequencer
    kickSound.load("kick.wav");
    snareSound.load("snare.wav");
    hihatSound.load("hihat.wav");
    openHihatSound.load("openhihat.wav");
    rimSound.load("rim.wav");
        
    // Assuming a sequencer with 16 steps, centered at (ofGetWidth() / 2, ofGetHeight() / 2), with a radius of 100
    
    drumSequencerPosition = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
    int drumRadius = 100;
    
    drumSequencer = DrumSequencer(16);

    std::vector<ofSoundPlayer*> soundPlayers = { &kickSound, &snareSound, &hihatSound };
    drumSequencer.setup(soundPlayers);
    
    drumSequencer.setBPM(130);
    
    // Set up steps for each track
    // Kick: 1,0,0,0,1,0,0,0,1 ...
    drumSequencer.setStep(0, 0, true);
    drumSequencer.setStep(0, 4, true);
    drumSequencer.setStep(0, 8, true);

    // Snare: 0,0,0,0,1,0,0,0,0 ...
    drumSequencer.setStep(1, 4, true);

    // HiHat: 0,0,1,0,0, ...
    for (int i = 2; i < 16; i += 2) {
        drumSequencer.setStep(2, i, true);
    }
        
    // Chord Sequencer setup    
    chordSequencerPosition = ofPoint(padding + chordSequencerRadius, padding + chordSequencerRadius);
    chordSequencer = ChordSequencer(16);  // Assuming ChordSequencer has a constructor taking the total steps
    //    chordSequencer.setup(&chordSound);  // Assuming setup for a single sound player
//    chordSequencer.setup(soundPlayers);

    
    
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
        drumSequencer.updateRhythm(0, kickK, kickN); // For kick
        drumSequencer.updateRhythm(1, snareK, snareN); // For snare
        drumSequencer.updateRhythm(2, hihatK, hihatN); // For hi-hat

        updatePending = false; // Reset the flag
    }
    drumSequencer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    drumSequencerView.draw(drumSequencer, drumSequencerPosition, drumSequencerRadius);
    chordSequencerView.draw(chordSequencer, chordSequencerPosition, chordSequencerRadius);

//    bassSequencer.draw();
//    melodySequencer.draw();
    
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
    
    // beatSequencer.
    //    if (ofDist(x, y, toggleButtonCenter.x, toggleButtonCenter.y) <= toggleButtonRadius) {
    //        isRunning = !isRunning; // Toggle the run state
    //    }
    
    int toggleButtonRadius = 10;
    // Example: Checking if the mouse click is within a circular toggle button at the center of the drum sequencer
    float distance = ofDist(x, y, drumSequencerPosition.x, drumSequencerPosition.y);
    if (distance <= toggleButtonRadius) {
        drumSequencer.setRunning(!drumSequencer.isRunning());
    }

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
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    // Update sequencer position using chordSequencerRadius and padding
//    ofPoint chordSequencerCenter(padding + chordSequencerRadius, padding + chordSequencerRadius);
//    drumSequencerView.setPosition(chordSequencerCenter);
//    chordSequencerView.setPosition(chordSequencerCenter);
}

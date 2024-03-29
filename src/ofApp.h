#pragma once

#include "ofMain.h"
#include "CircularSequencerView.hpp"
#include "DrumSequencer.hpp"
#include "ChordSequencer.hpp"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
    
    private:
    
        DrumSequencer drumSequencer;
        ChordSequencer chordSequencer;
        // BassSequencer bassSequencer;
        // MelodySequencer melodySequencer;

        CircularSequencerView drumSequencerView;
        CircularSequencerView chordSequencerView;
        // CircularSequencerView bassSequencerView;
        // CircularSequencerView melodySequencerView;

        ofPoint drumSequencerPosition; // Position for the drum sequencer view
        ofPoint chordSequencerPosition; // Position for the chord sequencer view

        // Radius of the sequencers, adjustable at runtime
        float drumSequencerRadius = 100;
        float chordSequencerRadius = 100;

        float padding = 10; // Padding from the edge, adjustable at runtime


        // beat sequencer
        ofSoundPlayer kickSound, snareSound, hihatSound, openHihatSound, rimSound;
        // sound players for chords, bass, and melody
        ofSoundPlayer bassSound;
        ofSoundPlayer melodySound;
        ofSoundPlayer chordSound;

    
        ofxPanel gui;
        ofxIntSlider kickK, kickN; // Euclidean parameters for kick
        ofxIntSlider snareK, snareN; // Euclidean parameters for snare
        ofxIntSlider hihatK, hihatN; // Euclidean parameters for hi-hat
    
        // debouce Update rhythm (not beatSequencer.updateRhythm(0, k, kickN))
        void onSliderChange();
        void onKickKChange(int& k);
        void onKickNChange(int& n);
        void onSnareKChange(int& k);
        void onSnareNChange(int& n);
        void onHihatKChange(int& k);
        void onHihatNChange(int& n);

        float lastSliderAdjustmentTime = 0; // Timestamp of the last slider adjustment
        bool updatePending = false; // Whether a rhythm update is pending
        const float debounceDelay = 0.5; // Debounce delay in seconds

};

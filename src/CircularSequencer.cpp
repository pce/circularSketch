//
//  CircularSequencer.cpp
//  circularSketch
//
//  Created by pce on 06.02.24.
//

#include "CircularSequencer.hpp"


CircularSequencer::CircularSequencer()
: totalSteps(16), center(ofPoint(0, 0)), radius(100) {
    // Initialize tracks with the default number of steps
    for (int i = 0; i < 3; ++i) { // 3 tracks: Kick, Snare, HiHat
        Track track;
        track.steps.resize(totalSteps, false);
        tracks.push_back(track);
    }
}

CircularSequencer::CircularSequencer(int totalSteps, ofPoint center, float radius)
: totalSteps(totalSteps), center(center), radius(radius) {
    // Initialize tracks with the specified number of steps
    for (int i = 0; i < 3; ++i) { // 3 tracks: Kick, Snare, HiHat
        Track track;
        track.steps.resize(totalSteps, false);
        tracks.push_back(track);
    }
}



void CircularSequencer::setup(float x, float y, float radius) {
    // Set up your sequencer (position, size, etc.)
}
void CircularSequencer::setup() {
    // Set up your sequencer (position, size, etc.)
}
void CircularSequencer::setup(const std::vector<ofSoundPlayer*>& soundPlayers) {
    sounds = soundPlayers; // Assume the size of soundPlayers matches the number of tracks
}

void CircularSequencer::setBPM(int bpm) {
    this->bpm = bpm;
    stepDuration = 60.0 / (bpm * 4); // Calculate step duration based on BPM
}



void CircularSequencer::draw() {
    // Draw the sequencer using OF drawing functions
    for (int trackIndex = 0; trackIndex < tracks.size(); ++trackIndex) {
        for (int step = 0; step < totalSteps; ++step) {
            float angle = ofDegToRad((360.0 / totalSteps) * step);
            float x = center.x + cos(angle) * (radius + trackIndex * 15); // Slightly offset each track
            float y = center.y + sin(angle) * (radius + trackIndex * 15);

            if (tracks[trackIndex].steps[step]) {
                ofSetColor(ofColor::red); // Highlight active steps
            } else {
                ofSetColor(ofColor::white);
            }
            ofDrawSphere(x, y, 0, 5); // Draw step as a small sphere
        }
    }
    // Draw toggle button
    toggleButtonCenter = center; // Position the button in the center
    ofSetColor(isRunning ? ofColor::green : ofColor::red);
    ofDrawCircle(toggleButtonCenter, toggleButtonRadius);
}

void CircularSequencer::setStep(int track, int step, bool active) {
    if (track >= 0 && track < tracks.size() && step >= 0 && step < totalSteps) {
        tracks[track].steps[step] = active;
    }
}


bool CircularSequencer::checkIntersection(CircularSequencer other) {
    // Implement intersection logic
    // Return true if this sequencer intersects with another
    return true;
}


void CircularSequencer::mousePressed(int x, int y) {
    // Check if the click is within the toggle button
    if (ofDist(x, y, toggleButtonCenter.x, toggleButtonCenter.y) <= toggleButtonRadius) {
        isRunning = !isRunning; // Toggle the run state
    }
}

void CircularSequencer::update() {
    if (!isRunning) return;

    float currentTime = ofGetElapsedTimef();
    if (currentTime - lastStepTime >= stepDuration) {
        for (int trackIndex = 0; trackIndex < tracks.size(); ++trackIndex) {
            if (tracks[trackIndex].steps[currentStep] && sounds[trackIndex] != nullptr) {
                sounds[trackIndex]->play(); // Play the sound for the active step
            }
        }

        currentStep = (currentStep + 1) % totalSteps;
        lastStepTime = currentTime;
    }}


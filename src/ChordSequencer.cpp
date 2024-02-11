//
//  ChordSequencer.cpp
//  circularSketch
//
//  Created by pce on 08.02.24.
//

#include "ChordSequencer.hpp"


ChordSequencer::ChordSequencer()
: BaseSequencer(16) {
}

ChordSequencer::ChordSequencer(int totalSteps) : BaseSequencer(totalSteps) {
    // Initialize tracks and other necessary members
    for (int i = 0; i < numberOfTracks; ++i) {
        Track track;
        track.steps.resize(totalSteps, false);
        tracks.push_back(track);
    }
    // Initialize pitch vectors or other necessary members
}

void ChordSequencer::setup(const std::vector<ofSoundPlayer*>& soundPlayers) {
    sounds = soundPlayers; // Store the provided sound player pointers
}


void ChordSequencer::setStep(int track, int step, bool active) {
    if (track >= 0 && track < tracks.size() && step >= 0 && step < totalSteps) {
        tracks[track].steps[step] = active;
    }
}

bool ChordSequencer::getStepState(int track, int step) const {
    // Assuming 'tracks' is a vector of Track objects and each Track has a 'steps' vector<bool>
    return this->tracks[track].steps[step];
}


void ChordSequencer::update() {
    // Example implementation
    if (!isRunning()) return;

    float currentTime = ofGetElapsedTimeMillis() / 1000.0; // Assuming a function to get elapsed time in seconds
    if (currentTime - lastUpdateTime >= stepDuration) {
        // Update logic here
        currentStep = (currentStep + 1) % totalSteps;
        lastUpdateTime = currentTime;
    }
}

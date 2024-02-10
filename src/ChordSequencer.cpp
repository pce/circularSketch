//
//  ChordSequencer.cpp
//  circularSketch
//
//  Created by pce on 08.02.24.
//

#include "ChordSequencer.hpp"

ChordSequencer::ChordSequencer(int totalSteps, ofPoint center, float radius)
: totalSteps(totalSteps), center(center), radius(radius) {
    // Initialization code for BaseSequencer...
}

int ChordSequencer::getTotalSteps() const {
    return this->totalSteps;
}

bool ChordSequencer::getStepState(int track, int step) const {
    // Assuming 'tracks' is a vector of Track objects and each Track has a 'steps' vector<bool>
    return this->tracks[track].steps[step];
}

int ChordSequencer::getNumberOfTracks() const {
    return this->tracks.size();
}


int ChordSequencer::getCurrentStep() const {
    return this->currentStep; // Assuming 'currentStep' tracks the current step
}


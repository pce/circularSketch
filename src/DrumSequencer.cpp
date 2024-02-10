//
//  DrumSequencer.cpp
//  DrumSketch
//
//  Created by pce on 06.02.24.
//

#include "DrumSequencer.hpp"

/*
DrumSequencer::DrumSequencer()
: totalSteps(16), center(ofPoint(0, 0)), radius(100) {
    // Initialize tracks with the default number of steps
    for (int i = 0; i < 3; ++i) { // 3 tracks: Kick, Snare, HiHat
        Track track;
        track.steps.resize(totalSteps, false);
        tracks.push_back(track);
        rhythms.push_back(std::vector<bool>(totalSteps, false)); // Initialize rhythm vectors
    }
}
*/

DrumSequencer::DrumSequencer()
: BaseSequencer(16) {

}

DrumSequencer::DrumSequencer(int totalSteps)
 : BaseSequencer(totalSteps) {
    // Initialize tracks and rhythms with the specified number of steps
    for (int i = 0; i < numberOfTracks; ++i) { // Assuming 3 tracks for Kick, Snare, HiHat
        Track track;
        track.steps.resize(totalSteps, false);
        tracks.push_back(track);
        // rhythms.push_back(std::vector<bool>(totalSteps, false));
        
    }
    // Initialize rhythm vectors
    for (int i = 0; i < numberOfTracks; ++i) {
        std::vector<bool> rhythm(totalSteps, false); // Initialize a rhythm pattern with all 'false'
        rhythms.push_back(rhythm);
    }
    
}

void DrumSequencer::setup(const std::vector<ofSoundPlayer*>& soundPlayers) {
    sounds = soundPlayers; // Assume the size of soundPlayers matches the number of tracks
}

void DrumSequencer::setStep(int track, int step, bool active) {
    if (track >= 0 && track < tracks.size() && step >= 0 && step < totalSteps) {
        tracks[track].steps[step] = active;
    }
}


void DrumSequencer::mousePressed(int x, int y) {
    // Check if the click is within the toggle button
    if (ofDist(x, y, toggleButtonCenter.x, toggleButtonCenter.y) <= toggleButtonRadius) {
        isRunning = !isRunning; // Toggle the run state
    }
}

void DrumSequencer::update() {
    if (!isRunning) return;

    float currentTime = ofGetElapsedTimef();
    if (currentTime - lastStepTime >= stepDuration) {
        for (int trackIndex = 0; trackIndex < tracks.size(); ++trackIndex) {
            
            if (trackIndex >= 0 && trackIndex < tracks.size() &&  tracks[trackIndex].steps[currentStep] && sounds[trackIndex] != nullptr) {
                sounds[trackIndex]->play(); // Play the sound for the active step
            }
        }

        currentStep = (currentStep + 1) % totalSteps;
        lastStepTime = currentTime;
    }
}

void DrumSequencer::updateRhythm(int track, int k, int n) {
    if (track < 0 || track >= tracks.size()) return;

    // Generate the new rhythm
    std::vector<bool> newRhythm = generateEuclideanRhythm(k, n);

    // Resize the track steps vector if necessary
    if (tracks[track].steps.size() != totalSteps) {
        tracks[track].steps.resize(totalSteps, false);
    }

    // Update the corresponding track's steps with the new rhythm
    int stepsToUpdate = std::min(n, totalSteps); // Ensure we don't go out of bounds
    for (int i = 0; i < stepsToUpdate; ++i) {
        tracks[track].steps[i] = newRhythm[i];
    }

    // Fill the remaining steps with false if the new rhythm is shorter than the total steps
    for (int i = stepsToUpdate; i < totalSteps; ++i) {
        tracks[track].steps[i] = false;
    }
}



int DrumSequencer::getTotalSteps() const {
    return this->totalSteps;
}

bool DrumSequencer::getStepState(int track, int step) const {
    // Assuming 'tracks' is a vector of Track objects and each Track has a 'steps' vector<bool>
    return this->tracks[track].steps[step];
}

int DrumSequencer::getCurrentStep() const {
    return this->currentStep; // Assuming 'currentStep' tracks the current step
}




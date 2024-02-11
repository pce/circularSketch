//
//  DrumSequencer.cpp
//  DrumSketch
//
//  Created by pce on 06.02.24.
//

#include "DrumSequencer.hpp"


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
        std::vector<bool> rhythm(totalSteps, false);
        rhythms.push_back(rhythm);
    }
    
}


void DrumSequencer::setup(const std::vector<ofSoundPlayer*>& soundPlayers) {
    sounds = soundPlayers; // Store the provided sound player pointers
}


void DrumSequencer::setStep(int track, int step, bool active) {
    if (track >= 0 && track < tracks.size() && step >= 0 && step < totalSteps) {
        tracks[track].steps[step] = active;
    }
}


void DrumSequencer::update() {
    if (!isRunning()) return;

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

bool DrumSequencer::getStepState(int track, int step) const {
    if (track >= 0 && track < tracks.size() && step >= 0 && step < totalSteps) {
        return tracks[track].steps[step];
    }
    return false; // Return false or handle error for out-of-bounds access
}

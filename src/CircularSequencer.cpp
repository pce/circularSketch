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
        rhythms.push_back(std::vector<bool>(totalSteps, false)); // Initialize rhythm vectors
    }
}


CircularSequencer::CircularSequencer(int totalSteps, ofPoint center, float radius)
: totalSteps(totalSteps), center(center), radius(radius) {
    // Initialize tracks and rhythms with the specified number of steps
    for (int i = 0; i < 3; ++i) { // Assuming 3 tracks for Kick, Snare, HiHat
        Track track;
        track.steps.resize(totalSteps, false);
        tracks.push_back(track);
        rhythms.push_back(std::vector<bool>(totalSteps, false)); // Initialize rhythm vectors
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

            if (step == currentStep) {
                     ofSetColor(ofColor::yellow); // Use a lighter color for the current step
            } else if (tracks[trackIndex].steps[step]) {
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
            
            if (trackIndex >= 0 && trackIndex < tracks.size() &&  tracks[trackIndex].steps[currentStep] && sounds[trackIndex] != nullptr) {
                sounds[trackIndex]->play(); // Play the sound for the active step
            }
        }

        currentStep = (currentStep + 1) % totalSteps;
        lastStepTime = currentTime;
    }
}

void CircularSequencer::updateRhythm(int track, int k, int n) {
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



std::vector<bool> CircularSequencer::generateEuclideanRhythm(int k, int n) {
    std::vector<std::vector<bool>> buckets(n, std::vector<bool>());

    for (int i = 0; i < k; ++i) {
        buckets[i].push_back(true); // Fill the first k buckets with a "one"
    }

    int ticks = 0;
    while (true) {
        ticks++;
        bool emptyBucket = false;
        for (int i = 0; i < n; ++i) {
            if (buckets[i].empty()) {
                emptyBucket = true;
                break;
            }
        }

        if (emptyBucket) break;

        std::vector<bool> firstNotEmptyBucket = buckets[0];
        for (int i = 0; i < n - 1; ++i) {
            buckets[i] = buckets[i + 1];
        }
        buckets[n - 1].clear();

        for (bool pulse : firstNotEmptyBucket) {
            buckets[n - 1].push_back(pulse);
        }
        
        if (ticks > 1000) {
            break;
        }
    }

    std::vector<bool> rhythm;
    for (auto& bucket : buckets) {
        rhythm.insert(rhythm.end(), bucket.begin(), bucket.end());
    }

    return rhythm;
}




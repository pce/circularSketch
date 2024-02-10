//
//  BaseSequencer.cpp
//  circularSketch
//
//  Created by pce on 08.02.24.
//

#include "BaseSequencer.hpp"

BaseSequencer::BaseSequencer(int totalSteps, ofPoint center, float radius)
: totalSteps(totalSteps), center(center), radius(radius) {
    // Initialize tracks and rhythms with the specified number of steps
    //    for (int i = 0; i < 3; ++i) { // Assuming 3 tracks for Kick, Snare, HiHat
    //        Track track;
    //        track.steps.resize(totalSteps, false);
    //        tracks.push_back(track);
    //        rhythms.push_back(std::vector<bool>(totalSteps, false)); // Initialize rhythm vectors
    //    }
}


void BaseSequencer::setBPM(int bpm) {
    this->bpm = bpm;
    stepDuration = 60.0 / (bpm * 4); // Calculate step duration based on BPM
}

bool BaseSequencer::isSequencerRunning() const {
    return this->isRunning;    
}



std::vector<bool> BaseSequencer::generateEuclideanRhythm(int k, int n) {
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


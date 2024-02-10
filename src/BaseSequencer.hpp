//
//  BaseSequencer.hpp
//  circularSketch
//
//  Created by pce on 08.02.24.
//

#ifndef BaseSequencer_hpp
#define BaseSequencer_hpp

#include <stdio.h>

#include "ofMain.h"

class BaseSequencer {
public:
    struct Track {
        std::vector<bool> steps;
    };
    BaseSequencer(int totalSteps, ofPoint center, float radius);
    virtual ~BaseSequencer() {}
    virtual void setStep(int step, bool active) = 0;
    virtual void update();
    virtual void draw();
    virtual void setup(const std::vector<ofSoundPlayer*>& soundPlayers);
    // accessors
    virtual int getTotalSteps() const = 0;
    virtual bool getStepState(int track, int step) const = 0;
    virtual int getCurrentStep() const = 0;
    virtual int getNumberOfTracks() const = 0;

    // implemented
    bool isSequencerRunning() const;
    void setBPM(int bpm);

protected:
    int bpm = 130; // Default BPM
    float stepDuration = 0.5f; // Duration of each step in seconds
    bool isRunning = false; // Run state of the sequencer

    std::vector<bool> steps;
    ofPoint center;
    float radius;
    int totalSteps;
    
    std::vector<Track> tracks; // For Example 0: Kick, 1: Snare, 2: HiHat

    // Euclidean rhythm generator
    static std::vector<bool> generateEuclideanRhythm(int k, int n);
};


#endif /* BaseSequencer_hpp */

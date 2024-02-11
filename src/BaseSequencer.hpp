#ifndef BaseSequencer_hpp
#define BaseSequencer_hpp

#include <stdio.h>
#include "ofMain.h"

class BaseSequencer {
public:
    struct Track {
        std::vector<bool> steps;
    };

    BaseSequencer(int totalSteps) : totalSteps(totalSteps), steps(totalSteps, false) {}
    virtual ~BaseSequencer() {}

    virtual void setStep(int track, int step, bool active) = 0;
    virtual void update() = 0;
    
    // Accessors
    virtual int getTotalSteps() const { return totalSteps; }
    virtual bool getStepState(int track, int step) const = 0;
    virtual int getCurrentStep() const = 0;
    virtual int getNumberOfTracks() const = 0;

    void setBPM(int bpm);
        
    void setRunning(bool run) { running = run; }
    bool isRunning() const { return running; }

protected:
    int bpm = 130; // Default BPM
    float stepDuration = 0.5f; // Duration of each step in seconds
    bool running = false; // Run state of the sequencer

    std::vector<bool> steps;
    int totalSteps;
    std::vector<Track> tracks; // For Example 0: Kick, 1: Snare, 2: HiHat
    std::vector<bool> generateEuclideanRhythm(int k, int n);
};

#endif /* BaseSequencer_hpp */

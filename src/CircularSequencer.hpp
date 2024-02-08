//
//  CircularSequencer.hpp
//  circularSketch
//
//  Created by pce on 06.02.24.
//

#ifndef CircularSequencer_hpp
#define CircularSequencer_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"

class CircularSequencer {
public:
    // Sequencer properties like radius, position, and steps
    struct Track {
        std::vector<bool> steps; // Steps for the track (true for active, false for inactive)
    };
    
    CircularSequencer();
    CircularSequencer(int totalSteps, ofPoint center, float radius);
    
    // methods for drawing the sequencer and triggering sounds
    void setStep(int track, int step, bool active);
    void setup(float x, float y, float radius); // Initialize sequencer
    void setup(); // Initialize sequencer
    void setup(const std::vector<ofSoundPlayer*>& soundPlayers);
    void draw(); // Draw the sequencer
    bool checkIntersection(CircularSequencer other); // Check for intersections
    void update(); // To update the sequencer's state
    void mousePressed(int x, int y); // To handle mouse clicks

    
    void updateRhythm(int track, int k, int n);
    void setBPM(int bpm);

private:
    int bpm = 130; // Default BPM
    std::vector<ofSoundPlayer*> sounds;
    // storage for generated rhythms
    std::vector<std::vector<bool>> rhythms;
    
    bool isRunning = false; // Run state of the sequencer
    float stepDuration = 0.5f; // Duration of each step in seconds
    float lastStepTime = 0; // When the last step was triggered
    int currentStep = 0; // The current step in the sequence
    ofPoint toggleButtonCenter; // Center of the toggle button
    float toggleButtonRadius = 20; // Radius of the toggle button

    std::vector<Track> tracks; // 0: Kick, 1: Snare, 2: HiHat
    int totalSteps;
    ofPoint center;
    float radius;
    
    // Euclidean rhythm generator
    static std::vector<bool> generateEuclideanRhythm(int k, int n);
};

#endif /* CircularSequencer_hpp */

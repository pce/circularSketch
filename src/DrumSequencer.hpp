//
//  DrumSequencer.hpp
//  DrumSketch
//
//  Created by pce on 06.02.24.
//

#ifndef DrumSequencer_hpp
#define DrumSequencer_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"


#include "BaseSequencer.hpp"

class DrumSequencer : public BaseSequencer {
public:

    
    DrumSequencer();
    DrumSequencer(int totalSteps, ofPoint center, float radius);
    
    void setPosition(ofPoint newCenter) {
        center = newCenter;
    }
    // methods for drawing the sequencer and triggering sounds
    void setStep(int track, int step, bool active);
    void setup(const std::vector<ofSoundPlayer*>& soundPlayers) override;
    void update() override;
    void mousePressed(int x, int y);
    
    void updateRhythm(int track, int k, int n);
        
    int getTotalSteps() const override;
    bool getStepState(int track, int step) const override;
    int getCurrentStep() const override;
    int getNumberOfTracks() const override;
    

private:
    std::vector<ofSoundPlayer*> sounds;
    // storage for generated rhythms
    std::vector<std::vector<bool>> rhythms;
    
    float lastStepTime = 0; // When the last step was triggered
    int currentStep = 0; // The current step in the sequence
    ofPoint toggleButtonCenter; // Center of the toggle button
    float toggleButtonRadius = 20; // Radius of the toggle button
    int numberOfTracks{3};

    int totalSteps;
    ofPoint center;
    float radius;
    
};

#endif /* DrumSequencer_hpp */

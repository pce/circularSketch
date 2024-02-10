//
//  ChordSequencer.hpp
//  circularSketch
//
//  Created by pce on 08.02.24.
//

#ifndef ChordSequencer_hpp
#define ChordSequencer_hpp

#include <stdio.h>
#include "BaseSequencer.hpp"

class ChordSequencer : public BaseSequencer {
public:
    using BaseSequencer::BaseSequencer; // Inherit constructors
    void setup(ofSoundPlayer* soundPlayer); // Setup with a single sound player
    void update() override; // Override to handle pitch adjustments
    void setPitch(int step, float pitch); // Method to adjust pitch for a step

    int getTotalSteps() const override;
    bool getStepState(int track, int step) const override;
    int getCurrentStep() const override;
    int getNumberOfTracks() const override;
    
private:
    ofSoundPlayer* sound = nullptr;
    std::vector<float> pitches; // Store pitch adjustments for each step
};


#endif /* ChordSequencer_hpp */

//
//  CircularSequencerView.hpp
//  circularSketch
//
//  Created by pce on 10.02.24.
//

#ifndef CircularSequencerView_hpp
#define CircularSequencerView_hpp

#include <stdio.h>
#include "BaseSequencer.hpp"

class CircularSequencerView {
public:
    void draw(const BaseSequencer& sequencer, ofPoint center, float radius);
    // bool checkIntersection(BaseSequencer other);
};

#endif /* CircularSequencerView_hpp */

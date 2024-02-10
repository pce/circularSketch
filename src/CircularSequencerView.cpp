//
//  CircularSequencerView.cpp
//  circularSketch
//
//  Created by pce on 10.02.24.
//

#include "CircularSequencerView.hpp"

void CircularSequencerView::draw(const BaseSequencer& sequencer, ofPoint center, float radius) {
    int totalSteps = sequencer.getTotalSteps();
    int currentStep = sequencer.getCurrentStep();
        
    int numberOfTracks = sequencer.getNumberOfTracks();
    for (int trackIndex = 0; trackIndex < numberOfTracks; ++trackIndex) {
        for (int step = 0; step < totalSteps; ++step) {
            float angle = ofDegToRad((360.0f / totalSteps) * step);
            float x = center.x + cos(angle) * (radius + trackIndex * 15); // Offset each track
            float y = center.y + sin(angle) * (radius + trackIndex * 15);

            if (step == currentStep) {
                ofSetColor(ofColor::yellow);
            } else if (sequencer.getStepState(trackIndex, step)) {
                ofSetColor(ofColor::red);
            } else {
                ofSetColor(ofColor::white);
            }
            ofDrawSphere(x, y, 0, 5);
        }
    }

    // Draw toggle button based on sequencer's running state
    ofSetColor(sequencer.isSequencerRunning() ? ofColor::green : ofColor::red);
    ofDrawCircle(center, 10); // Use a fixed radius for the toggle button, adjust as needed
}

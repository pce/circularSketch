#ifndef DrumSequencer_hpp
#define DrumSequencer_hpp

#include "BaseSequencer.hpp"

class DrumSequencer : public BaseSequencer {
public:
    DrumSequencer();
    DrumSequencer(int totalSteps);
    virtual ~DrumSequencer() noexcept = default;
    void setup(const std::vector<ofSoundPlayer*>& soundPlayers);
    void updateRhythm(int track, int k, int n);
    
    void setStep(int track, int step, bool active) override;
    void update() override;
    
    int getTotalSteps() const override { return BaseSequencer::getTotalSteps(); }
    bool getStepState(int track, int step) const override;
    int getCurrentStep() const override { return currentStep; }
    int getNumberOfTracks() const override { return tracks.size(); }
    

private:
    std::vector<ofSoundPlayer*> sounds;
    std::vector<std::vector<bool>> rhythms;
    int currentStep = 0;
    float lastStepTime = 0;
    int numberOfTracks = 3;
};

#endif /* DrumSequencer_hpp */

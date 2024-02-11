#ifndef ChordSequencer_hpp
#define ChordSequencer_hpp

#include "BaseSequencer.hpp"

class ChordSequencer : public BaseSequencer {
public:
    ChordSequencer();
    ChordSequencer(int totalSteps);
//    using BaseSequencer::BaseSequencer;
    virtual ~ChordSequencer() noexcept = default;
    void setup(const std::vector<ofSoundPlayer*>& soundPlayers);
    // pitch adjustment for a step
    void setPitch(int step, float pitch);
    float getPitch(int step) const;

    void setStep(int track, int step, bool active) override;
    void update() override;

    int getTotalSteps() const override { return BaseSequencer::getTotalSteps(); }
    bool getStepState(int track, int step) const override;
    int getCurrentStep() const override { return currentStep; }
    int getNumberOfTracks() const override { return tracks.size(); }

private:
    std::vector<float> pitches;
    std::vector<ofSoundPlayer*> sounds;
    int currentStep = 0;
    int numberOfTracks = 1;
    float lastUpdateTime = 0;
};

#endif /* ChordSequencer_hpp */

/*
  ==============================================================================

    PitchShift.h
    Created: 17 Nov 2018 5:39:26pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#pragma once

#include "ProcessorBase.h"
#include "RubberBandStretcher.h"
#include "DryWet.h"

class PitchShift : public AudioProcessor
{
public:
    PitchShift(AudioProcessorValueTreeState& vts);
    ~PitchShift(); 
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock(AudioSampleBuffer& buffer, MidiBuffer&) override;
    void reset() override;
    const String getName() const override;
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    //==============================================================================
   
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int) override;
    const String getProgramName (int index) override;
    void changeProgramName (int, const String&) override;
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void releaseResources()  override;
    
    
private:
    
    // Parameters for pitch && formant
    
    float* formantParameter = nullptr;
    float* pitchParameter = nullptr;
    
    float* pitch_mixParameter = nullptr;
    
    // Actual Pitch Shifting object
    std::unique_ptr<RubberBand::RubberBandStretcher> pitch;
    RubberBand::RubberBandStretcher::Options options;
    
    AudioProcessorValueTreeState& treeState;
    
    DryWet dryWet; 
    
    //declare the pitch and formant shifting
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchShift)
};







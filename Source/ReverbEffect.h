/*
  ==============================================================================

    ReverbEffect.h
    Created: 20 Nov 2018 2:25:11pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "ProcessorBase.h"
#include "DryWet.h"

class ReverbEffect : public AudioProcessor

{
public:
    ReverbEffect(AudioProcessorValueTreeState& vts);
    ~ReverbEffect();
    
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override;
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
    float* reverbMix = nullptr;
    
    DryWet dryWet; 
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbEffect)
    
};

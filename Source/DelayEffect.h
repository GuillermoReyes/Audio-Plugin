/*
  ==============================================================================

    DelayEffect.h
    Created: 20 Nov 2018 1:50:06pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "DryWet.h"


class DelayEffect : public AudioProcessor

{
public:
    DelayEffect(AudioProcessorValueTreeState& vts);
    ~DelayEffect();
    
    
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
    DryWet dryWet; 
    float* timeParameter = nullptr;
    float* feedbackParameter = nullptr;
    float* loPass = nullptr;
    float* hiPass = nullptr;
    float* delayMix = nullptr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayEffect)
    
};

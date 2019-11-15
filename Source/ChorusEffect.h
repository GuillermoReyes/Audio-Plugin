/*
  ==============================================================================

    ChorusEffect.h
    Created: 20 Nov 2018 1:49:52pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "DryWet.h"

#include "Gain.h"
class ChorusEffect : public AudioProcessor

{
public:
    ChorusEffect(AudioProcessorValueTreeState& vts);
    
    ~ChorusEffect();
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override;
    const String getName() const override;
    
    
    float lfo (float phase);
    void copyDrySignal(const AudioBuffer<float>& buffer) noexcept
    {
        dryBuffer.makeCopyOf(buffer, true);
    }
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
    AudioSampleBuffer delayBuffer;
    int delayBufferSamples;
    int delayBufferChannels;
    int delayWritePosition;
    
    float lfoPhase;
    float inverseSampleRate;
    float twoPi;
    
    float* mixParameter;
    
    AudioBuffer<float> dryBuffer;
    Gain wetGain;
    Gain dryGain; 
    
    float* chorusMix = nullptr;
    DryWet dryWet;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChorusEffect)
    
    
};

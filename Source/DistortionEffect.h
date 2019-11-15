/*
  ==============================================================================

    DistortionEffect.h
    Created: 20 Nov 2018 1:49:35pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "ProcessorBase.h"
#include "DryWet.h"
class DistortionEffect : public AudioProcessor

{
public:
    DistortionEffect(AudioProcessorValueTreeState& vts);
    ~DistortionEffect();
    
    
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
    
    class Filter : public IIRFilter
    {
    public:
        void updateCoefficients (const double discreteFrequency,
                                 const double gain) noexcept
        {
            jassert (discreteFrequency > 0);
            
            double tan_half_wc = tan (discreteFrequency / 2.0);
            double sqrt_gain = sqrt (gain);
            
            coefficients = IIRCoefficients (/* b0 */ sqrt_gain * tan_half_wc + gain,
                                            /* b1 */ sqrt_gain * tan_half_wc - gain,
                                            /* b2 */ 0.0,
                                            /* a0 */ sqrt_gain * tan_half_wc + 1.0,
                                            /* a1 */ sqrt_gain * tan_half_wc - 1.0,
                                            /* a2 */ 0.0);
            
            setCoefficients (coefficients);
        }
    };
    
    
private:
    
    OwnedArray<Filter> filters;
    DryWet dryWet;
    float* distortionMix = nullptr; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistortionEffect)
};

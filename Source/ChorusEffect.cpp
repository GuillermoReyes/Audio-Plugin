/*
  ==============================================================================

    ChorusEffect.cpp
    Created: 20 Nov 2018 1:49:52pm
    Author:  Guillermo Reyes

  ==============================================================================
*/


#include "ChorusEffect.h"

#define MAXDELAYTIME 100.f

ChorusEffect::ChorusEffect(AudioProcessorValueTreeState& vts)
{
    chorusMix = vts.getRawParameterValue("chorusMix");
}


ChorusEffect::~ChorusEffect()
{
    
}
void ChorusEffect::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dryBuffer.setSize(getTotalNumInputChannels(), samplesPerBlock);
    delayBufferSamples = (int) (100 * (float)sampleRate);
    
    if(delayBufferSamples < 1)
        delayBufferSamples = 1;
    delayBufferChannels = getTotalNumInputChannels();
    
    delayBuffer.setSize(delayBufferSamples, delayBufferSamples);
    
    delayBuffer.clear();
    
    delayWritePosition = 0;
    lfoPhase = 0.0f;
    inverseSampleRate = 1.0f / (float) sampleRate;
    twoPi = 2.0f * M_PI;
    
    dsp::ProcessSpec spec
    {
        sampleRate,
        static_cast<uint32>(samplesPerBlock),
        static_cast<uint32>(getTotalNumInputChannels())
    };
    
    dryWet.prepare(spec);
    
}
void ChorusEffect::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    ScopedNoDenormals noDenormals;
    int maxDelayTime = 100.f;
    const int numInputChannels = getTotalNumInputChannels();
    const int numOutputChannels = getTotalNumOutputChannels();
    
    const int numSamples = buffer.getNumSamples();
    
    // Just to test, typically this will be read from the stateTree
    wetGain.params->gain = 0.5f;
    dryGain.params->gain = 1.0f - 0.5f;
    
    float currentDelay = 30.f * 0.001;
    float currentWidth = 20.0f * 0.001f;
    float currentDepth = 1.f;
    
    int numVoices  = 5;
    
    float currentFrequency = .20;
    bool stereo = true;
    
    int localWritePosition;
    float phase;
    
    
    // Actual Chorus Algorithm
    
    for (int channel = 0; channel < numInputChannels; ++channel) {
        float* channelData = buffer.getWritePointer (channel);
        float* delayData = delayBuffer.getWritePointer (channel);
        localWritePosition = delayWritePosition;
        phase = lfoPhase;
        
        for (int sample = 0; sample < numSamples; ++sample) {
            const float in = channelData[sample];
            float out = 0.0f;
            float phaseOffset = 0.0f;
            float weight;
            
            for (int voice = 0; voice < numVoices - 1; ++voice) {
                if (stereo && numVoices > 2) {
                    weight = (float)voice / (float)(numVoices - 2);
                    if (channel != 0)
                        weight = 1.0f - weight;
                } else {
                    weight = 1.0f;
                }
                
                float localDelayTime =
                (currentDelay + currentWidth * lfo (phase + phaseOffset) * (float)getSampleRate());
                
                float readPosition =
                fmodf ((float)localWritePosition - localDelayTime + (float)delayBufferSamples, delayBufferSamples);
                int localReadPosition = floorf (readPosition);
                
                
                
                float fraction = readPosition - (float)localReadPosition;
                float delayed0 = delayData[(localReadPosition + 0)];
                float delayed1 = delayData[(localReadPosition + 1) % delayBufferSamples];
                out = delayed0 + fraction * (delayed1 - delayed0);
                
                
                
                
                if (stereo && numVoices == 2)
                    channelData[sample] = (channel == 0) ? in : out * currentDepth;
                else
                    channelData[sample] += out * currentDepth * weight;
                
                if (numVoices == 3)
                    phaseOffset += 0.25f;
                else if (numVoices > 3)
                    phaseOffset += 1.0f / (float)(numVoices - 1);
            }
            
            delayData[localWritePosition] = in;
            
            if (++localWritePosition >= delayBufferSamples)
                localWritePosition -= delayBufferSamples;
            
            phase += currentFrequency * inverseSampleRate;
            if (phase >= 1.0f)
                phase -= 1.0f;
        }
    }
    
    delayWritePosition = localWritePosition;
    lfoPhase = phase;
    // Should I clear the buffer? NO or YES 
}
const String ChorusEffect::getName() const
{
    return "Distortion";
    
}
float ChorusEffect::lfo (float phase)
{
    float out = 0.0;
    if (phase < 0.5f)
        out = 0.5f + phase;
    else
        out = phase - 0.5f;
    
    
    return out;
}
AudioProcessorEditor* ChorusEffect::createEditor()
{
    return nullptr;
}
bool ChorusEffect::hasEditor() const
{
    return false;
}
//==============================================================================

bool ChorusEffect::acceptsMidi() const
{
    return false;
}
bool ChorusEffect::producesMidi() const
{
    return false;
}
double ChorusEffect::getTailLengthSeconds() const
{
    return 0;
}
//==============================================================================
int ChorusEffect::getNumPrograms()
{
    return 0;
}
int ChorusEffect::getCurrentProgram()
{
    return 0;
}
void ChorusEffect::setCurrentProgram (int)
{
    
}
const String ChorusEffect::getProgramName (int index)
{
    return {};
    
}
void ChorusEffect::changeProgramName (int, const String&)
{
    
}
//==============================================================================
void ChorusEffect::getStateInformation (MemoryBlock& destData)
{
    
}
void ChorusEffect::setStateInformation (const void* data, int sizeInBytes)
{
    
}
void ChorusEffect::releaseResources()
{
    
}

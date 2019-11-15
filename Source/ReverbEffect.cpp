/*
  ==============================================================================

    ReverbEffect.cpp
    Created: 20 Nov 2018 2:25:11pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#include "ReverbEffect.h"
ReverbEffect::ReverbEffect(AudioProcessorValueTreeState& vts)
{
    reverbMix = vts.getRawParameterValue("reverbMix");
}
ReverbEffect::~ReverbEffect()
{
    
}


void ReverbEffect::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec
    {
        sampleRate,
        static_cast<uint32>(samplesPerBlock),
        static_cast<uint32>(getTotalNumInputChannels())
    };
    
    dryWet.prepare(spec);
    
}
void ReverbEffect::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    
}
const String ReverbEffect::getName() const
{
    return "Reverb";
    
}
AudioProcessorEditor* ReverbEffect::createEditor()
{
    return nullptr;
}
bool ReverbEffect::hasEditor() const
{
    return false;
}
//==============================================================================

bool ReverbEffect::acceptsMidi() const
{
    return false;
}
bool ReverbEffect::producesMidi() const
{
    return false;
}
double ReverbEffect::getTailLengthSeconds() const
{
    return 0;
}
//==============================================================================
int ReverbEffect::getNumPrograms()
{
    return 0;
}
int ReverbEffect::getCurrentProgram()
{
    return 0;
}
void ReverbEffect::setCurrentProgram (int)
{
    
}
const String ReverbEffect::getProgramName (int index)
{
    return {};
}
void ReverbEffect::changeProgramName (int, const String&)
{
    
}
//==============================================================================
void ReverbEffect::getStateInformation (MemoryBlock& destData)
{
    
}
void ReverbEffect::setStateInformation (const void* data, int sizeInBytes)
{
    
}
void ReverbEffect::releaseResources()
{
    
}

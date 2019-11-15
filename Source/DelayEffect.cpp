/*
  ==============================================================================

    DelayEffect.cpp
    Created: 20 Nov 2018 1:50:06pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#include "DelayEffect.h"
DelayEffect::DelayEffect(AudioProcessorValueTreeState& vts)
{
    timeParameter = vts.getRawParameterValue("time");
    feedbackParameter = vts.getRawParameterValue("feedback");
    loPass = vts.getRawParameterValue("delay_loPass");
    hiPass = vts.getRawParameterValue("delay_hiPass");
    delayMix = vts.getRawParameterValue("delayMix");
}
DelayEffect::~DelayEffect()
{
    
}


void DelayEffect::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec
    {
        sampleRate,
        static_cast<uint32>(samplesPerBlock),
        static_cast<uint32>(getTotalNumInputChannels())
    };
    dryWet.prepare(spec);
    
}
void DelayEffect::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    
}
const String DelayEffect::getName() const
{
    return "Delay";
    
}

AudioProcessorEditor* DelayEffect::createEditor()
{
    return nullptr;
}
bool DelayEffect::hasEditor() const
{
    return false;
}
//==============================================================================

bool DelayEffect::acceptsMidi() const
{
    return false;
}
bool DelayEffect::producesMidi() const
{
    return false;
}
double DelayEffect::getTailLengthSeconds() const
{
    return 0;
}
//==============================================================================
int DelayEffect::getNumPrograms()
{
    return 0;
}
int DelayEffect::getCurrentProgram()
{
    return 0;
}
void DelayEffect::setCurrentProgram (int)
{
    
}
const String DelayEffect::getProgramName (int index)
{
    return {};
}
void DelayEffect::changeProgramName (int, const String&)
{
    
}
//==============================================================================
void DelayEffect::getStateInformation (MemoryBlock& destData)
{
    
}
void DelayEffect::setStateInformation (const void* data, int sizeInBytes)
{
    
}
void DelayEffect::releaseResources()
{
    
}


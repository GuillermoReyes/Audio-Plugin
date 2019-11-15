/*
  ==============================================================================

    DistortionEffect.cpp
    Created: 20 Nov 2018 1:49:35pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#include "DistortionEffect.h"

DistortionEffect::DistortionEffect(AudioProcessorValueTreeState& vts)
{
    distortionMix = vts.getRawParameterValue("distortionMix");
}
DistortionEffect::~DistortionEffect()
{
    
}


void DistortionEffect::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec
    {
        sampleRate,
        static_cast<uint32>(samplesPerBlock),
        static_cast<uint32>(getTotalNumInputChannels())
    };
    
    dryWet.prepare(spec);
}
void DistortionEffect::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    
}
const String DistortionEffect::getName() const
{
    return "Distortion";
    
}
AudioProcessorEditor* DistortionEffect::createEditor()
{
    return nullptr;
}
bool DistortionEffect::hasEditor() const
{
    return false;
}
//==============================================================================

bool DistortionEffect::acceptsMidi() const
{
    return false;
}
bool DistortionEffect::producesMidi() const
{
    return false;
}
double DistortionEffect::getTailLengthSeconds() const
{
    return 0;
}
//==============================================================================
int DistortionEffect::getNumPrograms() {
    return 0;
}
int DistortionEffect::getCurrentProgram() {
    return 0;
}
void DistortionEffect::setCurrentProgram (int) {
    
}

void DistortionEffect::changeProgramName (int, const String&)
{
    
}
//==============================================================================
void DistortionEffect::getStateInformation (MemoryBlock& destData)
{
    
}
void DistortionEffect::setStateInformation (const void* data, int sizeInBytes)
{
    
}
void DistortionEffect::releaseResources()
{
    
}
// --- // --- //
const String DistortionEffect::getProgramName (int index)
{
    return {};
}

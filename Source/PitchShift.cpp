/*
  ==============================================================================

    PitchShift.cpp
    Created: 17 Nov 2018 5:39:26pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#include "PitchShift.h"

PitchShift::PitchShift(AudioProcessorValueTreeState& vts)
:treeState(vts)
{
    options = 0;
    pitchParameter = treeState.getRawParameterValue("pitch");
    formantParameter = treeState.getRawParameterValue("formant");
    pitch_mixParameter = treeState.getRawParameterValue("pitchMix");
}
PitchShift::~PitchShift()
{
    
}

void PitchShift::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    options |= RubberBand::RubberBandStretcher::OptionProcessRealTime;
    options |= RubberBand::RubberBandStretcher::OptionWindowLong;
    options |= RubberBand::RubberBandStretcher::OptionTransientsCrisp;
    options |= RubberBand::RubberBandStretcher::OptionDetectorSoft;
    options |= RubberBand::RubberBandStretcher::OptionFormantShifted;
    
    options |= RubberBand::RubberBandStretcher::OptionPitchHighQuality;
    options |= RubberBand::RubberBandStretcher::OptionThreadingAlways;
    options |= RubberBand::RubberBandStretcher::OptionSmoothingOn;
    
    pitch = std::unique_ptr<RubberBand::RubberBandStretcher>(new RubberBand::RubberBandStretcher(sampleRate, 2,options,1.0, 1.0));
    
  
    // JUST to test, typically this would be read from the tree state
    pitch->setPitchScale(1.0);
    //pitch->setFormantScale(1.f);
    
    dsp::ProcessSpec spec
    {
        sampleRate,
        static_cast<uint32>(samplesPerBlock),
        static_cast<uint32>(getTotalNumInputChannels())
    };
    dryWet.prepare(spec);
    
    
}
void PitchShift::processBlock(AudioSampleBuffer& buffer, MidiBuffer&)
{
   // pitchParameter = treeState.getRawParameterValue("pitch");
    pitch->setPitchScale(*pitchParameter);
    std::cout<<*pitchParameter<<std::endl;
    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);
    //pitch->setPitchScale(1.f);
    //pitch->setFormantScale(1.f);
    
    pitch->process((const float* const*)buffer.getArrayOfReadPointers() , buffer.getNumSamples(),false);
    //pitch->process(context.getInputBlock(), buffer.getNumSamples(),false);
    pitch->retrieve((float *const *) buffer.getArrayOfWritePointers(), buffer.getNumSamples());
    
    
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    //TODO:
    //copy the dry signal to  wetDry,
    // And after the processing, apply the dryWet processing using dryWet
    
}
void PitchShift::reset()
{
    
    
}
const String PitchShift::getName() const
{
    return "Pitch";
}
AudioProcessorEditor* PitchShift::createEditor()
{
    return nullptr;
}
bool PitchShift::hasEditor() const {
    return false;
}
//==============================================================================

bool PitchShift::acceptsMidi() const
{
    return false;
}
bool PitchShift::producesMidi() const
{
    return false;
}
double PitchShift::getTailLengthSeconds() const
{
    return 0;
}
//==============================================================================
int PitchShift::getNumPrograms()
{
    return 0;
}
int PitchShift::getCurrentProgram()
{
    return 0;
}
void PitchShift::setCurrentProgram (int)
{
    
}
const String PitchShift::getProgramName (int index)
{
    return {}; 
}
void PitchShift::changeProgramName (int, const String&){
    
}
//==============================================================================
void PitchShift::getStateInformation (MemoryBlock& destData)
{
    
}
void PitchShift::setStateInformation (const void* data, int sizeInBytes)
{
    
}
void PitchShift::releaseResources()
{
    
    
}

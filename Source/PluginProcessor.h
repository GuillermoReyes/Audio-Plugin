/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PitchShift.h"
#include "ChorusEffect.h"
#include "DistortionEffect.h"
#include "ReverbEffect.h"
#include "DelayEffect.h"
//==============================================================================
/**
*/
class TheSaucePluginAudioProcessor  : public AudioProcessor
{
public:
    
    using AudioGraphIOProcessor = AudioProcessorGraph::AudioGraphIOProcessor;
    
    using Node = AudioProcessorGraph::Node;
    //==============================================================================
    TheSaucePluginAudioProcessor();
    ~TheSaucePluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void initialiseGraph();
    
    void connectAudioNodes();
    void connectMidiNodes();
    void updateGraph();
    
    

private:
    //==============================================================================
    
    // ---- Daisy Chaining the Processors ----
    
    std::unique_ptr<AudioProcessorGraph> mainProcessor;
    
    Node::Ptr audioInputNode;
    Node::Ptr audioOutputNode;
    Node::Ptr midiInputNode;
    Node::Ptr midiOutputNode;
    
    Node::Ptr slot1Node;
    Node::Ptr slot2Node;
    Node::Ptr slot3Node;
    
    
    
    AudioProcessorValueTreeState parameters; 
    
    float* master_output = nullptr;
    float* master_loPass = nullptr;
    float* master_hiPass = nullptr;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheSaucePluginAudioProcessor)
};

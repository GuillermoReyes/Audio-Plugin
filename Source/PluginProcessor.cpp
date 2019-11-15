/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheSaucePluginAudioProcessor::TheSaucePluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
, mainProcessor(new AudioProcessorGraph()),
parameters(*this, nullptr, Identifier("ROOT"),
           {
               std::make_unique<AudioParameterFloat>("chorus_mix", "Mix",0.0f, 1.0f, 0.5f),
               std::make_unique<AudioParameterFloat>("pitch", "PITCH", 0.01, 2.0, 1.0),
               std::make_unique<AudioParameterBool> ("link",  "LINK", true ),   
               std::make_unique<AudioParameterFloat> ("formant", "FORMANT", 0.01, 2.0, 1.0),
               std::make_unique<AudioParameterFloat>("pitchMix", "MIX", 0.f, 1.0, 0),
               std::make_unique<AudioParameterFloat> ("distortionMix", "MIX", 0.0f, 1.0, 0.f),
               std::make_unique<AudioParameterFloat> ("chorusMix", "MIX", 0.0f, 1.f, 0),
               std::make_unique<AudioParameterFloat> ("time", "TIME", 0.f, 1.f, 0 ),
               std::make_unique<AudioParameterFloat> ("feedback", "FEEDBACK", 0.f, 1.f, 0),
               std::make_unique<AudioParameterFloat> ("delay_hiPass", "HIPASS", 0.f, 1.f, 0.0),
               std::make_unique<AudioParameterFloat> ("delay_loPass", "LOPASS", 0.f, 1.f, 0.0),
               std::make_unique<AudioParameterFloat> ("delayMix", "MIX", 0.0f, 1.f, 0),
               std::make_unique<AudioParameterBool> ("reverbSmall", "S", true),
               std::make_unique<AudioParameterBool> ("reverbMed", "M", false),
               std::make_unique<AudioParameterBool> ("reverbLarge", "L", false),
               std::make_unique<AudioParameterFloat> ("reverbMix", "MIX", 0.f, 1.f, 0),
               std::make_unique<AudioParameterFloat> ("master_hiPass", "HIPASS", 0.f, 1.f, 0),
               std::make_unique<AudioParameterFloat> ("master_loPass", "LOPASS", 0.f, 1.f, 0),
               std::make_unique<AudioParameterFloat> ("masterSlider", "MASTER", 0.f, 1.f, 0)
               
           })
{
    master_output = parameters.getRawParameterValue("masterSlider");
    master_loPass = parameters.getRawParameterValue("master_loPass");
    master_hiPass = parameters.getRawParameterValue("master_hiPass");
}

TheSaucePluginAudioProcessor::~TheSaucePluginAudioProcessor()
{
    
}

//==============================================================================
const String TheSaucePluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TheSaucePluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TheSaucePluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TheSaucePluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TheSaucePluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TheSaucePluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TheSaucePluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TheSaucePluginAudioProcessor::setCurrentProgram (int index)
{
}

const String TheSaucePluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void TheSaucePluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TheSaucePluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    mainProcessor->setPlayConfigDetails(getMainBusNumInputChannels(), getMainBusNumOutputChannels(), sampleRate, samplesPerBlock);
    mainProcessor->prepareToPlay(sampleRate, samplesPerBlock);
    initialiseGraph();
    updateGraph();
}

void TheSaucePluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
    mainProcessor->releaseResources();
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TheSaucePluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TheSaucePluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    mainProcessor->processBlock(buffer, midiMessages);
}

//==============================================================================
bool TheSaucePluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TheSaucePluginAudioProcessor::createEditor()
{
    return new TheSaucePluginAudioProcessorEditor (*this,parameters);
}

//==============================================================================
void TheSaucePluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void TheSaucePluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheSaucePluginAudioProcessor();
}

void TheSaucePluginAudioProcessor::initialiseGraph()
{
    mainProcessor->clear();
    
    audioInputNode  = mainProcessor->addNode (new AudioGraphIOProcessor (AudioGraphIOProcessor::audioInputNode));
    audioOutputNode = mainProcessor->addNode (new AudioGraphIOProcessor (AudioGraphIOProcessor::audioOutputNode));
    midiInputNode   = mainProcessor->addNode (new AudioGraphIOProcessor (AudioGraphIOProcessor::midiInputNode));
    midiOutputNode  = mainProcessor->addNode (new AudioGraphIOProcessor (AudioGraphIOProcessor::midiOutputNode));
    
    //TODO: implement the audioconnection nodes
    connectAudioNodes();
    connectMidiNodes();
    
    
    
    
}

void TheSaucePluginAudioProcessor::connectAudioNodes()
{
    for (int channel = 0; channel < 2; ++channel)
        mainProcessor->addConnection ({ { audioInputNode->nodeID,  channel },
            { audioOutputNode->nodeID, channel } });
}
void TheSaucePluginAudioProcessor::connectMidiNodes()
{
    
    
    mainProcessor->addConnection ({ { midiInputNode->nodeID,  AudioProcessorGraph::midiChannelIndex },
            { midiOutputNode->nodeID, AudioProcessorGraph::midiChannelIndex } });
    
    
}
void TheSaucePluginAudioProcessor::updateGraph()
{
    
    
    ReferenceCountedArray<Node> slots;
    
    
    //slots.add(mainProcessor->addNode(new PitchShift()));
    slots.add(mainProcessor->addNode(new DistortionEffect(parameters)));
    slots.add(mainProcessor->addNode(new DelayEffect(parameters)));
    slots.add(mainProcessor->addNode(new ReverbEffect(parameters)));
    slots.add(mainProcessor->addNode(new PitchShift(parameters)));
    //slots.add(mainProcessor->addNode(new ChorusEffect())); // crashes if enabled
    
    //mainProcessor->setPlayConfigDetails(getMainBusNumInputChannels(), getMainBusNumOutputChannels(), getSampleRate(), getBlockSize());
    
    
    ReferenceCountedArray<Node> activeSlots;
    for(auto slot : slots)
        slot->getProcessor()->setPlayConfigDetails(getMainBusNumInputChannels(), getMainBusNumOutputChannels(), getSampleRate(), getBlockSize());
    
    for (int i = 0; i < slots.size()-1; ++i)
    {
        for(int channel = 0; channel < 2; ++channel)
            mainProcessor->addConnection({ { slots.getUnchecked(i)->nodeID, channel },
                
                { slots.getUnchecked(i+1)->nodeID, channel } });
                
            
    }
        
    for(int channel = 0; channel < 2; ++channel)
    {
        mainProcessor->addConnection({ { audioInputNode->nodeID,         channel },
            { slots.getFirst()->nodeID, channel } });
        mainProcessor->addConnection({ { slots.getLast()->nodeID,         channel },
            { audioOutputNode->nodeID, channel } });
        
    }
    connectMidiNodes();
    for( auto  node : mainProcessor->getNodes())
        node->getProcessor()->enableAllBuses();
    
}

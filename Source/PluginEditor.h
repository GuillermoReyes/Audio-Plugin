/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "TheSauceComponents.h"

//==============================================================================
/**
*/
class TheSaucePluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    
    TheSaucePluginAudioProcessorEditor (TheSaucePluginAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~TheSaucePluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    AudioProcessorValueTreeState& valueTreeState;
    std::unique_ptr<Image> background;
    // Pitch && Formant
    Slider pitchSlider;
    Slider formantSlider;
    Slider pitchMix;
    
    
    ToggleButton linkButton;
    
    // Labels for pitch profile
    Label pitchMainLabel;
    Label pitchLabel;
    Label formantLabel;
    Label pitchMixLabel;
    // Chorus
    Slider chorusMix;
    Label chorusLabel;
    std::unique_ptr<SliderAttachment> chorusMixAttachment; 
    //
    Slider distortionMix;
    Label distortionLabel;
    //Delay
    Slider timeDelay;
    Slider feedbackDelay;
    
    Slider hi_passDelay;
    Slider lo_passDelay;
    
    Slider delayMix;
    /* Delay Labels */
    Label delayLabel;
    
    //Reverb
    
    ComboBox roomSize; 
    Slider reverbMix;
    TextButton reverb_sm;
    
    TextButton reverb_md;
    
    TextButton reverb_lg;
    
    Label reverbLabel;
    
    // Master Controls
    
    Slider master_hi_pass;
    Slider master_lo_pass;
    Slider master_output;
    
    
    Label masterLabel;
    Label masterDisplay; 
    // Plugin State
    ToolbarPanel toolbar;
    TopPanel topPanel;
    DelayPanel delayPanel;
    ReverbPanel reverbPanel;
    std::unique_ptr<Drawable> sauce_logo;
    std::unique_ptr<Drawable> djswivel_logo; 
   
    TheSaucePluginAudioProcessor& processor;
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheSaucePluginAudioProcessorEditor)
};

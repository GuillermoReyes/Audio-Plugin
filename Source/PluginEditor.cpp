/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#define HEIGHT 428

#define WIDTH 608
//==============================================================================
TheSaucePluginAudioProcessorEditor::TheSaucePluginAudioProcessorEditor (TheSaucePluginAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts), topPanel(vts)


{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    Colour sauce_orange = Colour(242, 87, 26);
    
    auto initSlider = [this](Slider& slider)
    {
        slider.setSliderStyle(Slider::Rotary);
        addAndMakeVisible(slider);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    };
    
    //background = std::unique_ptr<Image>(Drawable::createFromImageData(BinaryData::TheSauceBackground_svg, BinaryData::TheSauceBackground_svgSize));
    //addAndMakeVisible(background.get());
    pitchLabel.setText("Pitch", NotificationType::dontSendNotification);
    formantLabel.setText("Formant", NotificationType::dontSendNotification);
    pitchMixLabel.setText("Mix", NotificationType::dontSendNotification);
    distortionLabel.setText("DISTORTION", NotificationType::dontSendNotification);
    chorusLabel.setText("CHORUS", NotificationType::dontSendNotification);
    delayLabel.setText("DELAY", NotificationType::dontSendNotification);
    reverbLabel.setText("REVERB",NotificationType::dontSendNotification );
    masterLabel.setText("MASTER",NotificationType::dontSendNotification );
    // Logo and Stuff
    masterDisplay.setColour(Label::textColourId, sauce_orange);
    masterDisplay.getTextValue().referTo(master_output.getValueObject());
    
    sauce_logo = std::unique_ptr<Drawable>(Drawable::createFromImageData(BinaryData::The_Sauce__Logo_svg, BinaryData::The_Sauce__Logo_svgSize));
    djswivel_logo = std::unique_ptr<Drawable> (Drawable::createFromImageData(BinaryData::DJSwivelLogo_png, BinaryData::DJSwivelLogo_pngSize));
    addAndMakeVisible(sauce_logo.get());
    //addAndMakeVisible(djswivel_logo.get());
    
    //addAndMakeVisible(pitchLabel);
    //addAndMakeVisible(formantLabel);
    //addAndMakeVisible(pitchMixLabel);
    //addAndMakeVisible(distortionLabel);
    //addAndMakeVisible(chorusLabel);
    //addAndMakeVisible(delayLabel);
    //addAndMakeVisible(reverbLabel);
    //addAndMakeVisible(masterLabel);
    //initSlider(pitchSlider);
    //initSlider(formantSlider);
    //initSlider(pitchMix);
    //initSlider(distortionMix);
    //initSlider(chorusMix);
    chorusMixAttachment.reset(new SliderAttachment(valueTreeState,"chorus_mix",chorusMix));
    //initSlider(hi_passDelay);
    //initSlider(lo_passDelay);
    //initSlider(hi_passDelay);
    //initSlider(delayMix);
    //initSlider(reverbMix);
    //initSlider(master_output);
    //initSlider(master_hi_pass);
    //initSlider(master_lo_pass);
    //roomSize.addItem("S", 1);
    //roomSize.addItem("M", 2);
    //roomSize.addItem("L", 3);
    
    //addAndMakeVisible(roomSize);
    //initSlider(timeDelay);
    
    //timeDelay.setSliderStyle(Slider::Rotary);
    //timeDelay.setTextBoxStyle(Slider::TextBoxRight, false, 40, 20);
    //addAndMakeVisible(timeDelay);
    
    //feedbackDelay.setSliderStyle(Slider::Rotary);
    //feedbackDelay.setTextBoxStyle(Slider::TextBoxRight, true, 40, 20);
    //addAndMakeVisible(feedbackDelay);
    
    //addAndMakeVisible(linkButton);
    
    
    
    
    addAndMakeVisible(toolbar);
    addAndMakeVisible(topPanel);
    addAndMakeVisible(delayPanel);
    addAndMakeVisible(reverbPanel);
    //master_output.setRange(0, 100, 1);
    initSlider(master_output);
    initSlider(master_lo_pass);
    initSlider(master_hi_pass);
    
    addAndMakeVisible(masterDisplay);
    
    setSize(WIDTH,HEIGHT);
    
    
    
    
}

TheSaucePluginAudioProcessorEditor::~TheSaucePluginAudioProcessorEditor()
{
    
}

//==============================================================================
void TheSaucePluginAudioProcessorEditor::paint (Graphics& g)
{//124
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    Image background = ImageCache::getFromMemory(BinaryData::TheSauceBackground_png, BinaryData::TheSauceBackground_pngSize);
    Image djswivel = ImageCache::getFromMemory(BinaryData::DJSwivelLogo_png, BinaryData::DJSwivelLogo_pngSize);
    Image splash = ImageCache::getFromMemory(BinaryData::TheSauceSplash_png, BinaryData::TheSauceSplash_pngSize);
    
    g.drawImageAt(background, 0, 0);
    g.drawImageAt(djswivel, 16, 20);
    g.drawImageAt(splash, 510, -48);
    g.setColour (Colours::white);
    g.setFont (15.0f);
    //background->setBounds(0, 0, 608, 428);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void TheSaucePluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    //background->setBounds(0, 0, 608, 428);
    int left_margin = 16;
    int top_margin = 53;
    int toolbar_height = 40;
    
    int component_spacing = 16;
    int component_label_spacing = 20;
    int component_label_indent = component_label_spacing;
    
   // pitchSlider.setBounds(left_margin,
                  //        50,
                   //       72, 72);
    
    
    // =========
    
   // linkButton.setBounds(left_margin + 80,
                 //        78,
                   //      20,20);
    
    // =========
    
   // formantSlider.setBounds(145, 50, 72, 72);
    
    // =========
    
    //pitchMix.setBounds(145+120,50,72,72);
    
    // ==========
    //pitchLabel.setBounds(30, 110, 40, 40);
    //formantLabel.setBounds(150, 110, 60, 40);
    //pitchMixLabel.setBounds(285, 110, 40, 40);
    
    
    
    
    
    //Distortion
    //distortionMix.setBounds(370 , 50, 72, 72);
    
    //distortionLabel.setBounds(368, 20, 80, 40);
    
    //===========
    
    //chorusMix.setBounds(480, 50, 72, 72);
    //chorusLabel.setBounds(479, 20, 80, 40);
    
    //======   DELAY CONTROLS
    
    //timeDelay.setBounds(left_margin, 190, 106, 106);
   
    //==
    //feedbackDelay.setBounds(left_margin, 270, 106, 106);
    
    // ====
    
    //hi_passDelay.setBounds(180, 210, 60, 60);
    //lo_passDelay.setBounds(260, 210, 60, 60);
    //delayMix.setBounds(210, 290, 72, 72);
    
    //delayLabel.setBounds(20, 180, 80, 40);
    
    // ===== Reverb Controls
    
    //roomSize.setBounds(350, 230, 30, 20);
    
    //reverbMix.setBounds( 340, 290, 72, 72);
    
    //reverbLabel.setBounds(220,180, 80, 40);
    
    //====== MASTER controls
    
    //master_output.setBounds(460, 290, 72, 72);
    
    //master_hi_pass.setBounds(420, 210, 60, 60);
    //master_lo_pass.setBounds(500, 210, 60, 60);
    
    //masterLabel.setBounds(470, 180, 80, 40);
    sauce_logo->setBounds(259, 8, 91, 34 );
    //djswivel_logo->setBounds(16, 10, 104, 12); 29
    toolbar.setBounds(16, 53, 636, 100 );
    topPanel.setBounds(16, 109, 667, 210);
    delayPanel.setBounds(16,242, 381, 260 );
    reverbPanel.setBounds(322, 242, 209, 260);
    
    master_output.setBounds(490, 320, 59, 59);
    master_hi_pass.setBounds(480, 280, 29, 29);
    master_lo_pass.setBounds(530, 280, 29, 29);
    
    masterDisplay.setBounds(502, 341, 40, 13);
    
    
    
    //master_lo_pass.setBounds(
    
}

/*
  ==============================================================================

    TheSauceComponents.cpp
    Created: 27 Nov 2018 8:29:00pm
    Author:  Guillermo Reyes

  ==============================================================================
*/
// (16, 335)
#include "TheSauceComponents.h"
#include "TheSauceLookAndFeel.h"

TopPanel::TopPanel(AudioProcessorValueTreeState& vts)
:treeState(vts)
{
    Colour sauce_orange = Colour(242, 87, 26);
    auto initSlider = [this](Slider& slider)
    {
        slider.setSliderStyle(Slider::Rotary);
        addAndMakeVisible(slider);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    };
    Font lowercase(Typeface::createSystemTypefaceFor(BinaryData::GothamBook_otf, BinaryData::GothamBook_otfSize));
    
    //setLookAndFeel(lf);
    topPanel_image = std::unique_ptr<Drawable>(Drawable::createFromImageData(BinaryData::TheSauceTopContainer_svg, BinaryData::TheSauceTopContainer_svgSize));
    pitchLabel.setText("PITCH", dontSendNotification);
    distortionLabel.setText("DISTORTION", dontSendNotification);
    chorusLabel.setText("CHORUS", dontSendNotification);
    lookAndFeel->setDefaultLookAndFeel(lookAndFeel);
   
    linkButton.setButtonText("LINK");
    pitchText.setFont(lowercase);
    formantText.setFont(lowercase);
    pitchText.setText("PITCH", dontSendNotification);
    formantText.setText("FORMANT", dontSendNotification);
    
    addAndMakeVisible(topPanel_image.get());
    addAndMakeVisible(pitchLabel);
    addAndMakeVisible(distortionLabel);
    addAndMakeVisible(chorusLabel);
    initSlider(pitchSlider);
    pitchAttachment.reset(new SliderAttachment(vts, "pitch", pitchSlider));
    //pitchSlider.setRange(-12, 12, 1);
    pitchDisplay.setColour(Label::textColourId, sauce_orange);
    pitchDisplay.getTextValue().referTo(pitchSlider.getValueObject());
    initSlider(formantSlider);
    formantAttachment.reset(new SliderAttachment(vts, "formant", formantSlider));
    
    formantDisplay.setColour(Label::textColourId, sauce_orange);
    formantDisplay.getTextValue().referTo(formantSlider.getValueObject());
    //formantSlider.setRange(-12, 12, 1);
    initSlider(pitchMixSlider);
    
    pitchMixAttachment.reset(new SliderAttachment(vts, "pitchMix", pitchMixSlider)); 
    pitchMixSlider.setColour(Slider::rotarySliderFillColourId, sauce_orange);
    //pitchMixSlider.setRange(0, 100,1);
    pitchMixDisplay.setColour(Label::textColourId, sauce_orange);
    pitchMixDisplay.getTextValue().referTo(pitchMixSlider.getValueObject());
    initSlider(distortionSlider);
    //distortionSlider.setRange(0, 100,1);
    distortionAttachment.reset(new SliderAttachment(vts, "distortion", distortionSlider)); 
    
    distortionDisplay.setColour(Label::textColourId, sauce_orange);
    distortionDisplay.getTextValue().referTo(distortionSlider.getValueObject());
    
    initSlider(chorusSlider);
    //chorusSlider.setRange(0, 100, 1);
    chorusAttachment.reset(new SliderAttachment(vts, "chorus", chorusSlider));
    
    chorusDisplay.setColour(Label::textColourId, sauce_orange);
    chorusDisplay.getTextValue().referTo(chorusSlider.getValueObject());
    
    addAndMakeVisible(pitchText);
    addAndMakeVisible(formantText);
    addAndMakeVisible(linkButton);
    
    addAndMakeVisible(pitchDisplay);
    addAndMakeVisible(formantDisplay);
    addAndMakeVisible(pitchMixDisplay);
    addAndMakeVisible(distortionDisplay);
    addAndMakeVisible(chorusDisplay);
    
    
    
    
    
}
void TopPanel::paint(Graphics& g)
{
    topPanel_image->setBounds(0, 0, 667, 210);
    pitchLabel.setBounds(155, 7, 43, 13);
    distortionLabel.setBounds(368, 7, 78, 13);
    chorusLabel.setBounds(490, 7, 57, 13);
    pitchSlider.setBounds(20, 37, 59, 59);
    formantSlider.setBounds(140, 37, 59, 59);
    pitchMixSlider.setBounds(260, 37, 59, 59);
    distortionSlider.setBounds(380, 37, 59, 59);
    chorusSlider.setBounds(493, 37, 59, 59);
    pitchText.setBounds(23, 102, 40, 11);
    formantText.setBounds(140, 102, 62, 11);
    linkButton.setBounds(90, 63, 30, 13 );
    
    
    pitchDisplay.setBounds(32, 60, 37, 13);
    formantDisplay.setBounds(152, 60, 37, 13);
    distortionDisplay.setBounds(392, 60, 40, 13);
    pitchMixDisplay.setBounds(272, 60, 40, 13);
    chorusDisplay.setBounds(505, 60, 40, 13);
}

DelayPanel::DelayPanel()
{
    auto initSlider = [this](Slider& slider)
    {
        slider.setSliderStyle(Slider::Rotary);
        addAndMakeVisible(slider);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    };
    
    delayPanel = std::unique_ptr<Drawable>(Drawable::createFromImageData(BinaryData::TheSauceBottomRightContainer_svg, BinaryData::TheSauceBottomRightContainer_svgSize));
    delayLabel.setText("DELAY", dontSendNotification);
    addAndMakeVisible(delayPanel.get());
    addAndMakeVisible(delayLabel);
    
    Colour sauce_orange = Colour(242, 87, 26);
    Colour sauce_darkgrey = Colour(37, 37, 37);
    Colour sauce_black = Colour(21, 21, 21);
    timeSlider.setSliderStyle(Slider::Rotary);
    feedbackSlider.setSliderStyle(Slider::Rotary);
    timeBox.setColour(Label::textColourId, sauce_orange);
    timeBox.setColour(Label::outlineColourId, sauce_darkgrey);
    timeBox.setColour(Label::backgroundColourId, sauce_black);
    timeBox.setEditable(true);
    timeBox.getTextValue().referTo(timeSlider.getValueObject());
    feedbackBox.setColour(Label::textColourId, sauce_orange);
    feedbackBox.setColour(Label::outlineColourId, sauce_darkgrey);
    feedbackBox.setColour(Label::backgroundColourId, sauce_black);
    feedbackBox.setEditable(true);
    feedbackBox.getTextValue().referTo(feedbackSlider.getValueObject());
    timeSlider.setTextBoxStyle(Slider::NoTextBox,false, 0, 0 );
    
    feedbackSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    
    delayDisplay.setColour(Label::textColourId, sauce_orange);
    delayDisplay.getTextValue().referTo(mixSlider.getValueObject());
    addAndMakeVisible(timeBox);
    addAndMakeVisible(feedbackBox);
    addAndMakeVisible(timeSlider);
    addAndMakeVisible(feedbackSlider);
    
    mixSlider.setRange(0, 100, 1);
    initSlider(loPassSlider);
    initSlider(hiPassSlider);
    initSlider(mixSlider);
    
    addAndMakeVisible(delayDisplay);
    
    
    
}
void DelayPanel::paint(Graphics& g)
{
    delayPanel->setBounds(0, 0, 381, 260);
    delayLabel.setBounds(117, 7, 46, 13);
    
    timeSlider.setBounds(20, 33, 39, 39);
    timeBox.setBounds(56, 42, 44, 20);
    feedbackSlider.setBounds(20, 100, 39, 39);
    feedbackBox.setBounds(56, 109, 44, 20);
    hiPassSlider.setBounds(160, 40, 29, 29);
    loPassSlider.setBounds(210, 40, 29, 29);
    mixSlider.setBounds(175, 80, 59, 59);
    
    delayDisplay.setBounds(187, 103, 40, 13);
    
}
ReverbPanel::ReverbPanel()
{
    Colour sauce_orange = Colour(242, 87, 26);
    reverbPanel_image = std::unique_ptr<Drawable> (Drawable::createFromImageData(BinaryData::TheSauceBottomMiddleContainer_svg, BinaryData::TheSauceBottomMiddleContainer_svgSize));
    reverbLabel.setText("REVERB", dontSendNotification);
    
    reverbSlider.setSliderStyle(Slider::Rotary);
    reverbSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    reverbSlider.setRange(0, 100, 1);
    reverbDisplay.setColour(Label::textColourId, sauce_orange);
    reverbDisplay.getTextValue().referTo(reverbSlider.getValueObject());
    small.setLookAndFeel(lnf);
    small.setClickingTogglesState(true);
    med.setLookAndFeel(lnf);
    med.setClickingTogglesState(true);
    large.setLookAndFeel(lnf);
    large.setClickingTogglesState(true);
    
    small.setRadioGroupId(RoomOptions);
    med.setRadioGroupId(RoomOptions);
    large.setRadioGroupId(RoomOptions);
    
    addAndMakeVisible(reverbPanel_image.get());
    addAndMakeVisible(reverbLabel);
    addAndMakeVisible(small);
    addAndMakeVisible(med);
    addAndMakeVisible(large);
    addAndMakeVisible(reverbSlider);
    addAndMakeVisible(reverbDisplay);
    
    
}

ReverbPanel::~ReverbPanel()
{
    small.setLookAndFeel(nullptr);
    med.setLookAndFeel(nullptr);
    large.setLookAndFeel(nullptr); 
}
void ReverbPanel::paint(Graphics& g)
{
    reverbPanel_image->setBounds(0, 0, 209, 260);
    reverbLabel.setBounds(33, 7, 55, 13);
    
    small.setBounds(20, 30, 22, 22);
    med.setBounds(50, 30, 22, 22);
    large.setBounds(80, 30, 22, 22);
    
    reverbSlider.setBounds(31, 78, 59, 59);
    reverbDisplay.setBounds(43, 100, 40, 13);
    
    
    
}

void ToolbarPanel::paint(Graphics& g)
{
  
    
    //setOpaque(true);
    //g.drawImage(toolbar, 0, 0, 636, 100, 0, 0, 636, 100);
    toolbar->setBounds(0, 0, 636, 100);
    
    save.setBounds(474, 5, 64, 13);
    save_as.setBounds(474, 22, 64, 13);
    //do an affine transform to reflect the "undo" button
    go_back.setBounds(0,0,26, 38);
    go_forward.setBounds(26, 0, 26, 38);
    menu.setBounds(52, 0, 27, 38);
    
}
ToolbarPanel::ToolbarPanel()
{
    //Font fontAwesome(Typeface::createSystemTypefaceFor(BinaryData::FontAwesome_otf, BinaryData::FontAwesome_otfSize));
    
    toolbar_image = ImageCache::getFromMemory(BinaryData::TheSauceToolbar_png, BinaryData::TheSauceToolbar_pngSize);
   toolbar = std::unique_ptr<Drawable>(Drawable::createFromImageData(BinaryData::TheSauceToolbar_svg, BinaryData::TheSauceToolbar_svgSize));
    
    save.setButtonText("SAVE");
    save_as.setButtonText("SAVE AS");
    save.setLookAndFeel(lnf);
    save_as.setLookAndFeel(lnf);
    
    go_back.setLookAndFeel(iconLnf);
    go_back.setButtonText("G");
    go_forward.setLookAndFeel(iconLnf);
    go_forward.setButtonText("G");
    menu.setLookAndFeel(iconLnf);
    menu.setButtonText("h");
    
    addAndMakeVisible(toolbar.get());
    addAndMakeVisible(save);
    addAndMakeVisible(save_as);
    addAndMakeVisible(go_back);
    addAndMakeVisible(go_forward);
    addAndMakeVisible(menu);
    
    
}
ToolbarPanel::~ToolbarPanel()
{
    setLookAndFeel(nullptr); 
    
}

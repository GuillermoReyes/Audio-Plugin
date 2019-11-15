/*
  ==============================================================================

    TheSauceComponents.h
    Created: 27 Nov 2018 8:29:00pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

#include "TheSauceLookAndFeel.h"
/*
 TODO:
 
 For all Components, render the label string, once you have loaded the fonts
 Use SauceLookAndFeel and inhert the methods to draw the knobs, etc
 
 
 TODO:
 
 Pass the paramter states to the indvudual components, as well as in Effects/
 
 
 
 */
typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;


class TopPanel : public Component
{
public:
    TopPanel(AudioProcessorValueTreeState& vts);
    void paint(Graphics& g);
    
    
private:
    std::unique_ptr<Drawable> topPanel_image;
    
    Label pitchLabel;
    Label distortionLabel;
    Label chorusLabel;
    SharedResourcePointer<TheSauceLookAndFeel> lookAndFeel;
    
    Slider pitchSlider;
    
    Slider formantSlider;
    Slider pitchMixSlider;
    Slider distortionSlider;
    Slider chorusSlider;
    
    std::unique_ptr<SliderAttachment> pitchAttachment;
    std::unique_ptr<SliderAttachment> formantAttachment;
    std::unique_ptr<SliderAttachment> pitchMixAttachment;
    std::unique_ptr<SliderAttachment> distortionAttachment;
    std::unique_ptr<SliderAttachment> chorusAttachment;
    
    Label pitchDisplay;
    Label formantDisplay;
    Label pitchMixDisplay;
    
    Label distortionDisplay;
    Label chorusDisplay;
    
    
    
    TextButton linkButton; 
    
    Label pitchText;
    Label formantText;
    
    std::unique_ptr<ButtonAttachment> linkAttachment;
    OwnedArray<Label> mixLabels;
    AudioProcessorValueTreeState& treeState;
    
};


class DelayPanel : public Component

{
public:
    DelayPanel();
    void paint(Graphics& g);
    
private:
    std::unique_ptr<Drawable> delayPanel;
    Label delayLabel;
    
    Slider timeSlider;
    Slider feedbackSlider;
    Slider hiPassSlider;
    Slider loPassSlider;
    Slider mixSlider;
    
    Label delayDisplay; 
    Label timeBox;
    Label feedbackBox; 
    
};

class ReverbPanel : public Component
{
public: 
    ReverbPanel();
    ~ReverbPanel(); 
    void paint(Graphics& g);
    
    
private:
 
    enum RadioButtonIDs
    {
        RoomOptions = 1001
    };
    std::unique_ptr<Drawable> reverbPanel_image;
    Label reverbLabel;
    
    TextButton small {"S"};
    TextButton med   {"M"};
    TextButton large {"L"};
    
    SharedResourcePointer<OtherLookAndFeel> lnf;
    
    Slider reverbSlider;
    Label reverbDisplay; 
    
    
};


class ToolbarPanel : public Component
{
public: 
    ToolbarPanel();
    ~ToolbarPanel();
    void paint(Graphics& g);
    
private:
    
    SharedResourcePointer<LargeButtonLookAndFeel> lnf;
    SharedResourcePointer<IconLookAndFeel> iconLnf; 
    //TODO create buttons for undo, redo, save, etc, etc 
    Image toolbar_image;
    TextButton save;
    TextButton save_as;
    TextButton go_back;
    TextButton go_forward;
    TextButton menu;
    TextButton up;
    TextButton down;
    std::unique_ptr<Drawable> toolbar;
};


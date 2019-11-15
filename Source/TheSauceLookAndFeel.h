/*
  ==============================================================================

    TheSauceLookAndFeel.h
    Created: 27 Nov 2018 7:57:35pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class TheSauceLookAndFeel : public LookAndFeel_V4
{
public: 
    TheSauceLookAndFeel();
    
    Image imageKnobSM, imageKnobMD, imageKnobLG, imageButtonSmall, imageButtonPressed;
    
    
    void drawRotarySlider (Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &) override;
    void drawLinearSliderBackground (Graphics&, int x, int y, int width, int height,
                                     float sliderPos, float minSliderPos, float maxSliderPos,
                                     const Slider::SliderStyle, Slider&) override;
    
    void drawButtonBackground (Graphics&, Button&, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override;
    
    Typeface::Ptr getTypefaceForFont(const Font &) override;
    
    void     drawToggleButton (Graphics &, ToggleButton &, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
    void     drawTickBox (Graphics &, Component &, float x, float y, float w, float h, bool ticked, bool isEnabled, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override; 
    
private:
    std::unique_ptr<Drawable> large_knob; 
    std::unique_ptr<Drawable> medium_button;
    std::unique_ptr<Drawable> button_on;
    std::unique_ptr<Drawable> button_off;
    
    
    
    
};

class OtherLookAndFeel : public LookAndFeel_V4
{
public:
    
    OtherLookAndFeel();
   
    
    void drawButtonBackground (Graphics&, Button&, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override;
    
    Typeface::Ptr getTypefaceForFont(const Font &) override;
    
private:
    
    std::unique_ptr<Drawable> button_off;
    std::unique_ptr<Drawable> button_on; 
    
};

class LargeButtonLookAndFeel : public LookAndFeel_V4
{
public:
    LargeButtonLookAndFeel();
    
    void drawButtonBackground (Graphics&, Button&, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override;
    
    Typeface::Ptr getTypefaceForFont(const Font & ) override;
private:
    std::unique_ptr<Drawable> large_button;
};

class IconLookAndFeel : public LookAndFeel_V4
{
public:
    IconLookAndFeel();
    ~IconLookAndFeel();
    
    Typeface::Ptr getTypefaceforFont(const Font &) ;
    Font getTextButtonFont(TextButton &, int buttonHeight) ;
    

private:
    

    
};

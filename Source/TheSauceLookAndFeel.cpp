/*
  ==============================================================================

    TheSauceLookAndFeel.cpp
    Created: 27 Nov 2018 7:57:35pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#include "TheSauceLookAndFeel.h"





// ---

TheSauceLookAndFeel::TheSauceLookAndFeel()
{
    Colour sauceOrange, saucePurple, sauceLightGrey, sauceDarkGrey, sauceBlack;
    
    sauceOrange = Colour(242, 87, 26);
    saucePurple = Colour(150, 22, 101);
    sauceLightGrey = Colour(112, 112, 112);
    sauceDarkGrey = Colour(37, 37, 37);
    sauceBlack = Colour(21, 21, 21);
    
    
    setColour(Slider::rotarySliderFillColourId, sauceOrange);
    setColour(Slider::thumbColourId, sauceOrange);
    
    setColour(AlertWindow::backgroundColourId,sauceLightGrey);
    setColour(AlertWindow::textColourId, Colours::white);
    setColour(TextEditor::backgroundColourId,sauceBlack);
    setColour(TextEditor::textColourId, sauceOrange);
    setColour(TextEditor::outlineColourId, sauceDarkGrey);
    setColour(TreeView::backgroundColourId, sauceLightGrey);
    
    imageKnobSM = ImageCache::getFromMemory(BinaryData::KnobSmall_svg , BinaryData::KnobSmall_svgSize);
    imageKnobMD = ImageCache::getFromMemory(BinaryData::KnobMedium_svg, BinaryData::KnobMedium_svgSize);
    imageButtonSmall = ImageCache::getFromMemory(BinaryData::ButtonSmall_svg, BinaryData::ButtonSmall_svgSize);
    large_knob = std::unique_ptr<Drawable>(Drawable::createFromImageData(BinaryData::KnobLarge_svg, BinaryData::KnobLarge_svgSize));
    medium_button = std::unique_ptr<Drawable>(Drawable::createFromImageData(BinaryData::ButtonMedium_svg, BinaryData::ButtonMedium_svgSize));
    button_on = std::unique_ptr<Drawable> (Drawable::createFromImageData(BinaryData::ButtonSmallActive_svg, BinaryData::ButtonSmallActive_svgSize));
    button_off = std::unique_ptr<Drawable> (Drawable::createFromImageData(BinaryData::ButtonSmall_svg, BinaryData::ButtonSmall_svgSize));
    
    
}
void TheSauceLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider & slider)
{
    //TODO: pretty trivial, draw the PAth of the Rotary::Slider
    auto radius = jmin (width / 2, height / 2) - 4.0f;
    auto centreX = x + width  * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    
    // fill
    //g.setColour (Colour(112,112,112));
    //g.fillEllipse (rx, ry, rw, rw);
    // outline
    //knob_Large->drawWithin(g, slider.getLocalBounds().toFloat(), RectanglePlacement::stretchToFit,1);
    //g.setColour (Colour(37,37,37));
    //g.drawEllipse (rx, ry, rw, rw, 1.0f);
    //DRAW IMAGE HERE
    large_knob->drawWithin(g,slider.getLocalBounds().toFloat(),RectanglePlacement::stretchToFit,1);
    
    Path p;
    auto pointerLength = radius * 0.50f;
    auto pointerThickness = 4.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
    
    g.setColour (Colour(242,87,26));
    g.fillPath (p);
}
void TheSauceLookAndFeel::drawLinearSliderBackground (Graphics&, int x, int y, int width, int height,
                                 float sliderPos, float minSliderPos, float maxSliderPos,
                                 const Slider::SliderStyle, Slider&)
{
    
}
void TheSauceLookAndFeel::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                                bool isMouseOverButton, bool isButtonDown) {
    auto buttonArea = button.getLocalBounds();
    medium_button->drawWithin(g, button.getLocalBounds().toFloat(), RectanglePlacement::stretchToFit, 1);
    
    
}

Typeface::Ptr TheSauceLookAndFeel::getTypefaceForFont(const Font &) {
    //TODO Fx this, the typeface should be GOTHAM-BOOK, oveerride typeface only for the TOOLBAR?
    //GOTHAM BLACK
    return Typeface::createSystemTypefaceFor(BinaryData::GothamBlack_otf, BinaryData::GothamBlack_otfSize);
}

void     TheSauceLookAndFeel::drawToggleButton (Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    
   
        if(shouldDrawButtonAsDown)
            button_on->drawWithin(g, button.getLocalBounds().toFloat(), RectanglePlacement::stretchToFit, 1);
    
        else
            button_off->drawWithin(g, button.getLocalBounds().toFloat(), RectanglePlacement::stretchToFit,1);
    
}

void     TheSauceLookAndFeel::drawTickBox (Graphics& g, Component &, float x, float y, float w, float h, bool ticked, bool isEnabled, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    
    
    
}

OtherLookAndFeel::OtherLookAndFeel()
{
    button_off = std::unique_ptr<Drawable>(Drawable::createFromImageData(BinaryData::ButtonSmall_svg, BinaryData::ButtonSmall_svgSize));
    button_on = std::unique_ptr<Drawable>(Drawable::createFromImageData(BinaryData::ButtonSmallActive_svg, BinaryData::ButtonSmallActive_svgSize));
    
    
    
}

void OtherLookAndFeel::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                           bool isMouseOverButton, bool isButtonDown)
{
    auto state = button.getToggleState();
    
    if(state)
        button_on->drawWithin(g, button.getLocalBounds().toFloat(), RectanglePlacement::stretchToFit, 1);
    
    else
        button_off->drawWithin(g, button.getLocalBounds().toFloat(), RectanglePlacement::stretchToFit,1);
    
}

Typeface::Ptr OtherLookAndFeel::getTypefaceForFont(const Font &)
{
     return Typeface::createSystemTypefaceFor(BinaryData::GothamBlack_otf, BinaryData::GothamBlack_otfSize);
}

LargeButtonLookAndFeel::LargeButtonLookAndFeel()
{
    large_button = std::unique_ptr<Drawable> (Drawable::createFromImageData(BinaryData::ButtonLarge_svg, BinaryData::ButtonLarge_svgSize));
}

void LargeButtonLookAndFeel::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                           bool isMouseOverButton, bool isButtonDown)
{
    auto buttonArea = button.getLocalBounds();
    large_button->drawWithin(g, button.getLocalBounds().toFloat(), RectanglePlacement::stretchToFit, 1);
}

Typeface::Ptr LargeButtonLookAndFeel::getTypefaceForFont(const Font & )
{
    return Typeface::createSystemTypefaceFor(BinaryData::GothamBlack_otf, BinaryData::GothamBlack_otfSize);
}
IconLookAndFeel::IconLookAndFeel()
{
    setColour(TextButton::buttonColourId, Colour(21, 21, 21));
    
}
IconLookAndFeel::~IconLookAndFeel()
{
    
}

Typeface::Ptr IconLookAndFeel::getTypefaceforFont(const Font &)
{
    return Typeface::createSystemTypefaceFor(BinaryData::FontAwesome_otf,BinaryData::FontAwesome_otfSize );
}
Font IconLookAndFeel::getTextButtonFont(TextButton &, int buttonHeight)
{
    Font fontAwesome(Typeface::createSystemTypefaceFor(BinaryData::FontAwesome_otf, BinaryData::FontAwesome_otfSize));
    
    return fontAwesome;
}

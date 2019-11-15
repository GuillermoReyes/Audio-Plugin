/*
  ==============================================================================

    State.h
    Created: 28 Nov 2018 6:36:55pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"


//Borowed from github.com/johnflynnjohnflynn

void saveStateToXml (const AudioProcessor& processor, XmlElement& xml);
void loadStateFromXml (const XmlElement& xml, AudioProcessor& processor);


class StateAB
{
public:
    explicit StateAB (AudioProcessor& p);
    
    void toggleAB();
    void copyAB();
    
private:
    
    AudioProcessor& pluginProcessor;
    XmlElement ab {"AB"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StateAB);
    
    
    
    
};

void createFileIfNonExistant (const File& file);
void parseFileToXmlElement (const File& file, XmlElement& xml);
void writeXmlElementToFile (const XmlElement& xml, File& file);
String getNextAvailablePresetID (const XmlElement& presetXml);

class StatePresets
{
public:
    StatePresets (AudioProcessor& proc, const String& presetFileLocation);
    ~StatePresets();
    
    void savePreset (const String& presetName); // preset already exists? confirm overwrite
    void loadPreset (int presetID);
    void deletePreset();
    
    StringArray getPresetNames() const;
    int getNumPresets() const;
    int getCurrentPresetId() const;
    
private:
    AudioProcessor& pluginProcessor;
    XmlElement presetXml {"PRESETS"}; // local, in-plugin representation
    File presetFile;                  // on-disk representation
    int currentPresetID {0};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatePresets);
};
//TODO :
//Incude the followng in the GLobal Plugin Editor

class StateComponent  : public Component,
public Button::Listener,
public ComboBox::Listener
{
public:
    StateComponent (StateAB& sab, StatePresets& sp);
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    StateAB&      procStateAB;
    StatePresets& procStatePresets;
    
    TextButton toggleABButton;
    TextButton copyABButton;
    ComboBox   presetBox;
    TextButton savePresetButton;
    TextButton deletePresetButton;
    
    void buttonClicked (Button* clickedButton) override;
    void comboBoxChanged (ComboBox* changedComboBox) override;
    
    void refreshPresetBox();
    void ifPresetActiveShowInBox();
    void deletePresetAndRefresh();
    void savePresetAlertWindow();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StateComponent);
};


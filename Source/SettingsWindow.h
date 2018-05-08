/*
  ==============================================================================

    SettingsWindow.h
    Created: 4 Apr 2018 3:39:27pm
    Author:  Niccolo'

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SettingsWindow    : public Component
{
public:
    SettingsWindow();
    ~SettingsWindow();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsWindow)
};

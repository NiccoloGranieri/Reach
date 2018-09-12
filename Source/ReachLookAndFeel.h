/*
  ==============================================================================

    ReachLookAndFeel.h
    Created: 17 May 2018 12:44:57pm
    Author:  Niccolo'

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class ReachLookAndFeel    : public LookAndFeel_V4
{
public:
    ReachLookAndFeel();
    ~ReachLookAndFeel();

	void drawLabel(Graphics&, Label&) override;

private:

	void setupColours();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReachLookAndFeel)
};

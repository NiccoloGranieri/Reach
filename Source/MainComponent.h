/*
  ==============================================================================

  MainComponent.h
  Created: 18 Jan 2018 2:04:28pm
  Author:  Niccolò

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Leap.h"
#include "LeapListener.h"
#include "SettingsWindow.h"

class MainContentComponent   : public Component, 
	                           public Timer
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
	Leap::Controller controller;
	ScopedPointer<LeapListener> leapListener;

	SettingsWindow settings;

	String currentSizeAsString;

	OSCSender sender;

	Leap::HandList handList;

	void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

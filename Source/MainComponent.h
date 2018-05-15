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

class MainContentComponent   : public Component, 
	                           public Timer,
	                           public Label::Listener
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
	Leap::HandList handList;

	//==============================================================================
	OSCSender sender;

	//==============================================================================
	void timerCallback() override;

	//==============================================================================
	Label ipAddress;
	Label port;

	//==============================================================================
	String currentSizeAsString;

	//==============================================================================
	String senderIP = "127.0.0.1";
	int senderPort = 5678;
	int throttleTime = 200;

	void labelTextChanged(Label* labelThatHasChanged) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

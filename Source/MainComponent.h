/*
  ==============================================================================

  MainComponent.h
  Created: 18 Jan 2018 2:04:28pm
  Author:  Niccolò

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Leap.h"

class MainContentComponent   : public Component,
	                           public Timer,
	                           public Label::Listener
{
public:
    //==============================================================================
    MainContentComponent ();
	~MainContentComponent() = default;

    void paint (Graphics&) override;
    void resized() override;

private:
	//==============================================================================
	Leap::Controller controller;
	int64 lastFrameId = -1;

    //==============================================================================
	bool leftLed = false;
	bool rightLed = false;

	//==============================================================================
	OSCSender sender;

	//==============================================================================
	void timerCallback() override;
	void sendNormalisedValues(Leap::Hand hand, StringRef handedness);
	void sendDenormalisedValues(Leap::Hand hand, StringRef handedness);

	//==============================================================================
	Label ipAddress;
	Label port;
	Label throttleSpeed;
	Label normValueButtonLabel{ {}, "Normalised Values" };
	ToggleButton normValueButton;
	Label hmdButtonLabel{ {}, "Head Mounted" };
	ToggleButton hmdButton;

	//==============================================================================
	String currentSizeAsString;

	//==============================================================================
	String senderIP = "127.0.0.1";
	int senderPort = 5678;
	int throttleTime = 200;

	void labelTextChanged(Label* labelThatHasChanged) override;

    //==============================================================================
    const StringArray jointTypes = { "/TYPE_THUMB", "/TYPE_INDEX", "/TYPE_MIDDLE", "/TYPE_RING", "/TYPE_PINKY"};
    const StringArray joints = { "/knuckle", "/joint1", "/joint2", "/joint3"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

/*
  ==============================================================================

    LeapListener.h
    Created: 18 Jan 2018 2:04:28pm
    Author:  Jefferson

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Leap.h"

//==============================================================================
/*
*/
class LeapListener : public Leap::Listener
{
public:
	LeapListener (ValueTree);
	~LeapListener();

	void onConnect(const Leap::Controller&) override;
	void onFrame(const Leap::Controller&) override;

	bool isConnected()		{ return connected; }

private:
	ValueTree tree;
	ValueTree leftHand;
	ValueTree rightHand;
	bool connected = false;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeapListener)
};
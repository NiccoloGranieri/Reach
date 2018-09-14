/*
  ==============================================================================

    LeapListener.h
    Created: 18 Jan 2018 2:04:28pm
    Author:  Jefferson

  ==============================================================================
*/

#pragma once

#include "Leap.h"
#include "LeapHands.h"

//==============================================================================
/*
*/
class LeapListener : public Leap::Listener
{
public:
	LeapListener ();
	~LeapListener();

	void onConnect(const Leap::Controller&) override;
	void onFrame(const Leap::Controller&) override;

private:
	SharedResourcePointer<LeapHands> handsArray;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeapListener)
};
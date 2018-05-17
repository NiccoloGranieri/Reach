/*
  ==============================================================================

    LeapListener.cpp
    Created: 18 Jan 2018 2:04:28pm
    Author:  Jefferson

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LeapListener.h"

using namespace Leap;

//==============================================================================
LeapListener::LeapListener(HandList& h)
: handList (h)
{
}

LeapListener::~LeapListener()
{
}

void LeapListener::onConnect (const Controller& controller)
{
}

void LeapListener::onFrame (const Controller& controller)
{
	const Frame frame = controller.frame();
	handList = frame.hands();
}

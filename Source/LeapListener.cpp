/*
  ==============================================================================

    LeapListener.cpp
    Created: 18 Jan 2018 2:04:28pm
    Author:  Jefferson

  ==============================================================================
*/

#include "LeapListener.h"

using namespace Leap;

//==============================================================================
LeapListener::LeapListener()
{
}

LeapListener::~LeapListener() = default;

void LeapListener::onConnect (const Controller& controller)
{
}

void LeapListener::onFrame (const Controller& controller)
{
	const auto frame = controller.frame();
	//handList = frame.hands();
}

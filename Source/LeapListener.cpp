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
LeapListener::LeapListener()
{
	
}

LeapListener::~LeapListener()
{
}

void LeapListener::onConnect (const Controller& controller)
{
	DBG ("Connected");
}

void LeapListener::onFrame (const Controller& controller)
{
	DBG ("Frame available");

	const Frame frame = controller.frame();

	DBG ("Frame id: " + (String)frame.id());
	DBG (", timestamp: " + (String)frame.timestamp());
	DBG (", hands: " + (String)frame.hands().count());
	DBG (", fingers: " + (String)frame.fingers().count());
	DBG(", testdata: " + (String)frame.hands().leftmost().palmPosition().x); 

	
}

/*
  ==============================================================================

    LeapListener.cpp
    Created: 18 Jan 2018 2:04:28pm
    Author:  Jefferson

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LeapListener.h"
#include "Identifiers.h"

using namespace Leap;

//==============================================================================
LeapListener::LeapListener (ValueTree v)
:	tree (v)
{
	leftHand = tree.getChildWithName(IDs::LEFTHAND);
	rightHand = tree.getChildWithName(IDs::RIGHTHAND);
}

LeapListener::~LeapListener()
{
}

void LeapListener::onConnect (const Controller& controller)
{
	DBG ("Connected");
	connected = true;
}

void LeapListener::onFrame (const Controller& controller)
{
	DBG ("Frame available");

	const Frame frame = controller.frame();
	auto palmPosition = frame.hands().leftmost().palmPosition();

	leftHand.setProperty(IDs::palmPositionX, palmPosition.x, nullptr);
	leftHand.setProperty(IDs::palmPositionY, palmPosition.y, nullptr);
	leftHand.setProperty(IDs::palmPositionZ, palmPosition.z, nullptr);
	
	
	//DBG((int)leftHand.getPropertyAsValue(IDs::palmPosition, nullptr).getValue().getArray()->getUnchecked(0));
	/*DBG ("Frame id: " + (String)frame.id());
	DBG (", timestamp: " + (String)frame.timestamp());
	DBG (", hands: " + (String)frame.hands().count());
	DBG (", fingers: " + (String)frame.fingers().count());
	DBG(", testdata: " + (String)frame.hands().leftmost().palmPosition().x);*/

	
}

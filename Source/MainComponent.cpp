/*
  ==============================================================================

  MainComponent.cpp
  Created: 18 Jan 2018 2:04:28pm
  Author:  Niccolò

  ==============================================================================
*/

#include "MainComponent.h"
#include "Leap.h"

//==============================================================================
MainContentComponent::MainContentComponent()
{
	Component::setBoundsRelative(0.2f, 0.2f, 0.75f, 0.75f);

	leapListener = new LeapListener (handList);
	controller.addListener (*leapListener);
	addAndMakeVisible (settings);

	sender.connect ("127.0.0.1", 5678);

	startTimer(200);

	/*DBG(", timestamp: " + (String)frame.timestamp());
	DBG(", hands: " + (String)frame.hands().count());
	DBG(", fingers: " + (String)frame.fingers().count());
	DBG(", testdata: " + (String)frame.hands().leftmost().palmPosition().x);*/
}

MainContentComponent::~MainContentComponent()
{
	controller.removeListener (*leapListener);
}

void MainContentComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText (currentSizeAsString, getLocalBounds(), Justification::centred, true);

}

void MainContentComponent::resized()
{
	auto area = getLocalBounds();
	settings.setBounds (area);
}

void MainContentComponent::timerCallback()
{
for (auto& hand : handList)
	{
		String handedness;

		if (hand.isLeft())
		{
			handedness = "/Lefthand";
		}

		else
		{
			handedness = "/Righthand";
		}

		OSCMessage m = OSCMessage(handedness + "/palmTest");
		m.addFloat32(hand.stabilizedPalmPosition().x);
		m.addFloat32(hand.stabilizedPalmPosition().y);
		m.addFloat32(hand.stabilizedPalmPosition().z);
		sender.send(m);

	}
}
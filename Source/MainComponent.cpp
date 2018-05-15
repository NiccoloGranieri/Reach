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
	Component::setBoundsRelative(0.025f, 0.025f, 0.15f, 0.15f);

	leapListener = new LeapListener (handList);
	controller.addListener (*leapListener);

	sender.connect (senderIP, senderPort);

	startTimer(throttleTime);

	addAndMakeVisible(ipAddress);
	addAndMakeVisible(port);

	ipAddress.addListener(this);
	port.addListener(this);

	ipAddress.setFont(Font(22.0f));
	ipAddress.setJustificationType(Justification::centred);
	ipAddress.setColour(Label::ColourIds::backgroundColourId, Colours::white);
	ipAddress.setColour(Label::ColourIds::textColourId, Colours::black);
	ipAddress.setColour(Label::ColourIds::textWhenEditingColourId, Colours::black);
	ipAddress.setEditable(true);
	ipAddress.setText(senderIP, dontSendNotification);

	port.setFont(Font(22.0f));
	port.setJustificationType(Justification::centred);
	port.setColour(Label::ColourIds::backgroundColourId, Colours::white);
	port.setColour(Label::ColourIds::textColourId, Colours::black);
	port.setColour(Label::ColourIds::textWhenEditingColourId, Colours::black);
	port.setEditable(true);
	port.setText((String)senderPort, dontSendNotification);

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
	auto area = getLocalBounds().reduced(proportionOfWidth(0.03), proportionOfHeight(0.03));
	area.removeFromTop(proportionOfHeight(0.2));
	auto labelarea = area.removeFromTop(proportionOfHeight(0.2));
	ipAddress.setBounds(labelarea.removeFromLeft(proportionOfWidth(0.4)));
	port.setBounds(labelarea.removeFromRight(proportionOfWidth(0.4)));
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

void MainContentComponent::labelTextChanged(Label* labelThatHasChanged)
{
	if (labelThatHasChanged == &ipAddress)
		senderIP = labelThatHasChanged->getText();

	if (labelThatHasChanged == &port)
		senderPort = (int)labelThatHasChanged->getText().getIntValue();
}
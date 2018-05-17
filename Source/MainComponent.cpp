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
	addAndMakeVisible(throttleSpeed);

	ipAddress.addListener(this);
	port.addListener(this);
	throttleSpeed.addListener(this);

	ipAddress.setFont(Font(22.0f));
	ipAddress.setEditable(true);
	ipAddress.setText(senderIP, dontSendNotification);

	port.setFont(Font(22.0f));
	port.setEditable(true);
	port.setText((String)senderPort, dontSendNotification);

	throttleSpeed.setFont(Font(22.0f));
	throttleSpeed.setEditable(true);
	throttleSpeed.setText((String)throttleTime, dontSendNotification);
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

	g.setColour(Colours::red);
	g.drawEllipse(getWidth() / 4, (getHeight() / 3) * 2, getWidth() / 100, getWidth() / 100, 5);
	g.drawEllipse((getWidth() / 4) * 3, (getHeight() / 3) * 2, getWidth() / 100, getWidth() / 100, 5);

	if (leftLed)
	{
		g.setColour(Colours::green);
		g.drawEllipse(getWidth() / 4, (getHeight() / 3) * 2, getWidth() / 100, getWidth() / 100, 5);
	}
	if (rightLed)
	{
		g.setColour(Colours::green);
		g.drawEllipse((getWidth() / 4) * 3, (getHeight() / 3) * 2, getWidth() / 100, getWidth() / 100, 5);
	}

}

void MainContentComponent::resized()
{

	auto area = getLocalBounds().reduced(proportionOfWidth(0.03), proportionOfHeight(0.03));
	area.removeFromTop(proportionOfHeight(0.2));
	auto labelarea = area.removeFromTop(proportionOfHeight(0.425));
	auto labelarea1 = labelarea.removeFromBottom(proportionOfHeight(0.2));
	auto spacearea = labelarea.removeFromBottom(proportionOfHeight(0.025));
	
	ipAddress.setBounds(labelarea.removeFromLeft(proportionOfWidth(0.4)));
	port.setBounds(labelarea.removeFromRight(proportionOfWidth(0.4)));

	labelarea1.removeFromRight(proportionOfWidth(0.27));
	throttleSpeed.setBounds(labelarea1.removeFromRight(proportionOfWidth(0.4)));
}

void MainContentComponent::timerCallback()
{

	leftLed = false;
	rightLed = false;

	for (auto& hand : handList)
	{
		String handedness;

		if (hand.isLeft())
		{
			leftLed = true;
			handedness = "/Lefthand";
		}

		else
		{
			rightLed = true;
			handedness = "/Righthand";
		}

		OSCMessage m = OSCMessage(handedness + "/palmTest");
		m.addFloat32(hand.stabilizedPalmPosition().x);
		m.addFloat32(hand.stabilizedPalmPosition().y);
		m.addFloat32(hand.stabilizedPalmPosition().z);
		sender.send(m);

	}

	repaint();
}

void MainContentComponent::labelTextChanged(Label* labelThatHasChanged)
{
	if (labelThatHasChanged == &ipAddress)
		senderIP = labelThatHasChanged->getText();

	if (labelThatHasChanged == &port)
		senderPort = (int)labelThatHasChanged->getText().getIntValue();

	if (labelThatHasChanged == &throttleSpeed)
	{
		throttleTime = (int)labelThatHasChanged->getText().getIntValue();
		startTimer(throttleTime);
	}
}
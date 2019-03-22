/*
  ==============================================================================

  MainComponent.cpp
  Created: 18 Jan 2018 2:04:28pm
  Author:  Niccolò

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent ()
{
	setBoundsRelative(0.025f, 0.025f, 0.15f, 0.15f);

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

MainContentComponent::~MainContentComponent() = default;

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
	if (! controller.isConnected())
		return;

	const auto& frame = controller.frame();

	if (frame.id() == lastFrameId)
		return;

	const auto& hands = frame.hands();

	leftLed = false;
	rightLed = false;

	for (auto& hand : hands)
	{
		String handedness;

		if (hand.isLeft())
		{
			leftLed = true;
			handedness = "/Left";
		}

		else
		{
			rightLed = true;
			handedness = "/Right";
		}

		OSCMessage oscPalm = OSCMessage(handedness + "/palm");
		oscPalm.addFloat32(hand.stabilizedPalmPosition().x);
		oscPalm.addFloat32(hand.stabilizedPalmPosition().y);
		oscPalm.addFloat32(hand.stabilizedPalmPosition().z);
		sender.send(oscPalm);

		OSCMessage oscWrist = OSCMessage(handedness + "/wrist");
		oscWrist.addFloat32(hand.wristPosition().x);
		oscWrist.addFloat32(hand.wristPosition().y);
		oscWrist.addFloat32(hand.wristPosition().z);
		sender.send(oscWrist);

		OSCMessage oscGrab = OSCMessage(handedness + "/grab");
		oscGrab.addFloat32(hand.grabAngle());
		sender.send(oscGrab);

		OSCMessage oscRotation = OSCMessage(handedness + "/rotation");
		oscRotation.addFloat32(hand.palmNormal().x);
		oscRotation.addFloat32(hand.palmNormal().y);
		oscRotation.addFloat32(hand.palmNormal().z);
		sender.send(oscRotation);



		for (auto& finger : hand.fingers())
		{
            sender.send ({ handedness + jointTypes[finger.type()] + "/extended", finger.isExtended() });
            
			for (auto i = 0; i <= 3; i++)
			{
				auto boneType = static_cast<Leap::Bone::Type>(i);
				auto bone = finger.bone(boneType);
				OSCMessage oscJoint = OSCMessage(String(handedness + jointTypes[finger.type()] + joints[i]));
				oscJoint.addFloat32(bone.nextJoint().x);
				oscJoint.addFloat32(bone.nextJoint().y);
				oscJoint.addFloat32(bone.nextJoint().z);
			}
		}
	}

	OSCMessage presenceL = OSCMessage("/Left/presence");
	presenceL.addInt32(leftLed);
	sender.send(presenceL);

	OSCMessage presenceR = OSCMessage("/Right/presence");
	presenceR.addInt32(rightLed);
	sender.send(presenceR);

	lastFrameId = frame.id();

	repaint();
}

void MainContentComponent::labelTextChanged(Label* labelThatHasChanged)
{
	if (labelThatHasChanged == &ipAddress)
	{
		senderIP = labelThatHasChanged->getText();
		sender.disconnect();
		sender.connect (senderIP, senderPort);
	}

	if (labelThatHasChanged == &port)
		senderPort = (int)labelThatHasChanged->getText().getIntValue();

	if (labelThatHasChanged == &throttleSpeed)
	{
		throttleTime = (int)labelThatHasChanged->getText().getIntValue();
		startTimer(throttleTime);
	}
}

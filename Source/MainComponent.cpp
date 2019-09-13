/*
  ==============================================================================

  MainComponent.cpp
  Created: 18 Jan 2018 2:04:28pm
  Author:  Niccolò

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
const float grabAndJNormalise(float value, const NormalisableRange<float>& range)
{
	const auto normalisedValue = range.convertTo0to1(value);
	return jmap(normalisedValue, -1.0f, 1.0f);
}

const float grabAndNormalise(float value, const NormalisableRange<float>& range)
{
	const auto normalisedValue = range.convertTo0to1(value);
	return normalisedValue;
}

//==============================================================================
MainContentComponent::MainContentComponent ()
{
	setBoundsRelative(0.025f, 0.025f, 0.25f, 0.25f);

	sender.connect (senderIP, senderPort);

	startTimer(throttleTime);

	addAndMakeVisible(ipAddress);
	ipAddress.setJustificationType(Justification::centred);
	addAndMakeVisible(port);
	port.setJustificationType(Justification::centred);
	addAndMakeVisible(throttleSpeed);
	throttleSpeed.setJustificationType(Justification::centred);
	addAndMakeVisible(normValueButton);
	addAndMakeVisible(normValueButtonLabel);
	normValueButtonLabel.attachToComponent(&normValueButton, true);
	normValueButtonLabel.setColour(Label::backgroundColourId, Colours::transparentBlack);
	normValueButtonLabel.setColour(Label::textColourId, Colours::white);
	addAndMakeVisible(hmdButton);
	addAndMakeVisible(hmdButtonLabel);
	hmdButtonLabel.setColour(Label::backgroundColourId, Colours::transparentBlack);
	hmdButtonLabel.setColour(Label::textColourId, Colours::white);

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

	hmdButton.onStateChange = [this] {controller.setPolicy(hmdButton.getToggleState() ? Leap::Controller::POLICY_OPTIMIZE_HMD 
																					  : Leap::Controller::POLICY_DEFAULT); };

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

	normValueButton.setBounds(area.removeFromRight(23).reduced(0, proportionOfHeight(0.08)));
	hmdButton.setBounds(area.removeFromLeft(23).reduced(0, proportionOfHeight(0.08)));
	hmdButtonLabel.setBounds(area.removeFromLeft(proportionOfWidth(0.3)));
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

		normValueButton.getToggleState() ? sendNormalisedValues(hand, handedness) : sendDenormalisedValues(hand, handedness);


		OSCMessage oscGrab = OSCMessage(handedness + "/grab");
		oscGrab.addFloat32(hand.grabAngle());
		sender.send(oscGrab);
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

void MainContentComponent::sendDenormalisedValues(Leap::Hand hand, StringRef handedness)
{
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

	OSCMessage oscRotation = OSCMessage(handedness + "/rotation");
	oscRotation.addFloat32(hand.palmNormal().x);
	oscRotation.addFloat32(hand.palmNormal().y);
	oscRotation.addFloat32(hand.palmNormal().z);
	sender.send(oscRotation);



	for (auto& finger : hand.fingers())
	{
		sender.send({ handedness + jointTypes[finger.type()] + "/extended", finger.isExtended() });

		for (auto i = 0; i <= 3; i++)
		{
			auto boneType = static_cast<Leap::Bone::Type>(i);
			auto bone = finger.bone(boneType);
			OSCMessage oscJoint = OSCMessage(String(handedness + jointTypes[finger.type()] + joints[i]));
			oscJoint.addFloat32(bone.nextJoint().x);
			oscJoint.addFloat32(bone.nextJoint().y);
			oscJoint.addFloat32(bone.nextJoint().z);
			sender.send(oscJoint);
		}
	}
}

void MainContentComponent::sendNormalisedValues(Leap::Hand hand, StringRef handedness)
{
	auto palmPosition = hand.stabilizedPalmPosition();

	OSCMessage oscPalm = OSCMessage(handedness + "/palm");
	oscPalm.addFloat32(grabAndJNormalise(palmPosition.x, xnzAxisRange));
	oscPalm.addFloat32(grabAndNormalise(palmPosition.y, yAxisRange));
	oscPalm.addFloat32(grabAndJNormalise(palmPosition.z, xnzAxisRange));
	sender.send(oscPalm);

	auto wristPosition = hand.wristPosition();

	OSCMessage oscWrist = OSCMessage(handedness + "/wrist");
	oscWrist.addFloat32(grabAndJNormalise(wristPosition.x, xnzAxisRange));
	oscWrist.addFloat32(grabAndNormalise(wristPosition.y, yAxisRange));
	oscWrist.addFloat32(grabAndJNormalise(wristPosition.z, xnzAxisRange));
	sender.send(oscWrist);

	auto palmRotation = hand.palmNormal();

	OSCMessage oscRotation = OSCMessage(handedness + "/rotation");

	oscRotation.addFloat32(palmRotation.x);
	oscRotation.addFloat32(palmRotation.y);
	oscRotation.addFloat32(palmRotation.z);
	sender.send(oscRotation);

	for (auto& finger : hand.fingers())
	{
		sender.send({ handedness + jointTypes[finger.type()] + "/extended", finger.isExtended() });

		for (auto i = 0; i <= 3; i++)
		{
			auto boneType = static_cast<Leap::Bone::Type>(i);
			auto bone = finger.bone(boneType);

			auto jointPosition = bone.nextJoint();

			OSCMessage oscJoint = OSCMessage(String(handedness + jointTypes[finger.type()] + joints[i]));
			oscJoint.addFloat32(grabAndJNormalise(jointPosition.x, xnzAxisRange));
			oscJoint.addFloat32(grabAndNormalise(jointPosition.y, yAxisRange));
			oscJoint.addFloat32(grabAndJNormalise(jointPosition.z, xnzAxisRange));
			sender.send(oscJoint);
		}
	}
}
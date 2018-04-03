/*
  ==============================================================================

  MainComponent.cpp
  Created: 18 Jan 2018 2:04:28pm
  Author:  Niccolò

  ==============================================================================
*/

#include "MainComponent.h"

#include "Identifiers.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
	Component::setBoundsRelative(0.2f, 0.2f, 0.75f, 0.75f);

	rootTree = ValueTree (IDs::REACH);

	rightHand = ValueTree(IDs::RIGHTHAND);
	leftHand = ValueTree(IDs::LEFTHAND);

	rootTree.addChild(leftHand, -1, nullptr);
	rootTree.addChild(rightHand, -1, nullptr);

	rightHand.setProperty(IDs::palmPositionX, 0, nullptr);
	rightHand.setProperty(IDs::palmPositionY, 0, nullptr);
	rightHand.setProperty(IDs::palmPositionZ, 0, nullptr);

	leftHand.setProperty(IDs::palmPositionX, 0, nullptr);
	leftHand.setProperty(IDs::palmPositionY, 0, nullptr);
	leftHand.setProperty(IDs::palmPositionZ, 0, nullptr);

	leapListener = new LeapListener(rootTree);
	controller.addListener(*leapListener);

	sender.connect("127.0.0.1", 5678);

	startTimerHz(200);
}

MainContentComponent::~MainContentComponent()
{
	controller.removeListener(*leapListener);
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

}

void MainContentComponent::timerCallback()
{
	OSCMessage message = OSCMessage("/LeftHand/palmTest");
	message.addInt32((int)leftHand.getProperty(IDs::palmPositionX));
	message.addInt32((int)leftHand.getProperty(IDs::palmPositionY));
	message.addInt32((int)leftHand.getProperty(IDs::palmPositionZ));
	sender.send(message);
}
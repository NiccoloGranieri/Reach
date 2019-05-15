/*
  ==============================================================================

    ReachLookAndFeel.cpp
    Created: 17 May 2018 12:44:57pm
    Author:  Niccolo'

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ReachLookAndFeel.h"

//==============================================================================
ReachLookAndFeel::ReachLookAndFeel()
{
	setupColours();
}

ReachLookAndFeel::~ReachLookAndFeel()
{
}

void ReachLookAndFeel::setupColours()
{
	setColour(Label::backgroundColourId, Colours::white);
	setColour(Label::textColourId, Colours::black);
	setColour(Label::textWhenEditingColourId, Colours::black);
}

void ReachLookAndFeel::drawLabel(Graphics& g, Label& label)
{
	g.fillAll(label.findColour(Label::backgroundColourId));

	if (!label.isBeingEdited())
	{
		auto alpha = label.isEnabled() ? 1.0f : 0.5f;
		const Font font(getLabelFont(label));

		g.setColour(label.findColour(Label::textColourId).withMultipliedAlpha(alpha));
		g.setFont(font);

		Rectangle<int> textArea(label.getBorderSize().subtractedFrom(label.getLocalBounds()));

		g.drawFittedText(label.getText(), textArea, label.getJustificationType(),
			jmax(1, (int)(textArea.getHeight() / font.getHeight())),
			label.getMinimumHorizontalScale());

		g.setColour(label.findColour(Label::outlineColourId).withMultipliedAlpha(alpha));
	}
	else if (label.isEnabled())
	{
		g.setColour(label.findColour(Label::outlineColourId));
	}

	g.drawRect(label.getLocalBounds());
}
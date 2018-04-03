/*
  ==============================================================================

    Identifiers.h
    Created: 3 Apr 2018 11:55:11am
    Author:  Niccolo'

  ==============================================================================
*/

#pragma once

namespace IDs
{
	// enables to replace all the const juce:: etc, with DEFINE_ID
	#define DEFINE_ID(name) const juce::Identifier name (#name);

	DEFINE_ID(REACH)

	DEFINE_ID(LEFTHAND)
	DEFINE_ID(RIGHTHAND)

	DEFINE_ID(palmPositionX)
	DEFINE_ID(palmPositionY)
	DEFINE_ID(palmPositionZ)



	#undef DEFINE_ID
};
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

	DEFINE_ID(LEFTTHUMB)
	DEFINE_ID(LEFTINDEX)
	DEFINE_ID(LEFTMIDDLE)
	DEFINE_ID(LEFTRING)
	DEFINE_ID(LEFTPINKY)

	DEFINE_ID(RIGHTTHUMB)
	DEFINE_ID(RIGHTINDEX)
	DEFINE_ID(RIGHTMIDDLE)
	DEFINE_ID(RIGHTRING)
	DEFINE_ID(RIGHTPINKY)

	DEFINE_ID(palmPositionX)
	DEFINE_ID(palmPositionY)
	DEFINE_ID(palmPositionZ)

	DEFINE_ID(wristPositionX)
	DEFINE_ID(wristPositionY)
	DEFINE_ID(wristPositionZ)

	DEFINE_ID(knuckleX)
	DEFINE_ID(knuckleY)
	DEFINE_ID(knuckleZ)

	DEFINE_ID(jointOneX)
	DEFINE_ID(jointOneY)
	DEFINE_ID(jointOneZ)

	DEFINE_ID(jointTwoX)
	DEFINE_ID(jointTwoY)
	DEFINE_ID(jointTwoZ)

	DEFINE_ID(jointThreeX)
	DEFINE_ID(jointThreeY)
	DEFINE_ID(jointThreeZ)


	#undef DEFINE_ID
};
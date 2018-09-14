#pragma once

#include "JuceHeader.h"
#include <array>

struct LeapBone
{
	std::array<std::atomic<float>, 3> position = {};
	std::atomic<float>& x = position[0];
	std::atomic<float>& y = position[1];
	std::atomic<float>& z = position[2];
};

struct LeapFinger
{
	std::array<LeapBone, 4> fingers;
};

struct LeapWrist
{
	std::array<std::atomic<float>, 3> position = {};
	std::atomic<float>& x = position[0];
	std::atomic<float>& y = position[1];
	std::atomic<float>& z = position[2];
};

struct LeapPalm
{
	std::array<std::atomic<float>, 3> position = {};
	std::atomic<float>& x = position[0];
	std::atomic<float>& y = position[1];
	std::atomic<float>& z = position[2];
};

struct LeapHand
{
	std::array<LeapFinger, 5> fingers;
	std::atomic<bool> isLeft;
	LeapPalm palm;
	LeapWrist wrist;
};

//==============================================================================
struct LeapHands
{
public:
	LeapHands() = default;
	~LeapHands() = default;

	Array<LeapHand> hands;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeapHands)
};

#pragma once

#include "JuceHeader.h"
#include "Leap.h"

//==============================================================================
class LeapLogger : public HighResolutionTimer
{
public:
	//==========================================================================
    LeapLogger ();
    ~LeapLogger();

	//==========================================================================
	void setLogFile (File logFolder);

private:
	//==========================================================================
	std::unique_ptr<FileLogger> logger;
	StringArray logFrameData;
	bool shouldStartNewSession = false;

	int currentSessionNumber = 0;

	//==========================================================================
	Leap::Controller controller;
	int lastFrameId = -1;

	//==========================================================================
	const StringArray jointTypes = { "/TYPE_THUMB", "/TYPE_INDEX", "/TYPE_MIDDLE", "/TYPE_RING", "/TYPE_PINKY" };
	const StringArray joints = { "/knuckle", "/joint1", "/joint2", "/joint3" };
	String dataNames{ "Hand,PalmX,PalmY,PalmZ,WristX,WristY,WristZ,Finger1Bone1X,Finger1Bone1Y,Finger1Bone1Z,Finger1Bone2X,Finger1Bone2Y,Finger1Bone2Z,Finger1Bone3X,Finger1Bone3Y,Finger1Bone3Z,Finger1Bone4X,Finger1Bone4Y,Finger1Bone4Z,Finger2Bone1X,Finger2Bone1Y,Finger2Bone1Z,Finger2Bone2X,Finger2Bone2Y,Finger2Bone2Z,Finger2Bone3X,Finger2Bone3Y,Finger2Bone3Z,Finger2Bone4X,Finger2Bone4Y,Finger2Bone4Z,Finger3Bone1X,Finger3Bone1Y,Finger3Bone1Z,Finger3Bone2X,Finger3Bone2Y,Finger3Bone2Z,Finger3Bone3X,Finger3Bone3Y,Finger3Bone3Z,Finger3Bone4X,Finger3Bone4Y,Finger3Bone4Z,Finger4Bone1X,Finger4Bone1Y,Finger4Bone1Z,Finger4Bone2X,Finger4Bone2Y,Finger4Bone2Z,Finger4Bone3X,Finger4Bone3Y,Finger4Bone3Z,Finger4Bone4X,Finger4Bone4Y,Finger4Bone4Z" };

	//==========================================================================
	void createNewLogFile();

	//==========================================================================
    void hiResTimerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeapLogger)
};

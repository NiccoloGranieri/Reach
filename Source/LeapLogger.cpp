#include "JuceHeader.h"
#include "LeapLogger.h"

//==============================================================================
LeapLogger::LeapLogger (File& logFile)
: logger (logFile, {})
{
	logger.writeToLog (ProjectInfo::projectName + String(" Data Log"));
	logger.writeToLog (newLine);
	logger.writeToLog (String("////=============================================================================="));
	logger.writeToLog(newLine);
}

LeapLogger::~LeapLogger()
{
	stopTimer();
}

//==============================================================================
void LeapLogger::hiResTimerCallback()
{
	if (! controller.isConnected())
	{
		return;
	}

	const auto& frame = controller.frame();

	if (frame.id() == lastFrameId)
		return;

	const auto& hands = frame.hands();

	for (auto& hand : hands)
	{
		writeToLog(hand.toString());

		if (hand.isLeft())
			writeToLog ("Left");
		else
			writeToLog("Right");

	    writeToLog(static_cast<String> (hand.stabilizedPalmPosition().x));
		writeToLog(static_cast<String> (hand.stabilizedPalmPosition().y));
		writeToLog(static_cast<String> (hand.stabilizedPalmPosition().z));

		writeToLog(static_cast<String> (hand.wristPosition().x));
		writeToLog(static_cast<String> (hand.wristPosition().y));
		writeToLog(static_cast<String> (hand.wristPosition().z));

		for (auto& finger : hand.fingers())
		{
			for (auto i = 0; ++i < 4;)
			{
				const auto& boneType = static_cast<Leap::Bone::Type> (i);
				const auto& bone = finger.bone (boneType);
				writeToLog(static_cast<String> (bone.nextJoint().x));
				writeToLog(static_cast<String> (bone.nextJoint().y));
				writeToLog(static_cast<String> (bone.nextJoint().z));
			}
		}
	}

	logger.writeToLog (newLine);

	lastFrameId = frame.id();
}

//==============================================================================
void LeapLogger::writeToLog (StringRef content)
{
	logger.writeToLog(content);
	logger.writeToLog(",");
}

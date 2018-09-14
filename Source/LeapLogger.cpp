#include "JuceHeader.h"
#include "LeapLogger.h"

//==============================================================================
LeapLogger::LeapLogger (File& logFile)
: logger (logFile, {})
{
	logFrameData.ensureStorageAllocated(200);
}

LeapLogger::~LeapLogger()
{
	stopTimer();
}

//==============================================================================
void LeapLogger::hiResTimerCallback()
{
	if (! controller.isConnected())
		return;

	const auto& frame = controller.frame();

	if (frame.id() == lastFrameId)
		return;

	const auto& hands = frame.hands();

	if (hands.isEmpty())
		return;

	logFrameData.clearQuick();

	for (auto& hand : hands)
	{
		if (hand.isLeft())
			logFrameData.add("Left");
		else
			logFrameData.add("Right");

		logFrameData.add(static_cast<String> (hand.stabilizedPalmPosition().x));
		logFrameData.add(static_cast<String> (hand.stabilizedPalmPosition().y));
		logFrameData.add(static_cast<String> (hand.stabilizedPalmPosition().z));

		logFrameData.add(static_cast<String> (hand.wristPosition().x));
		logFrameData.add(static_cast<String> (hand.wristPosition().y));
		logFrameData.add(static_cast<String> (hand.wristPosition().z));

		for (auto& finger : hand.fingers())
		{
			for (auto i = 0; ++i < 4;)
			{
				const auto& boneType = static_cast<Leap::Bone::Type> (i);
				const auto& bone = finger.bone (boneType);
				logFrameData.add(static_cast<String> (bone.nextJoint().x));
				logFrameData.add(static_cast<String> (bone.nextJoint().y));
				logFrameData.add(static_cast<String> (bone.nextJoint().z));
			}
		}
	}

	logger.writeToLog (logFrameData.joinIntoString (","));

	lastFrameId = frame.id();
}
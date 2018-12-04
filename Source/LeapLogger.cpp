#include "JuceHeader.h"
#include "LeapLogger.h"

//==============================================================================
LeapLogger::LeapLogger ()
{
	createNewLogFile ();

	startTimer (5);
}

LeapLogger::~LeapLogger()
{
	stopTimer();
}

//==============================================================================
void LeapLogger::createNewLogFile()
{
	DBG("CREATING FILE");
	const auto logFilename = String(String(ProjectInfo::projectName)
		+ "_Session" + String (currentSessionNumber) + "_Log_"
		+ Time::getCurrentTime().formatted("%d-%m-%Y_%H-%M-%S"));

	const auto logExtension = String(".csv");

	auto logFile = File::getSpecialLocation(File::SpecialLocationType::userDesktopDirectory)
		.getChildFile(logFilename + logExtension);

	Logger::setCurrentLogger(nullptr);
	logger.reset(new FileLogger(logFile, {}));
	Logger::setCurrentLogger(logger.get());

	logger->logMessage(ProjectInfo::projectName + String(" Data Log"));
	logger->logMessage({});
	logger->logMessage(dataNames);
	logger->logMessage({});

	logFrameData.ensureStorageAllocated(200);

	++currentSessionNumber;
	DBG(currentSessionNumber);
	DBG(logFilename);
}

//==============================================================================
void LeapLogger::hiResTimerCallback()
{
	if (! controller.isConnected())
	{
		DBG("DISCONNECT");
		shouldStartNewSession = true;
		return;
	}

    if (shouldStartNewSession && controller.isConnected())
    {
		DBG("NEW FILE INSIDE CALLBACK");
		createNewLogFile();
		shouldStartNewSession = false;
		return;
    }

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

	logger->logMessage (logFrameData.joinIntoString (","));

	lastFrameId = frame.id();
}

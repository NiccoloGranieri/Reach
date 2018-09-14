#pragma once

#include "JuceHeader.h"
#include "Leap.h"

//==============================================================================
class LeapLogger : public HighResolutionTimer
{
public:
	//==========================================================================
    explicit LeapLogger (File& logFile);
    ~LeapLogger();

	//==========================================================================
	FileLogger& getLogger() noexcept
	{ return logger; }

    void startLogger()
	{ startTimer(5); }

	//==========================================================================
	void setLogFile (File logFolder);

private:
	//==========================================================================
	FileLogger logger;
	StringArray logFrameData;

	//==========================================================================
	Leap::Controller controller;
	int lastFrameId = -1;

	//==========================================================================
	const StringArray jointTypes = { "/TYPE_THUMB", "/TYPE_INDEX", "/TYPE_MIDDLE", "/TYPE_RING", "/TYPE_PINKY" };
	const StringArray joints = { "/knuckle", "/joint1", "/joint2", "/joint3" };

	//==========================================================================
    void hiResTimerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeapLogger)
};

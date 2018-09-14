/*
  ==============================================================================

  Main.cpp
  Created: 18 Jan 2018 2:04:28pm
  Author:  Niccolò

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ReachLookAndFeel.h"
#include "MainComponent.h"
#include "LeapLogger.h"

//==============================================================================
class ReachApplication : public JUCEApplication
{
public:
    //==============================================================================
	ReachApplication() = default;
    ~ReachApplication() = default;

    const String getApplicationName() override { return ProjectInfo::projectName; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        ignoreUnused (commandLine);

        LookAndFeel::setDefaultLookAndFeel (&LAF);

		mainWindow = std::make_unique<MainWindow>("Reach");

		setupLogger();
    }

    void shutdown() override
    {
        mainWindow = nullptr;

		Logger::setCurrentLogger(nullptr);

		logger.reset();
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        quit();
    }

    void anotherInstanceStarted(const String& commandLine) override
    { }

    class MainWindow : public DocumentWindow
    {
    public:
        MainWindow(StringRef name) : DocumentWindow (name, Desktop::getInstance().getDefaultLookAndFeel()
                                                                                 .findColour (ResizableWindow::backgroundColourId),
                                                                                              DocumentWindow::allButtons)
        {
            setResizable (true, true);
            setUsingNativeTitleBar (true);
            setContentOwned (new MainContentComponent (), true);

            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:

    std::unique_ptr<MainWindow> mainWindow;
	std::unique_ptr<LeapLogger> logger;

    ReachLookAndFeel LAF;

	String dataNames{ "Hand,PalmX,PalmY,PalmZ,WristX,WristY,WristZ,Finger1Bone1X,Finger1Bone1Y,Finger1Bone1Z,Finger1Bone2X,Finger1Bone2Y,Finger1Bone2Z,Finger1Bone3X,Finger1Bone3Y,Finger1Bone3Z,Finger1Bone4X,Finger1Bone4Y,Finger1Bone4Z,Finger2Bone1X,Finger2Bone1Y,Finger2Bone1Z,Finger2Bone2X,Finger2Bone2Y,Finger2Bone2Z,Finger2Bone3X,Finger2Bone3Y,Finger2Bone3Z,Finger2Bone4X,Finger2Bone4Y,Finger2Bone4Z,Finger3Bone1X,Finger3Bone1Y,Finger3Bone1Z,Finger3Bone2X,Finger3Bone2Y,Finger3Bone2Z,Finger3Bone3X,Finger3Bone3Y,Finger3Bone3Z,Finger3Bone4X,Finger3Bone4Y,Finger3Bone4Z,Finger4Bone1X,Finger4Bone1Y,Finger4Bone1Z,Finger4Bone2X,Finger4Bone2Y,Finger4Bone2Z,Finger4Bone3X,Finger4Bone3Y,Finger4Bone3Z,Finger4Bone4X,Finger4Bone4Y,Finger4Bone4Z" };

	void setupLogger()
    {
		const auto logFilename = String(getApplicationName() + "_Log_" + Time::getCurrentTime().formatted("%d-%m-%Y_%H-%M-%S"));
		const auto logExtension = String(".csv");

		auto logFile = File::getSpecialLocation(File::SpecialLocationType::userDesktopDirectory)
			.getChildFile(logFilename + logExtension);

		logger = std::make_unique<LeapLogger>(logFile);

		Logger::setCurrentLogger(&logger->getLogger());

		logger->getLogger().logMessage(ProjectInfo::projectName + String(" Data Log"));
		logger->getLogger().logMessage({});
		logger->getLogger().logMessage(dataNames);
		logger->getLogger().logMessage({});

		logger->startLogger();
	}
};

//==============================================================================
START_JUCE_APPLICATION (ReachApplication)

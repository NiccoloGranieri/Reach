/*
  ==============================================================================

  Main.cpp
  Created: 18 Jan 2018 2:04:28pm
  Author:  Niccolò

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "ReachLookAndFeel.h"
#include "LeapListener.h"

//==============================================================================
class ReachApplication : public JUCEApplication
{
public:
    //==============================================================================
    ReachApplication()
        : leapListener (handList)
    {}

    ~ReachApplication() = default;

    const String getApplicationName() override { return ProjectInfo::projectName; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return true; }

    //==============================================================================
    void initialise(const String& commandLine) override
    {
        ignoreUnused (commandLine);

        controller.addListener (leapListener);

        LookAndFeel::setDefaultLookAndFeel (&LAF);

        mainWindow = std::make_unique<MainWindow> ("Reach", handList);
    }

    void shutdown() override
    {
        mainWindow = nullptr;

        controller.removeListener (leapListener);
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
        MainWindow(StringRef name, Leap::HandList& handList) : DocumentWindow (name,
                                                                               Desktop::getInstance()
                                                                               .getDefaultLookAndFeel()
                                                                               .findColour (
                                                                                   ResizableWindow::backgroundColourId),
                                                                               DocumentWindow::allButtons)
        {
            setResizable (true, true);
            setUsingNativeTitleBar (true);
            setContentOwned (new MainContentComponent (handList), true);

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
    Leap::Controller controller;
    Leap::HandList handList;
    LeapListener leapListener;

    std::unique_ptr<MainWindow> mainWindow;

    ReachLookAndFeel LAF;
};

//==============================================================================
START_JUCE_APPLICATION (ReachApplication)

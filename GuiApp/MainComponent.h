#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_gui_extra/juce_gui_extra.h>

struct CoolButton
:   juce::Button
{
    //! constructor
    /*! @param hue the base color of the button. (0.0 .. 1.0)
     */
    CoolButton(juce::String const &name, float hue);
    
    void paintButton (juce::Graphics &g,
                      bool shouldDrawButtonAsHighlighted,
                      bool shouldDrawButtonAsDown
                      ) override;
    
    float hue_ = 0.0;
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public juce::Component
{
public:
    //==============================================================================
    MainComponent();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    CoolButton btn1_;
    CoolButton btn2_;
    CoolButton btn3_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

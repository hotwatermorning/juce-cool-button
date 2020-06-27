#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
:   btn1_("Red", 0.0f)
,   btn2_("Green", 0.33f)
,   btn3_("Blue", 0.66f)
{
    addAndMakeVisible(btn1_);
    addAndMakeVisible(btn2_);
    addAndMakeVisible(btn3_);

    btn1_.setClickingTogglesState(true);
    btn2_.setClickingTogglesState(true);
    btn3_.setClickingTogglesState(true);

    setSize (600, 400);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    auto b = getLocalBounds();
    constexpr int kButtonHeight = 60;
    constexpr int kButtonWidth = 150;
    juce::Rectangle<int> const rc_button;
    constexpr int kPadding = 10;
    constexpr int kMinHorizontalWidth = kButtonWidth * 3 + kPadding * 6;

    static auto const def = CoolButton::getDefaultButtonTheme();

    CoolButton::ButtonTheme theme;
    theme.sz_round_                      = juce::jlimit(0.0f, 80.0f, JUCE_LIVE_CONSTANT(def.sz_round_));
    theme.sz_edge_                       = juce::jlimit(0.0f, 10.0f, JUCE_LIVE_CONSTANT(def.sz_edge_));
    theme.normal_.sa_front_              = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.normal_.sa_front_));
    theme.normal_.br_background_edge_    = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.normal_.br_background_edge_));
    theme.normal_.br_background_         = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.normal_.br_background_));
    theme.normal_.br_front_edge_         = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.normal_.br_front_edge_));
    theme.normal_.br_front_grad_top_     = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.normal_.br_front_grad_top_));
    theme.normal_.br_front_grad_bottom_  = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.normal_.br_front_grad_bottom_));
    theme.normal_.br_text_edge_          = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.normal_.br_text_edge_));
    theme.normal_.br_text_               = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.normal_.br_text_));

    theme.highlighted_.sa_front_              = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.highlighted_.sa_front_));
    theme.highlighted_.br_background_edge_    = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.highlighted_.br_background_edge_));
    theme.highlighted_.br_background_         = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.highlighted_.br_background_));
    theme.highlighted_.br_front_edge_         = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.highlighted_.br_front_edge_));
    theme.highlighted_.br_front_grad_top_     = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.highlighted_.br_front_grad_top_));
    theme.highlighted_.br_front_grad_bottom_  = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.highlighted_.br_front_grad_bottom_));
    theme.highlighted_.br_text_edge_          = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.highlighted_.br_text_edge_));
    theme.highlighted_.br_text_               = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.highlighted_.br_text_));

    theme.down_.sa_front_              = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.down_.sa_front_));
    theme.down_.br_background_edge_    = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.down_.br_background_edge_));
    theme.down_.br_background_         = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.down_.br_background_));
    theme.down_.br_front_edge_         = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.down_.br_front_edge_));
    theme.down_.br_front_grad_top_     = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.down_.br_front_grad_top_));
    theme.down_.br_front_grad_bottom_  = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.down_.br_front_grad_bottom_));
    theme.down_.br_text_edge_          = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.down_.br_text_edge_));
    theme.down_.br_text_               = juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(def.down_.br_text_));

    btn3_.setHue(juce::jlimit(0.0f, 1.0f, JUCE_LIVE_CONSTANT(0.66f)));
    btn3_.setButtonTheme(theme);

    if(b.getWidth() < kMinHorizontalWidth) {
        // Layout buttons vertically
        juce::Rectangle<int> b1, b2, b3;

        b1 = b2 = b3 = juce::Rectangle<int>(0, 0, kButtonWidth, kButtonHeight);

        b1 = b1.withCentre(b.getCentre()).translated(0, - (kButtonHeight + kPadding * 2));
        b2 = b2.withCentre(b.getCentre()).translated(0, 0);
        b3 = b3.withCentre(b.getCentre()).translated(0, + (kButtonHeight + kPadding * 2));

        btn1_.setBounds(b1.reduced(kPadding));
        btn2_.setBounds(b2.reduced(kPadding));
        btn3_.setBounds(b3.reduced(kPadding));

    } else {
        // Layout buttons horizontally
        juce::Rectangle<int> b1, b2, b3;

        b1 = b2 = b3 = juce::Rectangle<int>(0, 0, kButtonWidth, kButtonHeight);

        b1 = b1.withCentre(b.getCentre()).translated(- (kButtonWidth + kPadding * 2), 0);
        b2 = b2.withCentre(b.getCentre()).translated(0, 0);
        b3 = b3.withCentre(b.getCentre()).translated(+ (kButtonWidth + kPadding * 2), 0);

        btn1_.setBounds(b1.reduced(kPadding));
        btn2_.setBounds(b2.reduced(kPadding));
        btn3_.setBounds(b3.reduced(kPadding));
    }

    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

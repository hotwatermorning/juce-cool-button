#include "MainComponent.h"

CoolButton::CoolButton(juce::String const &name, float hue)
:   juce::Button(name)
,   hue_(hue)
{}

void CoolButton::paintButton (juce::Graphics &g,
                              bool shouldDrawButtonAsHighlighted,
                              bool shouldDrawButtonAsDown
                              )
{
    auto b = getLocalBounds();
    
    struct ButtonTheme
    {
        // sz := size
        // sa := saturation
        // br := brightness
        
        float sz_round_;
        float sz_edge_gap_;
        float sa_front_;
        float br_background_edge_;
        float br_background_;
        float br_front_edge_;
        float br_front_grad_top_;
        float br_front_grad_bottom_;
        float br_text_edge_;
        float br_text_;
    };
    
    constexpr ButtonTheme kButtonTheme_Normal         = { 3.0f, 1.0f, 0.4f, 0.5f, 0.1f, 0.72f, 0.66f, 0.60f, 0.15f, 0.9f };
    constexpr ButtonTheme kButtonTheme_Highlighted    = { 3.0f, 1.0f, 0.4f, 0.5f, 0.1f, 0.82f, 0.76f, 0.70f, 0.15f, 0.9f };
    constexpr ButtonTheme kButtonTheme_Down           = { 3.0f, 1.0f, 0.4f, 0.5f, 0.1f, 0.32f, 0.48f, 0.42f, 0.15f, 0.9f };
    
    ButtonTheme const *bt = &kButtonTheme_Normal;
    if(shouldDrawButtonAsDown || getToggleState()) {
        bt = &kButtonTheme_Down;
    } else if(shouldDrawButtonAsHighlighted) {
        bt = &kButtonTheme_Highlighted;
    }
    
    auto const round = bt->sz_round_;
    auto const gap = bt->sz_edge_gap_;
    
    // draw button background edge
    g.setColour(juce::Colour(0.0f, 0.0f, bt->br_background_edge_, 1.0f));
    g.fillRoundedRectangle(0, 0, b.getWidth(), b.getHeight(), round);
    
    // draw button background
    g.setColour(juce::Colour(0.0f, 0.0f, bt->br_background_, 1.0f));
    g.fillRoundedRectangle(0, 0, b.getWidth(), b.getHeight()-1, round);
    
    // draw button front edge
    g.setColour(juce::Colour(hue_, bt->sa_front_, bt->br_front_edge_, 1.0f));
    g.fillRoundedRectangle(gap, gap, b.getWidth() - (gap * 2), b.getHeight() - (gap * 3), round);
    
    // draw button front
    juce::ColourGradient grad(juce::Colour(hue_, bt->sa_front_, bt->br_front_grad_top_, 1.0f),
                              0.0f, 0.0f,
                              juce::Colour(hue_, bt->sa_front_, bt->br_front_grad_bottom_, 1.0f),
                              0.0f, (float)b.getHeight(),
                              false);
    g.setGradientFill(grad);
    g.fillRoundedRectangle(gap, gap * 2, b.getWidth() - (gap * 2), b.getHeight() - (gap * 4), round);

    // draw text edge
    g.setColour(juce::Colour(0.0f, 0.0f, bt->br_text_edge_, 1.0f));
    g.drawText(getButtonText(), b.reduced(1).translated(0, -1), juce::Justification::centred);
    
    // draw text
    g.setColour(juce::Colour(0.0f, 0.0f, bt->br_text_, 1.0f));
    g.drawText(getButtonText(), b, juce::Justification::centred);
}

//==============================================================================
MainComponent::MainComponent()
:   btn1_("Red", 0.0f)
,   btn2_("Green", 0.33f)
,   btn3_("Blue", 0.66f)
{
    addAndMakeVisible(btn1_);
    addAndMakeVisible(btn2_);
    addAndMakeVisible(btn3_);
    
    btn1_.setButtonText("Red");
    btn2_.setButtonText("Green");
    btn3_.setButtonText("Blue");
    
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

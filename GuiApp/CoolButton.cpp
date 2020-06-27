#include "CoolButton.h"

CoolButton::ButtonTheme CoolButton::getDefaultButtonTheme() noexcept
{
    return {
        3.0f, 1.0f,
        { 0.5f, 0.4f, 0.1f, 0.78f, 0.72f, 0.66f, 0.15f, 0.9f },
        { 0.5f, 0.4f, 0.1f, 0.88f, 0.82f, 0.76f, 0.15f, 0.9f },
        { 0.5f, 0.4f, 0.1f, 0.32f, 0.54f, 0.48f, 0.15f, 0.9f },
    };
}

CoolButton::CoolButton(juce::String const &name, float hue, ButtonTheme theme)
:   juce::Button(name)
,   theme_(theme)
{
    setHue(hue);
}

void CoolButton::setHue(float hue) noexcept
{
    assert(0.0f <= hue_ && hue_ <= 1.0f);
    hue_ = hue;
}

float CoolButton::getHue() const noexcept
{
    return hue_;
}

void CoolButton::setButtonTheme(CoolButton::ButtonTheme const &theme) noexcept
{
    theme_ = theme;
}

CoolButton::ButtonTheme CoolButton::getButtonTheme() const noexcept
{
    return theme_;
}

void CoolButton::paintButton (juce::Graphics &g,
                              bool shouldDrawButtonAsHighlighted,
                              bool shouldDrawButtonAsDown
                              )
{
    auto b = getLocalBounds();

    ButtonTheme::ColourSetting const *c = &theme_.normal_;
    if(shouldDrawButtonAsDown || getToggleState()) {
        c = &theme_.down_;
    } else if(shouldDrawButtonAsHighlighted) {
        c = &theme_.highlighted_;
    }

    auto const round = theme_.sz_round_;
    auto const edge = theme_.sz_edge_;

    // draw button background edge
    g.setColour(juce::Colour(0.0f, 0.0f, c->br_background_edge_, 1.0f));
    g.fillRoundedRectangle(0, 0, b.getWidth(), b.getHeight(), round);

    // draw button background
    g.setColour(juce::Colour(0.0f, 0.0f, c->br_background_, 1.0f));
    g.fillRoundedRectangle(0, 0, b.getWidth(), b.getHeight() - edge, round);

    // draw button front edge
    g.setColour(juce::Colour(hue_, c->sa_front_, c->br_front_edge_, 1.0f));
    g.fillRoundedRectangle(edge, edge, b.getWidth() - (edge * 2), b.getHeight() - (edge * 3), round);

    // draw button front
    juce::ColourGradient grad(juce::Colour(hue_, c->sa_front_, c->br_front_grad_top_, 1.0f),
                              0.0f, 0.0f,
                              juce::Colour(hue_, c->sa_front_, c->br_front_grad_bottom_, 1.0f),
                              0.0f, (float)b.getHeight(),
                              false);
    g.setGradientFill(grad);
    g.fillRoundedRectangle(edge, edge * 2, b.getWidth() - (edge * 2), b.getHeight() - (edge * 4), round);

    // draw text edge
    g.setColour(juce::Colour(0.0f, 0.0f, c->br_text_edge_, 1.0f));
    g.drawText(getButtonText(), b.reduced(1).translated(0, -1), juce::Justification::centred);

    // draw text
    g.setColour(juce::Colour(0.0f, 0.0f, c->br_text_, 1.0f));
    g.drawText(getButtonText(), b, juce::Justification::centred);
}

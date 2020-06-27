#ifndef CoolButton_h
#define CoolButton_h

#include <juce_gui_extra/juce_gui_extra.h>

// Cool Button Class.
struct CoolButton
:   juce::Button
{
    //! Button appearance setting.
    struct ButtonTheme
    {
        //! Colour settings.
        struct ColourSetting {
            //! colour saturation amount of the button. (0.0f .. 1.0f)
            float sa_front_;

            //! brightness of the background edge highlight. (0.0f .. 1.0f)
            float br_background_edge_;

            //! brightness of background. (0.0f .. 1.0f)
            float br_background_;

            //! brightness of the front edge highlight. (0.0f .. 1.0f)
            float br_front_edge_;

            //! the top side brightness of front gradient color. (0.0f .. 1.0f)
            float br_front_grad_top_;

            //! the bottom side brightness of the front gradient color. (0.0f .. 1.0f)
            float br_front_grad_bottom_;

            //! brightness of the text highlight. (0.0f .. 1.0f)
            float br_text_edge_;

            //! brightness of the text. (0.0f .. 1.0f)
            float br_text_;
        };

        //! rounding size of the button's rectangle area.
        float sz_round_;

        //! edge highlight size.
        float sz_edge_;

        //! Colour settin for normal state.
        ColourSetting normal_;

        //! Colour settin for highlighted state.
        ColourSetting highlighted_;

        //! Colour settin for down state.
        ColourSetting down_;
    };

    //! Get default button theme.
    static
    ButtonTheme getDefaultButtonTheme() noexcept;

    //! constructor
    /*! @param name the initial text of the button.
     *  @param hue the base color of the button. (0.0f .. 1.0f)
     */
    CoolButton(juce::String const &name, float hue, ButtonTheme theme = getDefaultButtonTheme());

    //! Set the base color of the button.
    /*! @param hue the base color of the button. (0.0f .. 1.0f)
     */
    void setHue(float hue) noexcept;

    //! Get the base color of the button.
    float getHue() const noexcept;

    //! Set button theme
    void setButtonTheme(ButtonTheme const &theme) noexcept;

    //! Get button theme
    ButtonTheme getButtonTheme() const noexcept;

private:
    float hue_ = 0.0;
    ButtonTheme theme_;

    void paintButton (juce::Graphics &g,
                      bool shouldDrawButtonAsHighlighted,
                      bool shouldDrawButtonAsDown
                      ) override;
};

#endif /* CoolButton_h */


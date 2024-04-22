#pragma once

#include "../Module.hpp"
#include "../../../Events/EventHandler.hpp"
#include "SprintListener.hpp"


class Sprint : public Module {

public:


    Sprint() : Module("Toggle Sprint", "Automatically sprints for you!!!", "\\Musui\\assets\\auto_sprint.png", 'M') {

        onEnable();

    };

    void onEnable() override {

        Module::onEnable();

        if (settings.getSettingByName<std::string>("text") == nullptr) settings.addSetting("text", (std::string)"{value}");

        if (settings.getSettingByName<std::string>("keybind")->value == (std::string)"") settings.getSettingByName<std::string>("keybind")->value = "CTRL";

        if (settings.getSettingByName<bool>("status") == nullptr) settings.addSetting("status", false);

        if (settings.getSettingByName<float>("textscale") == nullptr) settings.addSetting("textscale", 0.80f);

        if (settings.getSettingByName<bool>("always") == nullptr) {
            settings.addSetting("always", false);
        }

        EventHandler::registerListener(new SprintListener("Sprint", this));
    }

    void onDisable() override {

        EventHandler::unregisterListener("Sprint");

        Module::onDisable();

    }

    void SettingsRender() override {
        /* Border Start */

        float toggleX = Constraints::PercentageConstraint(0.019, "left");
        float toggleY = Constraints::PercentageConstraint(0.10, "top");

        const float textWidth = Constraints::RelativeConstraint(0.12, "height", true);
        const float textHeight = Constraints::RelativeConstraint(0.029, "height", true);


        MusuiGUI::ScrollBar(toggleX, toggleY, 140, Constraints::SpacingConstraint(5.5, textWidth), 2);

        MusuiGUI::SetScrollView(toggleX, Constraints::PercentageConstraint(0.00, "top"), Constraints::RelativeConstraint(1.0, "width"), Constraints::RelativeConstraint(1.0f, "height"));

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"UI Scale", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        float percent = MusuiGUI::Slider(4, toggleX + MusuiGUI::SettingsTextWidth("UI Scale "),
                                           toggleY, this->settings.getSettingByName<float>("uiscale")->value, 2.0f);

        this->settings.getSettingByName<float>("uiscale")->value = percent;


        toggleY += Constraints::SpacingConstraint(0.35, textWidth);
        if (MusuiGUI::Toggle(0, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "border")->value)) this->settings.getSettingByName<bool>("border")->value = !this->settings.getSettingByName<bool>("border")->value;


        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY, L"Border",
                                        textWidth * 3.0f, textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);


        percent = MusuiGUI::Slider(5, toggleX + Constraints::SpacingConstraint(0.60, textWidth) +
                                        MusuiGUI::SettingsTextWidth("Border "),
                                     toggleY, this->settings.getSettingByName<float>("borderWidth")->value, 4);

        this->settings.getSettingByName<float>("borderWidth")->value = percent;


        /* Border End */

        /* Rounding Start */
        toggleY += Constraints::SpacingConstraint(0.35, textWidth);


        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"Rounding", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        percent = MusuiGUI::Slider(6, toggleX + MusuiGUI::SettingsTextWidth("Rounding "),
                                     toggleY, this->settings.getSettingByName<float>("rounding")->value);

        this->settings.getSettingByName<float>("rounding")->value = percent;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::KeybindSelector(0, toggleX, toggleY, settings.getSettingByName<std::string>("keybind")->value);

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        MusuiGUI::to_wide("Always Sprint").c_str(), textWidth * 6.9f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING, Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(2, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "always")->value)) this->settings.getSettingByName<bool>("always")->value = !this->settings.getSettingByName<bool>("always")->value;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        MusuiGUI::to_wide("Toggle Status").c_str(), textWidth * 6.9f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING, Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(5, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "status")->value)) this->settings.getSettingByName<bool>("status")->value = !this->settings.getSettingByName<bool>("status")->value;



        /* Rounding End */

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        MusuiGUI::to_wide("Translucency").c_str(), textWidth * 6.9f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING, Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(4, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "BlurEffect")->value)) this->settings.getSettingByName<bool>("BlurEffect")->value = !this->settings.getSettingByName<bool>("BlurEffect")->value;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);
        MusuiGUI::TextBoxVisual(7, settings.getSettingByName<std::string>("text")->value, 16, toggleX, toggleY);

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"Text Scale", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        percent = MusuiGUI::Slider(8, toggleX + MusuiGUI::SettingsTextWidth("Text Scale "),
                                     toggleY, this->settings.getSettingByName<float>("textscale")->value, 2.00);

        this->settings.getSettingByName<float>("textscale")->value = percent;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);


        std::string txtAlignment = MusuiGUI::Dropdown(1,
                                                        toggleX, toggleY,
                                                        std::vector<std::string>{"Left", "Center", "Right"},
                                                        this->settings.getSettingByName<std::string>(
                                                                "textalignment")->value,
                                                        "Text Alignment"
        );

        this->settings.getSettingByName<std::string>("textalignment")->value = txtAlignment;

        MusuiGUI::SetIsInAdditionalYMode();

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        MusuiGUI::to_wide("Reverse Padding X").c_str(), textWidth * 6.9f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING, Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(15, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "reversepaddingx")->value)) this->settings.getSettingByName<bool>("reversepaddingx")->value = !this->settings.getSettingByName<bool>("reversepaddingx")->value;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        MusuiGUI::to_wide("Reverse Padding Y").c_str(), textWidth * 6.9f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING, Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(16, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "reversepaddingy")->value)) this->settings.getSettingByName<bool>("reversepaddingy")->value = !this->settings.getSettingByName<bool>("reversepaddingy")->value;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"Padding X", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        percent = MusuiGUI::Slider(15, toggleX + MusuiGUI::SettingsTextWidth("Padding X "),
                                     toggleY, this->settings.getSettingByName<float>("padx")->value, 0.53f, 0.0f,
                                     false);

        this->settings.getSettingByName<float>("padx")->value = percent;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"Padding Y", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        percent = MusuiGUI::Slider(16, toggleX + MusuiGUI::SettingsTextWidth("Padding Y "),
                                     toggleY, this->settings.getSettingByName<float>("pady")->value, 0.53f, 0.0f,
                                     false);

        this->settings.getSettingByName<float>("pady")->value = percent;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"Rect Width", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        percent = MusuiGUI::Slider(17, toggleX + MusuiGUI::SettingsTextWidth("Rect Width "),
                                     toggleY, this->settings.getSettingByName<float>("rectwidth")->value, 3.0f);

        this->settings.getSettingByName<float>("rectwidth")->value = percent;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"Rect Height", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        percent = MusuiGUI::Slider(18, toggleX + MusuiGUI::SettingsTextWidth("Rect Height "),
                                     toggleY, this->settings.getSettingByName<float>("rectheight")->value, 3.0f);

        this->settings.getSettingByName<float>("rectheight")->value = percent;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        MusuiGUI::to_wide("Responsive Rectangle (Moves with the Text)").c_str(),
                                        textWidth * 5.f, textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(17, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "responsivewidth")->value)) this->settings.getSettingByName<bool>("responsivewidth")->value = !this->settings.getSettingByName<bool>("responsivewidth")->value;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);
        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"Rotation", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);
        percent = MusuiGUI::Slider(19, toggleX + MusuiGUI::SettingsTextWidth("Rotation "),
                                     toggleY, this->settings.getSettingByName<float>("rotation")->value, 359.0f, 0.0f,
                                     false);

        this->settings.getSettingByName<float>("rotation")->value = percent;

        MusuiGUI::UnSetIsInAdditionalYMode();

        /* Color Pickers Start*/

        toggleX = Constraints::PercentageConstraint(0.55, "left");
        toggleY = Constraints::PercentageConstraint(0.10, "top");

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, MusuiGUI::to_wide("Background").c_str(), textWidth * 6.9f,
                                        textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);
        MusuiGUI::ColorPicker(0, toggleX + MusuiGUI::SettingsTextWidth("Background "), toggleY - Constraints::SpacingConstraint(0.017, textWidth), settings.getSettingByName<std::string>("bgColor")->value, settings.getSettingByName<float>("bgOpacity")->value, settings.getSettingByName<bool>("bgRGB")->value);

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, MusuiGUI::to_wide("Text").c_str(), textWidth * 6.9f,
                                        textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);
        MusuiGUI::ColorPicker(1, toggleX + MusuiGUI::SettingsTextWidth("Text "), toggleY * 0.99f, settings.getSettingByName<std::string>("textColor")->value, settings.getSettingByName<float>("textOpacity")->value, settings.getSettingByName<bool>("textRGB")->value);

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, MusuiGUI::to_wide("Border").c_str(), textWidth * 6.9f,
                                        textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);
        MusuiGUI::ColorPicker(2, toggleX + MusuiGUI::SettingsTextWidth("Border "), toggleY * 0.99f, settings.getSettingByName<std::string>("borderColor")->value, settings.getSettingByName<float>("borderOpacity")->value, settings.getSettingByName<bool>("borderRGB")->value);

        MusuiGUI::UnsetScrollView();

        MusuiGUI::ColorPickerWindow(0, settings.getSettingByName<std::string>("bgColor")->value, settings.getSettingByName<float>("bgOpacity")->value, settings.getSettingByName<bool>("bgRGB")->value);
        MusuiGUI::ColorPickerWindow(1, settings.getSettingByName<std::string>("textColor")->value, settings.getSettingByName<float>("textOpacity")->value, settings.getSettingByName<bool>("textRGB")->value);
        MusuiGUI::ColorPickerWindow(2, settings.getSettingByName<std::string>("borderColor")->value, settings.getSettingByName<float>("borderOpacity")->value, settings.getSettingByName<bool>("borderRGB")->value);
        /* Color Pickers End */

    }
};


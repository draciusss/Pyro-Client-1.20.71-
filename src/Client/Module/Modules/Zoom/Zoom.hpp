#pragma once

#include "../Module.hpp"
#include "ZoomListener.hpp"
#include "../../../Events/EventHandler.hpp"


class Zoom : public Module {

public:

    Zoom() : Module("Zoom", "Allows you to see distant places.", "\\Musui\\assets\\magnify.png", 'C') {

        onEnable();

    };

    void onEnable() override {

        EventHandler::registerListener(new ZoomListener("Zoom", this));

        Module::onEnable();

    }

    void NormalRender(int index, std::string text, std::string value) override {

    }

    virtual void DefaultConfig() override {
        if (settings.getSettingByName<bool>("SaveModifier") == nullptr) settings.addSetting("SaveModifier", true);
        if (settings.getSettingByName<bool>("hidehand") == nullptr) settings.addSetting("hidehand", true);
        if (settings.getSettingByName<bool>("hidemodules") == nullptr) settings.addSetting("hidemodules", false);
        if (settings.getSettingByName<bool>("hidehud") == nullptr) settings.addSetting("hidehud", false);
        if (settings.getSettingByName<float>("modifier") == nullptr) settings.addSetting("modifier", 10.0f);
        if (settings.getSettingByName<float>("anim") == nullptr) settings.addSetting("anim", 0.20f);
        if (settings.getSettingByName<float>("disableanim") == nullptr) settings.addSetting("disableanim", false);
        if (settings.getSettingByName<std::string>("text") == nullptr) settings.addSetting("text", (std::string)"real");
        if (settings.getSettingByName<std::string>("keybind")->value == (std::string)"") settings.getSettingByName<std::string>("keybind")->value = "C";
    }

    void onDisable() override {
        Module::onDisable();
    }

    void SettingsRender() override {

        float textWidth = Constraints::RelativeConstraint(0.12, "height", true);
        const float textHeight = Constraints::RelativeConstraint(0.029, "height", true);

        float toggleX = Constraints::PercentageConstraint(0.019, "left");
        float toggleY = Constraints::PercentageConstraint(0.10, "top");

        MusuiGUI::ScrollBar(toggleX, toggleY, 140, Constraints::SpacingConstraint(5.5, textWidth), 2);
        MusuiGUI::SetScrollView(toggleX, Constraints::PercentageConstraint(0.00, "top"), Constraints::RelativeConstraint(1.0, "width"), Constraints::RelativeConstraint(1.0f, "height"));

        MusuiGUI::KeybindSelector(0, toggleX, toggleY, settings.getSettingByName<std::string>("keybind")->value);

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"Modifier", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);


        float percent = MusuiGUI::Slider(7, toggleX + MusuiGUI::SettingsTextWidth("Modifier "),
                                           toggleY, this->settings.getSettingByName<float>("modifier")->value, 30, 0,
                                           0);

        this->settings.getSettingByName<float>("modifier")->value = percent;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        textWidth *= 1.5f;

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"Animation Speed", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);


        percent = MusuiGUI::Slider(8, toggleX + MusuiGUI::SettingsTextWidth("Animation Speed "),
                                     toggleY, this->settings.getSettingByName<float>("anim")->value, 0.40);

        this->settings.getSettingByName<float>("anim")->value = percent;

        toggleY += Constraints::SpacingConstraint(0.25, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.38, textWidth), toggleY,
                                        L"Save Modifier", textWidth * 3.0f, textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);
        if (MusuiGUI::Toggle(1, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "SaveModifier")->value)) this->settings.getSettingByName<bool>("SaveModifier")->value = !this->settings.getSettingByName<bool>("SaveModifier")->value;

        toggleX = Constraints::PercentageConstraint(0.55, "left");
        toggleY = Constraints::PercentageConstraint(0.10, "top");

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        L"Hide hand", textWidth * 3.0f, textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);
        if (MusuiGUI::Toggle(2, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "hidehand")->value)) this->settings.getSettingByName<bool>("hidehand")->value = !this->settings.getSettingByName<bool>("hidehand")->value;

        toggleY += Constraints::SpacingConstraint(0.25, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        L"Hide modules", textWidth * 3.0f, textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);
        if (MusuiGUI::Toggle(3, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "hidemodules")->value)) this->settings.getSettingByName<bool>("hidemodules")->value = !this->settings.getSettingByName<bool>("hidemodules")->value;

        toggleY += Constraints::SpacingConstraint(0.25, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        L"Disable animation", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);
        if (MusuiGUI::Toggle(4, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "disableanim")->value)) this->settings.getSettingByName<bool>("disableanim")->value = !this->settings.getSettingByName<bool>("disableanim")->value;

        MusuiGUI::UnsetScrollView();

    }
};
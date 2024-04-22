#pragma once

#include "../Module.hpp"
#include "../../../Events/EventHandler.hpp"


class TimeChanger : public Module {

public:

    TimeChanger() : Module("Time Changer", "Changes the ingame time.", "\\Musui\\assets\\time.png", 'C') {

        onEnable();

    };

    void onEnable() override {
        Module::onEnable();

    }

    void NormalRender(int index, std::string text, std::string value) override {

    }

    virtual void DefaultConfig() override {
        if (settings.getSettingByName<float>("time") == nullptr) settings.addSetting("time", 0.5f);

    }

    void onDisable() override {
        Module::onDisable();
    }

    void SettingsRender() override {


        float toggleX = Constraints::PercentageConstraint(0.019, "left");
        float toggleY = Constraints::PercentageConstraint(0.10, "top");

        const float textWidth = Constraints::RelativeConstraint(0.12, "height", true);
        const float textHeight = Constraints::RelativeConstraint(0.029, "height", true);

        MusuiGUI::ScrollBar(toggleX, toggleY, 140, Constraints::SpacingConstraint(5.5, textWidth), 2);
        MusuiGUI::SetScrollView(toggleX, Constraints::PercentageConstraint(0.00, "top"), Constraints::RelativeConstraint(1.0, "width"), Constraints::RelativeConstraint(1.0f, "height"));

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"Time Slider", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        float percent = MusuiGUI::Slider(4, toggleX + MusuiGUI::SettingsTextWidth("Time Slider "),
                                           toggleY, this->settings.getSettingByName<float>("time")->value, 1.0f);

        this->settings.getSettingByName<float>("time")->value = percent;

        MusuiGUI::UnsetScrollView();


    }
};
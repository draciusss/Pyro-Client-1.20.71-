#pragma once

#include "../Module.hpp"
#include "../../../Events/EventHandler.hpp"
#include "../../../Client.hpp"

class FOVChanger : public Module {

public:


    FOVChanger() : Module("FOV Changer", "Change your FOV beyond Minecraft's limits.", "\\Musui\\assets\\field-of-view.png", 'o') {

        onEnable();

    };

    void onEnable() override {

        Module::onEnable();

		if (settings.getSettingByName<float>("fovvalue") == nullptr) settings.addSetting("fovvalue", 60.00f);

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

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"FOV Value", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

		float percent = MusuiGUI::Slider(0, toggleX + MusuiGUI::SettingsTextWidth("FOV Value "),
                                           toggleY, this->settings.getSettingByName<float>("fovvalue")->value, 359.0f,
                                           0, 0);

		this->settings.getSettingByName<float>("fovvalue")->value = percent;

		MusuiGUI::UnsetScrollView();
    }
};


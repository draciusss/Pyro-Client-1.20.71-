#pragma once

#include "../Module.hpp"
#include "../../../Events/EventHandler.hpp"
#include "SneakListener.hpp"


class Sneak : public Module {

public:


    Sneak() : Module("Toggle Sneak", "No need to hold down your sneak key.", "\\Musui\\assets\\slowly.png", 'M') {

        onEnable();

    };

    void onEnable() override {

        Module::onEnable();

        if (settings.getSettingByName<std::string>("keybind")->value == (std::string)"") settings.getSettingByName<std::string>("keybind")->value = "SHIFT";

        if (settings.getSettingByName<bool>("status") == nullptr) settings.addSetting("status", false);

        if (settings.getSettingByName<float>("textscale") == nullptr) settings.addSetting("textscale", 0.80f);

        if (settings.getSettingByName<bool>("always") == nullptr) {
            settings.addSetting("always", false);
        }

        EventHandler::registerListener(new SneakListener("Sneak", this));
    }

    void onDisable() override {

        EventHandler::unregisterListener("Sneak");

        Module::onDisable();

    }

    void SettingsRender() override {

        float toggleX = Constraints::PercentageConstraint(0.019, "left");
        float toggleY = Constraints::PercentageConstraint(0.10, "top");

        const float textWidth = Constraints::RelativeConstraint(0.12, "height", true);
        const float textHeight = Constraints::RelativeConstraint(0.029, "height", true);

        MusuiGUI::KeybindSelector(0, toggleX, toggleY, settings.getSettingByName<std::string>("keybind")->value);

    }
};


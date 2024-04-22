#pragma once

#include "../Module.hpp"
#include "../../../Events/EventHandler.hpp"
#include "SpammerListener.hpp"


class Spammer : public Module {

public:


    Spammer() : Module("Spammer", "Spammer", "\\Musui\\assets\\text-box.png", 'o') {

        onEnable();

    };

    void onEnable() override {

        Module::onEnable();
        if (settings.getSettingByName<std::string>("text") == nullptr) settings.addSetting("text", (std::string)"");

        EventHandler::registerListener(new SpammerListener("spammertext", this));
    }

    void onDisable() override {

        EventHandler::unregisterListener("spammertext");
        Module::onDisable();

    }

    void SettingsRender() override {

        float toggleX = Constraints::PercentageConstraint(0.019, "left");
        float toggleY = Constraints::PercentageConstraint(0.10, "top");

        MusuiGUI::TextBoxVisual(5, settings.getSettingByName<std::string>("text")->value, 50, toggleX, toggleY);

    }
};


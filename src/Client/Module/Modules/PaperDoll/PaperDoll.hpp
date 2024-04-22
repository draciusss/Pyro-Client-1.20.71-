#pragma once

#include "../Module.hpp"
#include "../../../Events/EventHandler.hpp"
#include "DollListener.hpp"

class PaperDoll : public Module {

public:

    PaperDoll() : Module("Movable Paperdoll", "Makes the Minecraft paperdoll movable.", "\\Musui\\assets\\man.png", 'Y') {

        onEnable();

    };

    void onEnable() override {

        Module::onEnable();
        EventHandler::registerListener(new DollListener("Doll", this));
    }

    void onDisable() override {

        EventHandler::unregisterListener("PaperDoll");

        Module::onDisable();

    }

    void DefaultConfig() override {

       
        if (settings.getSettingByName<bool>("enabled") == nullptr) settings.addSetting("enabled", false);
        if (settings.getSettingByName<float>("uiscale") == nullptr) settings.addSetting("uiscale", 21.0f);
        if (settings.getSettingByName<bool>("alwaysshow") == nullptr) settings.addSetting("alwaysshow", false);
        if (settings.getSettingByName<float>("percentageX") == nullptr) {
            settings.addSetting("percentageX", 0.0f);
            settings.addSetting("percentageY", 0.0f);
        }
        if (settings.getSettingByName<bool>("vertical") == nullptr) settings.addSetting("vertical", false);

    }

    void SettingsRender() override {

        /* Border Start */



        float toggleX = Constraints::PercentageConstraint(0.019, "left");
        float toggleY = Constraints::PercentageConstraint(0.10, "top");

        const float textWidth = Constraints::RelativeConstraint(0.12, "height", true);
        const float textHeight = Constraints::RelativeConstraint(0.029, "height", true);

        MusuiGUI::ScrollBar(toggleX, toggleY, 140, 40, 2);
        MusuiGUI::SetScrollView(toggleX, toggleY, Constraints::RelativeConstraint(1.0, "width"),
            Constraints::RelativeConstraint(0.90, "height"));

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"UI Scale", textWidth * 6.9f,
                                        textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        float percent = MusuiGUI::Slider(3, toggleX + MusuiGUI::SettingsTextWidth("UI Scale "),
                                           toggleY,
                                           this->settings.getSettingByName<float>("uiscale")->value, 40.0f);

        this->settings.getSettingByName<float>("uiscale")->value = percent;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        MusuiGUI::to_wide("Always Show").c_str(), textWidth * 6.9f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING, Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(2, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "alwaysshow")->value)) this->settings.getSettingByName<bool>("alwaysshow")->value = !this->settings.getSettingByName<bool>("alwaysshow")->value;

        MusuiGUI::UnsetScrollView();
    }
};
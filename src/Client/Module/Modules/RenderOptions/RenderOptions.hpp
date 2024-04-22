#pragma once

#include "../Module.hpp"
#include "../../../Events/EventHandler.hpp"


class RenderOptions : public Module {

public:

    void NormalRender(int index, std::string text, std::string value) override {

    }

    RenderOptions() : Module("Render Options", "Change the way how the game is rendered.", "\\Musui\\assets\\renderoptions.png", 'b') {

        onEnable();

    };

    void onEnable() override {

        if (settings.getSettingByName<bool>("chunkborders") == nullptr) settings.addSetting("chunkborders", false);
        if (settings.getSettingByName<bool>("sky") == nullptr) settings.addSetting("sky", true);
        if (settings.getSettingByName<bool>("weather") == nullptr) settings.addSetting("weather", true);
        if (settings.getSettingByName<bool>("entity") == nullptr) settings.addSetting("entity", true);
        if (settings.getSettingByName<bool>("blockentity") == nullptr) settings.addSetting("blockentity", true);
        if (settings.getSettingByName<bool>("particles") == nullptr) settings.addSetting("particles", true);

        Module::onEnable();
    }


    void onDisable() override {
        Module::onDisable();
    }

    void SettingsRender() override {

        const float textWidth = Constraints::RelativeConstraint(0.12, "height", true);
        const float textHeight = Constraints::RelativeConstraint(0.029, "height", true);

        float toggleX = Constraints::PercentageConstraint(0.019, "left");
        float toggleY = Constraints::PercentageConstraint(0.10, "top");

        MusuiGUI::ScrollBar(toggleX, toggleY, 140, Constraints::SpacingConstraint(5.5, textWidth), 2);
        MusuiGUI::SetScrollView(toggleX, Constraints::PercentageConstraint(0.00, "top"), Constraints::RelativeConstraint(1.0, "width"), Constraints::RelativeConstraint(1.0f, "height"));

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        L"Chunk Borders", textWidth * 3.0f, textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(1, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "chunkborders")->value)) this->settings.getSettingByName<bool>("chunkborders")->value = !this->settings.getSettingByName<bool>("chunkborders")->value;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        L"Render Sky", textWidth * 3.0f, textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(2, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "sky")->value)) this->settings.getSettingByName<bool>("sky")->value = !this->settings.getSettingByName<bool>("sky")->value;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        L"Render Entities", textWidth * 3.0f, textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(3, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "entity")->value)) this->settings.getSettingByName<bool>("entity")->value = !this->settings.getSettingByName<bool>("entity")->value;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        L"Render Block Entities", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(4, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "blockentity")->value)) this->settings.getSettingByName<bool>("blockentity")->value = !this->settings.getSettingByName<bool>("blockentity")->value;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        L"Render Particles", textWidth * 3.0f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(5, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "particles")->value)) this->settings.getSettingByName<bool>("particles")->value = !this->settings.getSettingByName<bool>("particles")->value;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        L"Render Weather", textWidth * 3.0f, textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(6, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "weather")->value)) this->settings.getSettingByName<bool>("weather")->value = !this->settings.getSettingByName<bool>("weather")->value;

        MusuiGUI::UnsetScrollView();
    }
};
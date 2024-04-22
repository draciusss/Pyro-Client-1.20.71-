#pragma once

#include "../Module.hpp"
#include "../../../Events/EventHandler.hpp"
#include "TabListListener.hpp"
#include "../Nick/NickListener.hpp"


class TabList : public Module {

public:


    TabList() : Module("Tab List", "Java-like tab list.\nLists the current online players on the server.", "\\Musui\\assets\\list.png", 'o') {

        onEnable();

    };

    void onEnable() override {

        Module::onEnable();
        EventHandler::registerListener(new TabListListener("TabList", this));
        if (settings.getSettingByName<std::string>("keybind")->value == (std::string)"") settings.getSettingByName<std::string>("keybind")->value = "TAB";
        if (settings.getSettingByName<bool>("alphaOrder") == nullptr) settings.addSetting<bool>("alphaOrder", true);
    }

    void DefaultConfig() override {

        if(settings.getSettingByName<float>("percentageX") == nullptr) {
            settings.addSetting("percentageX", 0.0f);
            settings.addSetting("percentageY", 0.0f);
        }

        if(settings.getSettingByName<bool>("border") == nullptr) {
            settings.addSetting("border", false);
            settings.addSetting("borderWidth", 1.0f);
        }

        if(settings.getSettingByName<float>("rounding") == nullptr) settings.addSetting("rounding", 32.0f);

        if(settings.getSettingByName<std::string>("bgColor") == nullptr) {
            settings.addSetting("bgColor", (std::string)"000000");
            settings.addSetting("textColor", (std::string)"fafafa");
            settings.addSetting("borderColor", (std::string)"000000");
        }

        if(settings.getSettingByName<float>("bgOpacity") == nullptr) {
            settings.addSetting("bgOpacity", 0.55f);
            settings.addSetting("textOpacity", 1.0f);
            settings.addSetting("borderOpacity", 1.0f);
        }

        if (settings.getSettingByName<bool>("bgRGB") == nullptr) {
            settings.addSetting("bgRGB", false);
            settings.addSetting("textRGB", false);
            settings.addSetting("borderRGB", false);
        }

        if(settings.getSettingByName<float>("uiscale") == nullptr) {

            settings.addSetting("uiscale", 0.65f);
        }



        if (settings.getSettingByName<bool>("BlurEffect") == nullptr) {
            settings.addSetting("BlurEffect", true);
        }

    }

    void onDisable() override {

        EventHandler::unregisterListener("TabList");

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

        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"UI Scale", textWidth * 6.9f,
                                        textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        float percent = MusuiGUI::Slider(4, toggleX + MusuiGUI::SettingsTextWidth("UI Scale "),
                                           toggleY,
                                           this->settings.getSettingByName<float>("uiscale")->value, 2.0f);

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

        /* Rounding Start */
        toggleY += Constraints::SpacingConstraint(0.35, textWidth);


        MusuiGUI::MusuiTextWithFont(toggleX, toggleY, L"Rounding", textWidth * 6.9f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::RelativeConstraint(0.12, "height", true),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        percent = MusuiGUI::Slider(6, toggleX + MusuiGUI::SettingsTextWidth("Rounding "),
                                     toggleY,
                                     this->settings.getSettingByName<float>("rounding")->value);

        this->settings.getSettingByName<float>("rounding")->value = percent;

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::KeybindSelector(0, toggleX, toggleY, settings.getSettingByName<std::string>("keybind")->value);

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        MusuiGUI::to_wide("Alphabetical Order").c_str(),
                                        textWidth * 2.0f, textHeight, DWRITE_TEXT_ALIGNMENT_LEADING,
                                        Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(2, toggleX, toggleY,
                               this->settings.getSettingByName<bool>("alphaOrder")->value))
            this->settings.getSettingByName<bool>("alphaOrder")->value = !this->settings.getSettingByName<bool>(
                "alphaOrder")->value;

        /* Rounding End */

        toggleY += Constraints::SpacingConstraint(0.35, textWidth);

        MusuiGUI::MusuiTextWithFont(toggleX + Constraints::SpacingConstraint(0.60, textWidth), toggleY,
                                        MusuiGUI::to_wide("Translucency").c_str(), textWidth * 6.9f, textHeight,
                                        DWRITE_TEXT_ALIGNMENT_LEADING, Constraints::SpacingConstraint(1.05, textWidth),
                                        DWRITE_FONT_WEIGHT_NORMAL);

        if (MusuiGUI::Toggle(4, toggleX, toggleY, this->settings.getSettingByName<bool>(
                "BlurEffect")->value)) this->settings.getSettingByName<bool>("BlurEffect")->value = !this->settings.getSettingByName<bool>("BlurEffect")->value;

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

    }

    void NormalRender(int index, std::string text, std::string value) override {

        if (SDK::hasInstanced) {
            if (SDK::clientInstance->getLocalPlayer() != nullptr) {
                float keycardSize = Constraints::RelativeConstraint(
                    0.05f * this->settings.getSettingByName<float>("uiscale")->value, "height", true);

                Vec2<float> settingperc = Vec2<float>(this->settings.getSettingByName<float>("percentageX")->value,
                    this->settings.getSettingByName<float>("percentageY")->value);

                int i3 = 0;
                float i2 = 0;

                for (const auto& pair : SDK::clientInstance->getLocalPlayer()->getlevel()->getPlayerMap()) {

                    i3++;

                    if (i3 % 10 == 1) {
                        i2 += 4.85;
                    }

                }

                Vec2<float> realcenter;

                if (settingperc.x != 0)
                    realcenter = Vec2<float>(settingperc.x * MC::windowSize.x,
                        settingperc.y * MC::windowSize.y);
                else
                    realcenter = Constraints::CenterConstraint(i2 * keycardSize, 7.5f * keycardSize, "y", 0.0f, -0.85f);

                i3 = 0;
                i2 = 0;
                int count = 0;

                float fakex = realcenter.x;
                float fixer = 0;

                for (const auto& pair : SDK::clientInstance->getLocalPlayer()->getlevel()->getPlayerMap()) {

                    i3++;

                    if (i3 % 10 == 1) {
                        i2 += 4.85;
                        count++;

                        if(count != 1) {
                            fakex -= ((5.f * keycardSize) / 2.0f);
                            fixer += ((5.f * keycardSize) / 2.0f);
                        }
                    }

                }

                Vec2<float> rounde = Constraints::RoundingConstraint(
                    this->settings.getSettingByName<float>("rounding")->value *
                    settings.getSettingByName<float>("uiscale")->value,
                    this->settings.getSettingByName<float>("rounding")->value *
                    settings.getSettingByName<float>("uiscale")->value);

                float totalWidth = i2 * keycardSize;

                if (ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("enabled")->value || ClickGUIRenderer::editmenu)
                    MusuiGUI::SetWindowRect(fakex, realcenter.y, totalWidth, keycardSize * 7.5f, index, fixer);

                Vec2<float> vec2 = MusuiGUI::CalculateMovedXY(realcenter.x, realcenter.y, index, totalWidth,keycardSize * 7.5f);

                realcenter.x = vec2.x;
                realcenter.y = vec2.y;

                realcenter = realcenter;

                Vec2<float> percentages = Constraints::CalculatePercentage(realcenter.x, realcenter.y);

                this->settings.setValue("percentageX", percentages.x);
                this->settings.setValue("percentageY", percentages.y);

                float fontSize = Constraints::SpacingConstraint(3, keycardSize);

                D2D1_COLOR_F disabledColor;
                if (settings.getSettingByName<bool>("bgRGB")->value) disabledColor = MusuiGUI::rgbColor;
                else disabledColor = MusuiGUI::HexToColorF(settings.getSettingByName<std::string>("bgColor")->value);

                D2D1_COLOR_F textColor;
                if (settings.getSettingByName<bool>("textRGB")->value) textColor = MusuiGUI::rgbColor;
                else textColor = MusuiGUI::HexToColorF(settings.getSettingByName<std::string>("textColor")->value);

                D2D1_COLOR_F borderColor;
                if (settings.getSettingByName<bool>("borderRGB")->value) borderColor = MusuiGUI::rgbColor;
                else borderColor = MusuiGUI::HexToColorF(settings.getSettingByName<std::string>("borderColor")->value);

                disabledColor.a = settings.getSettingByName<float>("bgOpacity")->value;
                textColor.a = settings.getSettingByName<float>("textOpacity")->value;
                borderColor.a = settings.getSettingByName<float>("borderOpacity")->value;
                if (settings.getSettingByName<bool>("BlurEffect") != nullptr)
                    if (settings.getSettingByName<bool>("BlurEffect")->value) MusuiGUI::BlurRect(D2D1::RoundedRect(D2D1::RectF(fakex, realcenter.y, fakex + (i2 * keycardSize), realcenter.y + (7.5*keycardSize)), rounde.x, rounde.x), Client::settings.getSettingByName<float>("blurintensity")->value);
                if (this->settings.getSettingByName<bool>("border")->value) {
                    MusuiGUI::RoundedHollowRect(fakex, realcenter.y, Constraints::RelativeConstraint((this->settings.getSettingByName<float>("borderWidth")->value * (settings.getSettingByName<float>("uiscale")->value) / 100.0f), "height", true),
                        borderColor, totalWidth, 7.5f * keycardSize,
                        rounde.x, rounde.x);
                }
                MusuiGUI::RoundedRect(fakex, realcenter.y, disabledColor, totalWidth, 7.5f * keycardSize,
                    rounde.x,
                    rounde.x);

                int i = 0;

                bool yes = settings.getSettingByName<bool>("alphaOrder")->value;

                if(yes) {

                    auto vecmap = copyMapInAlphabeticalOrder(SDK::clientInstance->getLocalPlayer()->getlevel()->getPlayerMap());
                    for (const auto &pair: vecmap) {

                        i++;
                        std::string name = Utils::removeNonAlphanumeric(Utils::removeColorCodes(pair.second.name));
                        

                        auto it = std::find(ModuleManager::OnlineUsers.begin(), ModuleManager::OnlineUsers.end(), name);

                        // Check if the string was found
                        

                        auto module = ModuleManager::getModule("Nick");

                        if (module->settings.getSettingByName<bool>("enabled")->value && name == Utils::removeNonAlphanumeric(Utils::removeColorCodes(NickListener::original))) {
                            name = module->settings.getSettingByName<std::string>("nick")->value;
                        }

                        float xx = 0;

                        if (it != ModuleManager::OnlineUsers.end()) {
                            MusuiGUI::Image("\\Musui\\assets\\logo.png", D2D1::RectF(fakex + Constraints::SpacingConstraint(0.2, keycardSize), realcenter.y +
                                Constraints::SpacingConstraint(0.12, keycardSize), fakex + Constraints::SpacingConstraint(1.1, keycardSize), realcenter.y +
                                Constraints::SpacingConstraint(1.22, keycardSize)));

                            xx = Constraints::SpacingConstraint(0.5, keycardSize);

                        }

                        MusuiGUI::MusuiTextWithFont(fakex +xx+ Constraints::SpacingConstraint(0.5, keycardSize),
                                                        realcenter.y +
                                                        Constraints::SpacingConstraint(0.12, keycardSize),
                                                        MusuiGUI::to_wide(name).c_str(),
                                                        keycardSize * 5, keycardSize,
                                                        DWRITE_TEXT_ALIGNMENT_LEADING, fontSize,
                                                        DWRITE_FONT_WEIGHT_NORMAL, textColor, true);

                        realcenter.y += Constraints::SpacingConstraint(0.70, keycardSize);

                        if (i % 10 == 0) {
                            realcenter.y = vec2.y;
                            fakex += Constraints::SpacingConstraint(5.0, keycardSize);
                        }

                    }

                } else {
                    for (const auto &pair: SDK::clientInstance->getLocalPlayer()->getlevel()->getPlayerMap()) {

                        i++;

                        std::string name = pair.second.name;

                        auto it = std::find(ModuleManager::OnlineUsers.begin(), ModuleManager::OnlineUsers.end(), name);

                        // Check if the string was found
                        if (it != ModuleManager::OnlineUsers.end()) {
                            name = "[F] " + name;
                        }

                        auto module = ModuleManager::getModule("Nick");

                        if (module->settings.getSettingByName<bool>("enabled")->value && name == NickListener::backupOri) {
                            name = module->settings.getSettingByName<std::string>("nick")->value;
                        }

                        MusuiGUI::MusuiTextWithFont(fakex + Constraints::SpacingConstraint(0.5, keycardSize),
                                                        realcenter.y +
                                                        Constraints::SpacingConstraint(0.12, keycardSize),
                                                        MusuiGUI::to_wide(Utils::removeNonAlphanumeric(
                                                                Utils::removeColorCodes(name))).c_str(),
                                                        keycardSize * 5, keycardSize,
                                                        DWRITE_TEXT_ALIGNMENT_LEADING, fontSize,
                                                        DWRITE_FONT_WEIGHT_NORMAL, textColor, true);

                        realcenter.y += Constraints::SpacingConstraint(0.70, keycardSize);

                        if (i % 10 == 0) {
                            realcenter.y = vec2.y;
                            fakex += Constraints::SpacingConstraint(5.0, keycardSize);
                        }

                    }
                }

                if (ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("enabled")->value || ClickGUIRenderer::editmenu)

                    MusuiGUI::UnsetWindowRect();
            }
        }
    }

    std::vector<std::pair<mcUUID, PlayerListEntry>> copyMapInAlphabeticalOrder(const std::unordered_map<mcUUID, PlayerListEntry>& sourceMap) {
        std::vector<std::pair<mcUUID, PlayerListEntry>> sortedPairs(sourceMap.begin(), sourceMap.end());

        // Sort the vector based on the 'name' field
        std::sort(sortedPairs.begin(), sortedPairs.end(), [](const auto& a, const auto& b) {
            return a.second.name < b.second.name;
        });

        return sortedPairs;
    }
};


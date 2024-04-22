#pragma once


#include "../../../../SDK/SDK.hpp"
#include <format>
#include "../../../Events/Listener.hpp"
#include "../../../Events/Input/KeyEvent.hpp"
#include "../Module.hpp"
#include "../../../GUI/Engine/Engine.hpp"
#include "../../../../SDK/SDK.hpp"
#include "../../../../SDK/Client/Render/BaseActorRenderContext.hpp"
#include "../../../../SDK/Client/Render/ItemRenderer.hpp"
#include <Windows.h>
#include <chrono>

class ArmorHUDListener : public Listener {
public:

    Module* module;
    Vec2<float> currentPos;
    bool enabled = false;

    Vec2<float> convert() {

        auto e = SDK::clientInstance->guiData;
        Vec2<float> xd = Vec2<float>(e->ScreenSize.x, e->ScreenSize.y);
        Vec2<float> LOL = Vec2<float>(e->ScreenSizeScaled.x, e->ScreenSizeScaled.y);

        return {currentPos.x * (LOL.x / xd.x), currentPos.y * (LOL.y / xd.y)};
    }

    void onRender(RenderEvent& event) override {

        if(!module->settings.getSettingByName<bool>("enabled")->value) enabled = false;

        if(SDK::clientInstance->getTopScreenName() == "hud_screen" && module->settings.getSettingByName<bool>("enabled")->value || SDK::clientInstance->getTopScreenName() == "pause_screen" && module->settings.getSettingByName<bool>("enabled")->value) {

            if(!enabled && ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("enabled")->value) {
                MusuiGUI::Notify("To change the position of ArmorHUD, Please click " + ModuleManager::getModule("ClickGUI")->settings.getSettingByName<std::string>("editmenubind")->value + " in the settings tab.");
                enabled = true;
            }

            float s = Constraints::RelativeConstraint(0.04, "height", true) * module->settings.getSettingByName<float>("uiscale")->value;

            float spacing = Constraints::RelativeConstraint(0.0135, "height", true) * module->settings.getSettingByName<float>("uiscale")->value;

            Vec2<float> settingperc = Vec2<float>(module->settings.getSettingByName<float>("percentageX")->value,
            module->settings.getSettingByName<float>("percentageY")->value);

            if (settingperc.x != 0)
                currentPos = Vec2<float>(settingperc.x * MC::windowSize.x,
                                         settingperc.y * MC::windowSize.y);
            else
                currentPos = Constraints::CenterConstraint(s * 3 + spacing * 3, s);

            if(ClickGUIRenderer::editmenu) {
                if (!module->settings.getSettingByName<bool>("vertical")->value)
                    MusuiGUI::SetWindowRect(currentPos.x, currentPos.y, s * 3 + spacing * 3, s, 18);
                else MusuiGUI::SetWindowRect(currentPos.x, currentPos.y, s, s * 3 + spacing * 3, 18);
            }

            Vec2<float> vec2;
            
            if (!module->settings.getSettingByName<bool>("vertical")->value)
             vec2 = MusuiGUI::CalculateMovedXY(currentPos.x , currentPos.y, 18, s * 3 + spacing * 3, s);
            else vec2 = MusuiGUI::CalculateMovedXY(currentPos.x , currentPos.y, 18, s, s * 3 + spacing * 3);

            currentPos.x = vec2.x;
            currentPos.y = vec2.y;

            currentPos = currentPos;

            Vec2<float> percentages = Constraints::CalculatePercentage(currentPos.x, currentPos.y);

            module->settings.setValue("percentageX", percentages.x);
            module->settings.setValue("percentageY", percentages.y);

            if(ClickGUIRenderer::editmenu)
            MusuiGUI::UnsetWindowRect();
        } else {
            enabled = false;
        }

        if (SDK::CurrentScreen != "hud_screen") ClickGUIRenderer::editmenu = false;
    }

    void onSetupAndRender(SetupAndRenderEvent& event) override {

        if (SDK::clientInstance->getTopScreenName() == "hud_screen" && module->settings.getSettingByName<bool>("enabled")->value) {

            BaseActorRenderContext barc(event.muirc->screenContext, event.muirc->clientInstance, event.muirc->clientInstance->mcgame);

            Vec2<float> convert = this->convert();

            if(SDK::clientInstance->getLocalPlayer() != nullptr)
            if (SDK::clientInstance->getLocalPlayer()->playerInventory != nullptr) {
                if (SDK::clientInstance->getLocalPlayer()->playerInventory->inventory->getItem(SDK::clientInstance->getLocalPlayer()->playerInventory->SelectedSlot)->getItem() != nullptr)
                    barc.itemRenderer->renderGuiItemNew(&barc, SDK::clientInstance->getLocalPlayer()->playerInventory->inventory->getItem(SDK::clientInstance->getLocalPlayer()->playerInventory->SelectedSlot), 0, convert.x, convert.y, 1.0f, module->settings.getSettingByName<float>("uiscale")->value, false);


                float spacing = 15 * module->settings.getSettingByName<float>("uiscale")->value;

                float xmodifier = 0.0f;
                float ymodifier = 0.0f;

                for (int i = 0; i < 4; i++) {

                    if (module->settings.getSettingByName<bool>("vertical")->value) ymodifier += spacing;
                    else xmodifier += spacing;

                    if (SDK::clientInstance->getLocalPlayer()->getArmor(i)->getItem() != nullptr) {

                        convert = this->convert();
                        barc.itemRenderer->renderGuiItemNew(&barc, SDK::clientInstance->getLocalPlayer()->getArmor(i), 0, convert.x + xmodifier, convert.y + ymodifier, 1.0f, module->settings.getSettingByName<float>("uiscale")->value, false);

                    }
                }
            }
        }
    }

public:
    explicit ArmorHUDListener(const char string[5], Module* module) {
        this->name = string;
        this->module = module;
        this->currentPos = Vec2<float>(0, 0);
    }

};

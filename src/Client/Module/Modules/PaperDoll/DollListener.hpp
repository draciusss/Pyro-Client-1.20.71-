#pragma once


#include "../../../../SDK/SDK.hpp"
#include <format>
#include "../../../Events/Listener.hpp"
#include "../../../Events/Input/KeyEvent.hpp"
#include "../Module.hpp"
#include "../../../GUI/Engine/Engine.hpp"
#include "../../../../SDK/SDK.hpp"
#include "DollListener.hpp"
#include "../../Manager.hpp"
#include <Windows.h>
#include <chrono>

class DollListener : public Listener {
public:

    Module* module;
    Vec2<float> currentPos;
    bool enabled = false;
    static inline Vec2<float> oriXY = {0.0f, 0.0f};



    Vec2<float> convert() {

        auto e = SDK::clientInstance->guiData;
        Vec2<float> xd = Vec2<float>(e->ScreenSize.x, e->ScreenSize.y);
        Vec2<float> LOL = Vec2<float>(e->ScreenSizeScaled.x, e->ScreenSizeScaled.y);

        return {currentPos.x * (LOL.x / xd.x), currentPos.y * (LOL.y / xd.y)};
    }

    void onRender(RenderEvent& event) override {

        if(SDK::clientInstance->getTopScreenName() == "hud_screen" && module->settings.getSettingByName<bool>("enabled")->value || SDK::clientInstance->getTopScreenName() == "pause_screen" && module->settings.getSettingByName<bool>("enabled")->value) {

            if(!enabled && ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("enabled")->value) {
                if(!ModuleManager::getModule("ArmorHUD")->settings.getSettingByName<bool>("enabled")->value)
                MusuiGUI::Notify("To change the position of the Paperdoll, Please click " + ModuleManager::getModule("ClickGUI")->settings.getSettingByName<std::string>("editmenubind")->value + " in the settings tab.");
                enabled = true;
            }

            float width = Constraints::RelativeConstraint(0.0052, "height", true) * module->settings.getSettingByName<float>("uiscale")->value;
            float height = Constraints::RelativeConstraint(0.0040, "height", true) * module->settings.getSettingByName<float>("uiscale")->value;


            Vec2<float> settingperc = Vec2<float>(module->settings.getSettingByName<float>("percentageX")->value,
            module->settings.getSettingByName<float>("percentageY")->value);

            if (settingperc.x != 0)
                currentPos = Vec2<float>(settingperc.x * MC::windowSize.x,
                                         settingperc.y * MC::windowSize.y);
            else if(settingperc.x == 0 and DollListener::oriXY.x != 0.0f)
                currentPos = { DollListener::oriXY.x, DollListener::oriXY.y };

            if(ClickGUIRenderer::editmenu)
                MusuiGUI::SetWindowRect(currentPos.x, currentPos.y, width, height, 19);

            Vec2<float> vec2 = MusuiGUI::CalculateMovedXY(currentPos.x , currentPos.y, 19, width, height);


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
    }



    void onSetupAndRender(SetupAndRenderEvent& event) override {


        if(SDK::screenView->VisualTree->root->LayerName == "hud_screen") {
           
            SDK::screenView->VisualTree->root->forEachControl([this](std::shared_ptr<UIControl> control) {

                if (control->LayerName == "hud_player" && module->settings.getSettingByName<bool>("enabled")->value) {

                    if(DollListener::oriXY.x == 0.0f) {
                        DollListener::oriXY.x = control->x;
                        DollListener::oriXY.y = control->y;
                    }

                    Vec2<float> convert = this->convert();

                    control->x = convert.x + 7;
                    control->y = convert.y;

                    control->scale = module->settings.getSettingByName<float>("uiscale")->value;


                    if (module->settings.getSettingByName<bool>("alwaysshow")->value || ClickGUIRenderer::editmenu) {
                        auto component = reinterpret_cast<CustomRenderComponent*>(control->components[4].get());
                        component->renderer->state = 1.0f;
                    }

                    return; // dont go through other controls
                }

            });
        }
    }

public:
    explicit DollListener(const char string[5], Module* module) {
        this->name = string;
        this->module = module;
        this->currentPos = Vec2<float>(0, 0);
    }

};
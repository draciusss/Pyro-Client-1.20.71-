#pragma once

#include <format>
#include "../../../Events/Listener.hpp"
#include "../../../Events/Input/KeyEvent.hpp"
#include "../Module.hpp"
#include "../../../GUI/Engine/Engine.hpp"
#include "../../../../SDK/SDK.hpp"
#include <Windows.h>

class DeepfryListener : public Listener {

    Module* module;

    void onRender(RenderEvent& event) override {

        if (module->settings.getSettingByName<bool>("enabled")->value) {
            if (module->settings.getSettingByName<bool>("paint")->value) MusuiGUI::ApplyPaintEffect(10.0f);
            else MusuiGUI::ApplyCombinedDeepFry();
            
        }

    }

public:
    explicit DeepfryListener(const char string[5], Module* module) {
        this->name = string;
        this->module = module;
    }

};


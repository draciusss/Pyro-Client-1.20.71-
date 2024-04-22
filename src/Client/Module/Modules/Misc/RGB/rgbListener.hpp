#pragma once
#include "../../../../Hook/Hooks/Input/MouseHook.hpp"
#include "../../../../Events/Listener.hpp"
#include "../../../../Client.hpp"

class rgbListener : public Listener {

public:

    void onLocalTick(TickEvent& event) override {
        if (MusuiGUI::rgbHue > 359 - Client::settings.getSettingByName<float>("rgb_speed")->value) MusuiGUI::rgbHue = 0;
        else MusuiGUI::rgbHue += Client::settings.getSettingByName<float>("rgb_speed")->value;
        MusuiGUI::rgbColor = MusuiGUI::HSVtoColorF(MusuiGUI::rgbHue, Client::settings.getSettingByName<float>("rgb_saturation")->value, Client::settings.getSettingByName<float>("rgb_value")->value);
    }

public:
    explicit rgbListener(const char string[5]) {
        this->name = string;
    }
};

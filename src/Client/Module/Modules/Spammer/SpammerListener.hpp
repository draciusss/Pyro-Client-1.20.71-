#pragma once

#include "../../../../SDK/SDK.hpp"
#include "../../../../SDK//Client/Network/Packet/TextPacket.hpp"
#include <format>
#include "../../../Events/Listener.hpp"
#include "../../../Events/Input/KeyEvent.hpp"
#include "../Module.hpp"
#include "../../../GUI/Engine/Engine.hpp"
#include "../../../../SDK/Client/Network/Packet/SetTitlePacket.hpp"
#include <Windows.h>
#include <chrono>

class SpammerListener : public Listener {

    std::chrono::time_point<std::chrono::high_resolution_clock> last_used;

    Module* module;
    void onLocalTick(TickEvent &event) override {
        if (module->settings.getSettingByName<bool>("enabled")->value) {
            auto player = SDK::clientInstance->getLocalPlayer();
            std::string xuid = *player->getXuid(&xuid);

            std::shared_ptr<Packet> packet = SDK::createPacket(9);
            TextPacket* akbar = reinterpret_cast<TextPacket*>(packet.get());

            akbar->type = TextPacketType::CHAT;
            akbar->message = module->settings.getSettingByName<std::string>("text")->value;
            akbar->platformId = "";
            akbar->translationNeeded = false;
            akbar->xuid = xuid;
            akbar->name = player->playerName;
            SDK::clientInstance->getPacketSender()->sendToServer(akbar);
        }
    }

public:
    explicit SpammerListener(const char string[5], Module* module) {
        this->name = string;
        this->module = module;
    }
};


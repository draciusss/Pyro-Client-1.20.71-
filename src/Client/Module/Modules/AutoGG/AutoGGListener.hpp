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

class AutoGGListener : public Listener {

    Module* module;
    bool prevPacketSent = false;

    void onPacketReceive(PacketEvent &event) override {


        if (module->settings.getSettingByName<bool>("enabled")->value) {
            bool innanillah = false;

            if (event.getPacket()->getId() == MinecraftPacketIds::Text) {

                TextPacket *pkt = reinterpret_cast<TextPacket *>(event.getPacket().get());
                std::string amongus;

                std::string nwordpls = Utils::removeNonAlphanumeric(Utils::removeColorCodes(pkt->message));

                if (nwordpls.find("won the game") != std::string::npos) {

                    innanillah = true;

                }
            }

            if (event.getPacket()->getId() == MinecraftPacketIds::SetTitle) {

                SetTitlePacket *pkt = reinterpret_cast<SetTitlePacket *>(event.getPacket().get());
                std::string amongus;

                std::string nwordpls = Utils::removeNonAlphanumeric(Utils::removeColorCodes(pkt->text));

                if (nwordpls.find("won") != std::string::npos || nwordpls.find("lost") != std::string::npos ||
                    nwordpls.find("spectating") != std::string::npos || nwordpls.find("last") != std::string::npos ||
                    nwordpls.find("Over") != std::string::npos ||
                    nwordpls.find("Sweet Victory") != std::string::npos) {

                    innanillah = true;

                }
            }

            if (innanillah) {
                std::string stringToSendYessir = module->settings.getSettingByName<std::string>("text")->value;
                if (!stringToSendYessir.empty()) {
                    if (prevPacketSent) {
                        prevPacketSent = false;
                        return;
                    }

                    //std::cout << "bing chilling lol gg" << std::endl;

                    prevPacketSent = true;

                    auto player = SDK::clientInstance->getLocalPlayer();
                    std::string xuid = *player->getXuid(&xuid);
                    std::shared_ptr<Packet> packet = SDK::createPacket(9);
                    TextPacket *akbar = reinterpret_cast<TextPacket *>(packet.get());


                    akbar->type = TextPacketType::CHAT;
                    akbar->message = stringToSendYessir;
                    akbar->platformId = "";
                    akbar->translationNeeded = false;
                    akbar->xuid = xuid;
                    akbar->name = player->playerName;

                    SDK::clientInstance->getPacketSender()->sendToServer(akbar);
                }
            }
        }
    }

    void onPacketSend(PacketEvent &event) override {
//        if (event.getPacket()->getId() == MinecraftPacketIds::Text) {
//            TextPacket *pkt = reinterpret_cast<TextPacket *>(event.getPacket().get());
//            std::string nwordpls = Utils::removeNonAlphanumeric(Utils::removeColorCodes(pkt->message));
//            std::string stringToSendYessir = module->settings.getSettingByName<std::string>("text")->value;
//
//            std::cout << nwordpls << std::endl;
//
//            if (nwordpls == stringToSendYessir) {
//
//            }
//        }
    }


public:
    explicit AutoGGListener(const char string[5], Module *

    module) {
        this->name = string;
        this->module = module;
    }

};


#include <format>
#include "../../../Events/Listener.hpp"
#include "../../../Events/Input/KeyEvent.hpp"
#include "../../../../Utils/Logger/Logger.hpp"
#include "../../../Client.hpp"
#include <Windows.h>

class GUIKeyListener : public Listener {

    bool isCapital = false;

    std::chrono::steady_clock::time_point lastOnKeyTime = std::chrono::steady_clock::now();

    void onPacketSend(PacketEvent &event) override {
        if (event.getPacket()->getId() == MinecraftPacketIds::SetLocalPlayerAsInitialized) {
            MusuiGUI::Notify("Playing on " + RaknetTickHook::towriteip);
        }
    }

    void onKey(KeyEvent &event) override {

        if(!Client::disable) {

            if (ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("enabled")) {

                if (event.GetKey() == 20 && event.GetAction() == (int)ActionType::PRESSED || event.GetKey() == VK_SHIFT) isCapital = !isCapital;

                for(auto& shi : MusuiGUI::KeybindSelectors) {
                    shi.currentOnKeyTime = std::chrono::steady_clock::now();
                }

                if(event.GetPressedKeysAsString() != "no")
                MusuiGUI::currentKeybind = event.GetPressedKeysAsString();
                else MusuiGUI::currentKeybind = "nothing";

                for (auto &box: MusuiGUI::TextBoxes) {

                    if(event.GetKey() == VK_ESCAPE || ModuleManager::getModule("ClickGUI")->IsKeybind(event.keys) && ModuleManager::getModule("ClickGUI")->IsKeyPartOfKeybind(event.key)) box.isActive = false;

                    if (event.GetKey() == VK_BACK)
                        if (event.GetAction() == (int)ActionType::RELEASED) {
                            box.isDeleting = false;
                        }

                    if (box.isActive && event.GetAction() == (int) ActionType::PRESSED)

                        if (event.GetKey() != VK_BACK && event.GetPressedKeysAsString() != "CTRL+V") box.text += event.GetKeyAsString(isCapital);
                        else if (event.GetKey() == VK_BACK) {

                            if(event.GetAction() == (int)ActionType::PRESSED) {

                                std::thread t([&box]() {

                                    bool firstTime = true;
                                    while (box.isDeleting) {

                                        if (!box.text.empty() && !firstTime) {
                                            box.text.erase(box.text.length() - 1);  // Erase the last character
                                        }

                                        if(firstTime) { std::this_thread::sleep_for(std::chrono::milliseconds(400)); firstTime = false; }
                                        else {
                                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                                        }
                                    }
                                });

                                t.detach();

                                box.isDeleting = true;

                            }

                            if (!box.text.empty()) {
                                box.text.erase(box.text.length() - 1);  // Erase the last character
                            }
                        }

                        if (box.isActive && event.GetPressedKeysAsString() == "CTRL+V") {

                            if (OpenClipboard(NULL)) {
                                HANDLE hData = GetClipboardData(CF_TEXT);
                                if (hData != NULL) {
                                    char* clipboardText = static_cast<char*>(GlobalLock(hData));
                                    if (clipboardText != NULL) {
                                        box.text += clipboardText;
                                        GlobalUnlock(hData);
                                    }
                                }
                                CloseClipboard();
                            }


                        }
                }

            } else {

                for (auto &box: MusuiGUI::TextBoxes) {

                    box.isActive = false;

                }

            }
        }

    };

public:
    explicit GUIKeyListener(const char string[5]) {
        this->name = string;
    }
};

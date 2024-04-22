#include "HitboxListener.hpp"

#include <cmath>

#include "../../Manager.hpp"
#include "../../../../Utils/Render/DrawUtils.hpp"

void renderBox(Player* player) {
	Module* box = ModuleManager::getModule("Hitbox");

	D2D1_COLOR_F color2;
	if (box->settings.getSettingByName<bool>("color_rgb")->value) color2 = MusuiGUI::rgbColor;
	else color2 = MusuiGUI::HexToColorF(box->settings.getSettingByName<std::string>("color")->value);
	auto localPlayer = SDK::clientInstance->getLocalPlayer();
	if (player == localPlayer || !player || !player->isAlive() || !localPlayer->isValidTarget(player)) return;

    auto value = (float)std::fmax(0.5f, 1 / (float)fmax(1, localPlayer->getRenderPositionComponent()->renderPos.dist(player->getRenderPositionComponent()->renderPos)));
    DrawUtils::addEntityBox(player, value, color2);}

void HitboxListener::onRender(RenderEvent& event) {
	if (!this->module->settings.getSettingByName<bool>("enabled")->value)
		return;

	if (!SDK::clientInstance || !SDK::clientInstance->getLocalPlayer() || !SDK::clientInstance->mcgame->mouseGrabbed || !SDK::clientInstance->getLocalPlayer()->level)
		return;

	auto player = SDK::clientInstance->getLocalPlayer();

    if(player != nullptr) {
        for (const auto& ent: player->level->getRuntimeActorList()) {
            if (ent != nullptr && ent->isPlayer() && ent->hasCategory(ActorCategory::Player)) {
                renderBox((Player *) ent);
            }
        }
    }
}

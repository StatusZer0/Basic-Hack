#include "hacks.hpp"

std::vector<HackItem> allHacks;

bool HacksMain::isCheating() {
    auto cheats = HacksMain::getCheats();

    bool cheating = false;
    for (const auto& cheat : cheats) {
        if (HacksMain::hackEnabled(cheat)) {
            cheating = true;
            break;
        }
    }
    return cheating;
}
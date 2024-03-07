#include "hacks.hpp"

std::vector<HackItem> allHacks;

bool Hacks::isCheating() {
    auto cheats = Hacks::getCheats();

    bool cheating = false;
    for (const auto& cheat : cheats) {
        if (Hacks::hackEnabled(cheat)) {
            cheating = true;
            break;
        }
    }
    return cheating;
}
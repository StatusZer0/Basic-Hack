// tysm FireMario211 for helping me understand how custom saving works

#ifndef SAVE_HPP
#define SAVE_HPP

#include <Geode/Geode.hpp>
#include "hacks.hpp"

using namespace geode::prelude;

struct HackSave {
    std::string name;
    HackValue value;
};

template<>
struct matjson::Serialize<HackSave> {
    static HackSave from_json(matjson::Value const& value) {
        return HackSave {
            .name = value["name"].as_string(),
            .value = value["value"]
        };
    }

    static matjson::Value to_json(HackSave const& value) {
        auto obj = matjson::Object();
        obj["name"] = value.name;
        obj["value"] = value.value;
        return obj;
    }
};

class SaveMain
{
    public: 

    static void SetupHackValues(std::string category)
    {
        HacksMain::getHackList(category);

        auto hacks = allHacks;

        for (size_t i = 0; i < hacks.size; i++)
        {
            hacks.push_back(allHacks[i]);
        }
    }

    static void SaveHackValue(HackItem value)
    {   
        std::vector<HackSave> hacks = Mod::get()->getSavedValue<std::vector<HackSave>>("values");

        for (size_t i = 0; i < hacks.size(); i++)
        {
            if (hacks[i].name == value.name)
            {
                hacks[i].assign(value);
            }
        }

        Mod::get()->setSavedValue<std::vector<HackSave>>("values", hacks);
    }

    static HackValue GetSavedValue(std::string name)
    {
        std::vector<HackSave> hacks = Mod::get()->getSavedValue<std::vector<HackSave>>("values");
        
        for (size_t i = 0; i < hacks.size(); i++)
        {
            if (hacks[i].name == name)
            {
                return hacks[i].value;
            }
        }

        HackItem item = HacksMain::getHack(name);

        return item.value;
    }
}

#endif
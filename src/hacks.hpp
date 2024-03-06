// guards, protect this file from duplicating >:(
#ifndef HACKS_HPP
#define HACKS_HPP

#include <Geode/Geode.hpp>
#include <Geode/utils/general.hpp>
#include <matjson.hpp>

using namespace geode::prelude;

// thank you so much FireMario211 for the help on understanding this stuff
// and maybe letting me use his code ;-;
enum class ValueType
{
    Bool,
    Float,
    Int,
    Char,
    Custom
};

struct HackValue
{
    ValueType type;
    union {
        bool boolValue;
        float floatValue;
        int intValue;
        char* charValue;
        HackValue* customValue;
    };

    HackValue(bool value) : type(ValueType::Bool), boolValue(value) {}

    HackValue(float value) : type(ValueType::Float), floatValue(value) {}

    HackValue(int value) : type(ValueType::Int), intValue(value) {}

    HackValue(char* value) : type(ValueType::Char), charValue(value) {}

    HackValue(HackValue* value) : type(ValueType::Custom), customValue(value) {}
};

struct HackItem
{
    std::string name;
    std::string desc;
    std::string type;
    HackValue value;
};

extern std::vector<HackItem> allHacks; // this fixes everything.     - FireMario211

class Hacks
{
    public:

    static bool hackEnabled(const std::string& name) // checks if a hack is enabled by finding it in the list, and getting it's value
    {
        for (auto& hack : allHacks)
        {
            if (hack.name == name)
            {
                return hack.value.boolValue;
            }
        }
        return false;
    }

    static void readFile(const std::string& fileName)
    {
        std::string filePath = Mod::get()->getResourcesDir().string() + "/" + fileName;
        std::ifstream file(filePath);
        std::stringstream buffer;
        if (file)
        {
            buffer << file.rdbuf();
            return buffer.str();
        } else {
            return "{}";
        }
    }

    // returns all hacks that count as cheating
    static std::vector<std::string> getCheats() {
        return {
            "Noclip"
        }
    };

    static bool isCheating();

    // gets a checkbox via name
    static HackItem* getHack(const std::string& name)
    {
        for (auto& hack : allHacks)
        {
            if (hack.name == name)
            {
                return &hack;
            }
        }
        return nullptr; //return nullptr if no checkbox was found
    }

    static void getAllHacks()
    {
        allHacks = {};

        std::vector<matjson::Value> jsonArray;
        jsonArray = matjson::parse(readFile("hacks.json")).as_array();

        for (size_t i = 0; i < jsonArray.size; ++i)
        {
            const auto& object = jsonArray[i];
            HackItem item = {
                object.get<std::string>("name"),
                object.get<std::string>("desc"),
                object.get<std::string>("type"),
                false
            };

            allHacks.push_back(item);
        }
    }
};

#endif
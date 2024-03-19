// practically this whole file was taken from prism menu. tysm FireMario211

#ifndef SAVE_HPP
#define SAVE_HPP

#include <Geode/Geode.hpp>
#include "hacks.hpp"

using namespace geode::prelude;

struct HackValuesStruct {
    std::string m_hackName;
    std::string m_hackType;
    matjson::Value m_value;
};

struct SettingHackStruct {
    matjson::Array m_hackValues;
};

template<>
struct matjson::Serialize<SettingHackStruct> {
    static SettingHackStruct from_json(matjson::Value const& value) {
        return SettingHackStruct {
            .m_hackValues = value.as_array(),
        };
    }
    static bool is_json(matjson::Value const& a) {
        return a.is_array();
    }
    static matjson::Value to_json(SettingHackStruct const& value) {
        return value.m_hackValues;
    }
};

class SettingHackValue;

class SettingHackValue : public SettingValue {
protected:
    matjson::Array m_hackValues;
public:
    SettingHackValue(std::string const& key, std::string const& modID, SettingHackStruct const& hacks)
      : SettingValue(key, modID), m_hackValues(hacks.m_hackValues) {}

    bool load(matjson::Value const& json) override {
        if (!json.is_array()) return false;
        m_hackValues = json.as_array();
        return true;
    }
    bool save(matjson::Value& json) const override {
        json = m_hackValues;
        return true;
    }
    SettingNode* createNode(float width) override;
    void setHacks(SettingHackStruct const& value) {
        m_hackValues = value.m_hackValues;
    }
    SettingHackStruct getHacks() const {
        return { m_hackValues };
    }
};

template<>
struct SettingValueSetter<SettingHackStruct> {
    static SettingHackStruct get(SettingValue* setting) {
        auto hackSetting = static_cast<SettingHackValue*>(setting);
        struct SettingHackStruct defaultStruct = { hackSetting->getHacks() };
        return defaultStruct;
    };
    static void set(SettingHackValue* setting, SettingHackStruct const& value) {
        setting->setHacks(value);
    };
};

class SettingHackNode : public SettingNode {
protected:
    bool init(SettingHackValue* value, float width) {
        if (!SettingNode::init(value))
            return false;
        return true;
    }
public:
    // Geode calls this to query if the setting value has been changed, 
    // and those changes haven't been committed
    bool hasUncommittedChanges() override {
        return false;
    }

    // Geode calls this to query if the setting has a value that is 
    // different from its default value
    bool hasNonDefaultValue() override {
        return true;
    }

    // Geode calls this to reset the setting's value back to default
    void resetToDefault() override {

    }
    static SettingHackNode* create(SettingHackValue* value, float width) {
        auto ret = new SettingHackNode;
        if (ret && ret->init(value, width)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};
#endif

class SaveSystem
{
    public:

    static void saveAllHacks()
    {
        HacksMain::getHackList();

        Mod::get()->setSavedValue<std::vector<HackItem>>("hackValues", allHacks);
    }

    static void setupSaves()
    {
        saveAllHacks();

        std::vector<HackValue> allValues;

        for (int i = 0; i < allHacks.size() - 1; i++)
        {
            allValues.push_back(allHacks[i]);
        }

        Mod::get()->setSavedValue<std::vector<HackValue>>
    }

    static HackValue getHackValue(std::string hackName)
    {
        auto hack = HacksMain::getHack(hackName);

        return hack->value;
    }

    static void saveHackValue(HackValue value)
    {
        
    }
}

#endif
#ifndef _STORAGES_H
#define _STORAGES_H

#include <map>
#include <string>
#include "Common.h"

#define CURRENT_PATCH   10
#define CURRENT_BUILD   8606 // 2.4.3 (5875 - 1.12.1)
#define TBC_START_BUILD 5610 // 2.0.0

struct BroadcastText
{
    BroadcastText(std::string maleText, std::string femaleText) : m_maleText(maleText), m_femaleText(femaleText) {};
    std::string m_maleText;
    std::string m_femaleText;
};

class WorldDatabase
{
public:
    static void LoadCreatures();
    static void LoadGameObjects();
    static void LoadItems();
    static void LoadQuests();
    static void LoadSpells();
    static void LoadFactions();
    static void LoadSounds();
    static void LoadBroadcastTexts();

    static void LoadWorldDatabase()
    {
        LoadCreatures();
        LoadGameObjects();
        LoadItems();
        LoadQuests();
        LoadSpells();
        LoadFactions();
        LoadSounds();
        LoadBroadcastTexts();
    }

    static std::string GetCreatureName(uint32 id)
    {
        auto const itr = m_creatureNames.find(id);
        if (itr != m_creatureNames.cend())
            return itr->second;
        return "UNKNOWN";
    }
    static std::string GetGameObjectName(uint32 id)
    {
        auto const itr = m_gameObjectNames.find(id);
        if (itr != m_gameObjectNames.cend())
            return itr->second;
        return "UNKNOWN";
    }
    static std::string GetItemName(uint32 id)
    {
        auto const itr = m_itemNames.find(id);
        if (itr != m_itemNames.cend())
            return itr->second;
        return "UNKNOWN";
    }
    static std::string GetQuestName(uint32 id)
    {
        auto const itr = m_questNames.find(id);
        if (itr != m_questNames.cend())
            return itr->second;
        return "UNKNOWN";
    }
    static std::string GetSpellName(uint32 id)
    {
        auto const itr = m_spellNames.find(id);
        if (itr != m_spellNames.cend())
            return itr->second;
        return "UNKNOWN";
    }
    static std::string GetFactionName(uint32 id)
    {
        auto const itr = m_factionNames.find(id);
        if (itr != m_factionNames.cend())
            return itr->second;
        return "UNKNOWN";
    }
    static std::string GetSoundName(uint32 id)
    {
        auto const itr = m_soundNames.find(id);
        if (itr != m_soundNames.cend())
            return itr->second;
        return "UNKNOWN";
    }
    static uint32 GetBroadcastTextId(std::string text)
    {
        auto index = text.find("$N", 0);
        if (index != std::string::npos)
            text.replace(index, 2, "$n");

        for (auto const& itr : m_broadcastTexts)
        {
            if (itr.second.m_maleText == text || itr.second.m_femaleText == text)
                return itr.first;
        }
        return 0;
    }
private:
    static std::map<uint32, std::string> m_creatureNames;
    static std::map<uint32, std::string> m_gameObjectNames;
    static std::map<uint32, std::string> m_itemNames;
    static std::map<uint32, std::string> m_questNames;
    static std::map<uint32, std::string> m_spellNames;
    static std::map<uint32, std::string> m_factionNames;
    static std::map<uint32, std::string> m_soundNames;
    static std::map<uint32, BroadcastText> m_broadcastTexts;
};

#endif

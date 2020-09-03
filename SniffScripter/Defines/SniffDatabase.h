#ifndef _SNIFF_DB_H
#define _SNIFF_DB_H

#include <vector>
#include <string>
#include "Common.h"

struct CreatureText
{
    uint32 creatureId = 0;
    uint32 groupId = 0;
    std::string text;
    uint32 chatType = 0;
    std::string comment;
};

class SniffDatabase
{
public:
    static std::string m_databaseName;

    static void LoadCreatureTextTemplate();
    static void LoadCreatureSpawns();
    static void LoadGameObjectSpawns();
    static void LoadSniffDatabase()
    {
        LoadCreatureTextTemplate();
        LoadCreatureSpawns();
        LoadGameObjectSpawns();
    }

    static void LoadSpellCastStart(char const* whereClause);
    static void LoadSpellCastGo(char const* whereClause);
    static void LoadPlaySound(char const* whereClause);
    static void LoadPlayMusic(char const* whereClause);
    template <class T>
    static void LoadCreatureUpdate(char const* fieldName, char const* whereClause);
    static void LoadCreatureText(char const* whereClause);
    static void LoadCreatureMovement(char const* whereClause);
    static void LoadCreatureEmote(char const* whereClause);
    static void LoadCreatureAttackStart(char const* whereClause);
    static void LoadCreatureAttackStop(char const* whereClause);
    static void LoadCreatureDestroy(char const* whereClause);
    static void LoadCreatureCreate2(char const* whereClause);
    static void LoadCreatureCreate1(char const* whereClause);
    static void LoadGameObjectDestroy(char const* whereClause);
    static void LoadGameObjectCreate2(char const* whereClause);
    static void LoadGameObjectCreate1(char const* whereClause);
    template <class T>
    static void LoadGameObjectUpdate(char const* fieldName, char const* whereClause);
    static void LoadQuestAcceptTimes(char const* whereClause);
    static void LoadQuestCompleteTimes(char const* whereClause);
    static void LoadGameObjectUseTimes(char const* whereClause);
    static void LoadItemUseTimes(char const* whereClause);

    static CreatureText const* GetCreatureTextTemplate(uint32 creatureId, uint32 groupId)
    {
        for (auto const& itr : m_creatureTextTemplates)
        {
            if (itr.creatureId == creatureId && itr.groupId == groupId)
                return &itr;
        }
        return nullptr;
    }

    static uint32 GetCreatureFieldValueBeforeTime(uint32 guid, uint32 unixtime, char const* fieldName);

    static uint32 GetCreatureEntryFromGuid(uint32 guid) { return m_creatureGuidToEntry[guid]; }
    static uint32 GetGameObjectEntryFromGuid(uint32 guid) { return m_gameObjectGuidToEntry[guid]; }
private:
    static std::vector<CreatureText> m_creatureTextTemplates;
    static std::map<uint32, uint32> m_creatureGuidToEntry;
    static std::map<uint32, uint32> m_gameObjectGuidToEntry;
};

#endif

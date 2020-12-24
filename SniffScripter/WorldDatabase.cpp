#include <string>
#include <map>
#include "Defines\WorldDatabase.h"
#include "Database\Database.h"

extern Database GameDb;

#define CURRENT_PATCH 10
#define CURRENT_BUILD 5875

std::map<uint32, std::string> WorldDatabase::m_creatureNames;

void WorldDatabase::LoadCreatures()
{
    printf("Loading creature database.\n");
    //                                                              0        1
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `entry`, `name` FROM `creature_template` t1 WHERE `patch`=(SELECT max(`patch`) FROM `creature_template` t2 WHERE t1.`entry`=t2.`entry` && `patch` <= %u)", CURRENT_PATCH))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 entry = pFields[0].getUInt32();
            std::string name = pFields[1].getCppString();
            m_creatureNames.insert(std::make_pair(entry, name));

        } while (result->NextRow());
    }
}

std::map<uint32, std::string> WorldDatabase::m_gameObjectNames;

void WorldDatabase::LoadGameObjects()
{
    printf("Loading gameobject database.\n");
    //                                                              0        1
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `entry`, `name` FROM `gameobject_template` t1 WHERE `patch`=(SELECT max(`patch`) FROM `gameobject_template` t2 WHERE t1.`entry`=t2.`entry` && `patch` <= %u)", CURRENT_PATCH))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 entry = pFields[0].getUInt32();
            std::string name = pFields[1].getCppString();
            m_gameObjectNames.insert(std::make_pair(entry, name));

        } while (result->NextRow());
    }
}

std::map<uint32, std::string> WorldDatabase::m_itemNames;

void WorldDatabase::LoadItems()
{
    printf("Loading item database.\n");
    //                                                              0        1
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `entry`, `name` FROM `item_template` t1 WHERE `patch`=(SELECT max(`patch`) FROM `item_template` t2 WHERE t1.`entry`=t2.`entry` && `patch` <= %u)", CURRENT_PATCH))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 entry = pFields[0].getUInt32();
            std::string name = pFields[1].getCppString();
            m_itemNames.insert(std::make_pair(entry, name));

        } while (result->NextRow());
    }
}

std::map<uint32, std::string> WorldDatabase::m_questNames;

void WorldDatabase::LoadQuests()
{
    printf("Loading quest database.\n");
    //                                                              0        1
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `entry`, `Title` FROM `quest_template` t1 WHERE `patch`=(SELECT max(`patch`) FROM `quest_template` t2 WHERE t1.`entry`=t2.`entry` && `patch` <= %u)", CURRENT_PATCH))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 entry = pFields[0].getUInt32();
            std::string name = pFields[1].getCppString();
            m_questNames.insert(std::make_pair(entry, name));

        } while (result->NextRow());
    }
}

std::map<uint32, std::string> WorldDatabase::m_spellNames;

void WorldDatabase::LoadSpells()
{
    printf("Loading spell database.\n");
    //                                                              0        1
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `entry`, `name` FROM `spell_template` t1 WHERE `build`=(SELECT max(`build`) FROM `spell_template` t2 WHERE t1.`entry`=t2.`entry` && `build` <= %u)", CURRENT_BUILD))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 entry = pFields[0].getUInt32();
            std::string name = pFields[1].getCppString();
            m_spellNames.insert(std::make_pair(entry, name));

        } while (result->NextRow());
    }
}

std::map<uint32, std::string> WorldDatabase::m_factionNames;

void WorldDatabase::LoadFactions()
{
    std::map<uint32, std::string> factionNames;
    printf("Loading faction database.\n");
    //                                                              0     1
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `id`, `name` FROM `faction` t1 WHERE `build`=(SELECT max(`build`) FROM `faction` t2 WHERE t1.`id`=t2.`id` && `build` <= %u)", CURRENT_BUILD))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 id = pFields[0].getUInt32();
            std::string name = pFields[1].getCppString();
            factionNames.insert(std::make_pair(id, name));

        } while (result->NextRow());
    }
    printf("Loading faction template database.\n");
    //                                                              0     1   
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `id`, `faction_id` FROM `faction_template` t1 WHERE `build`=(SELECT max(`build`) FROM `faction_template` t2 WHERE t1.`id`=t2.`id` && `build` <= %u)", CURRENT_BUILD))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 id = pFields[0].getUInt32();
            uint32 faction_id = pFields[1].getUInt32();
            m_factionNames.insert(std::make_pair(id, factionNames[faction_id]));

        } while (result->NextRow());
    }
}

std::map<uint32, std::string> WorldDatabase::m_soundNames;

void WorldDatabase::LoadSounds()
{
    printf("Loading sound database.\n");
    //                                                              0     1    
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `id`, `name` FROM `sound_entries`"))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 id = pFields[0].getUInt32();
            std::string name = pFields[1].getCppString();
            m_soundNames.insert(std::make_pair(id, name));

        } while (result->NextRow());
    }
}

std::map<uint32, BroadcastText> WorldDatabase::m_broadcastTexts;

void WorldDatabase::LoadBroadcastTexts()
{
    printf("Loading broadcast text database.\n");
    //                                                              0        1            2      
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `entry`, `male_text`, `female_text` FROM `broadcast_text`"))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 entry = pFields[0].getUInt32();
            std::string maleText = pFields[1].getCppString();
            auto index = maleText.find("$N", 0);
            if (index != std::string::npos)
                maleText.replace(index, 2, "$n");

            std::string femaleText = pFields[2].getCppString();
            index = femaleText.find("$N", 0);
            if (index != std::string::npos)
                femaleText.replace(index, 2, "$n");

            m_broadcastTexts.insert(std::make_pair(entry, BroadcastText(maleText, femaleText)));

        } while (result->NextRow());
    }
    printf("loaded %u texts\n", m_broadcastTexts.size());
}
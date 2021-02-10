#include <string>
#include <vector>
#include <map>
#include "Defines\SniffDatabase.h"
#include "Defines\SniffedEvents.h"
#include "Defines\TimelineMaker.h"
#include "Database\Database.h"

extern Database GameDb;

std::string SniffDatabase::m_databaseName;
std::vector<CreatureText> SniffDatabase::m_creatureTextTemplates;

void SniffDatabase::LoadCreatureTextTemplate()
{
    printf("Loading creature text database.\n");
    //                                                              0        1           2       3            4
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `entry`, `group_id`, `text`, `chat_type`, `comment` FROM `%s`.`creature_text_template`", m_databaseName.c_str()))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            CreatureText textEntry;
            textEntry.creatureId = pFields[0].getUInt32();
            textEntry.groupId = pFields[1].getUInt32();
            textEntry.text = pFields[2].getCppString();
            textEntry.chatType = pFields[3].getUInt32();
            textEntry.comment = pFields[4].getCppString();

            m_creatureTextTemplates.emplace_back(std::move(textEntry));
        } while (result->NextRow());
    }
}

std::map<uint32, uint32> SniffDatabase::m_creatureGuidToEntry;

void SniffDatabase::LoadCreatureSpawns()
{
    printf("Loading creature spawn database.\n");
    //                                                              0       1
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `id` FROM `%s`.`creature`", m_databaseName.c_str()))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();
            uint32 id = pFields[1].getUInt32();

            m_creatureGuidToEntry[guid] = id;
        } while (result->NextRow());
    }
}


std::map<uint32, uint32> SniffDatabase::m_gameObjectGuidToEntry;

void SniffDatabase::LoadGameObjectSpawns()
{
    printf("Loading gameobject spawn database.\n");
    //                                                              0       1
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `id` FROM `%s`.`gameobject`", m_databaseName.c_str()))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();
            uint32 id = pFields[1].getUInt32();

            m_gameObjectGuidToEntry[guid] = id;
        } while (result->NextRow());
    }
}

std::map<uint32, std::string> SniffDatabase::m_playerNames;

void SniffDatabase::LoadPlayerNames()
{
    printf("Loading player database.\n");
    //                                                              0       1
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `name` FROM `%s`.`player`", m_databaseName.c_str()))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();
            std::string name = pFields[1].getCppString();

            m_playerNames[guid] = name;
        } while (result->NextRow());
    }
}

void SniffDatabase::LoadSpellCastStart(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `caster_guid`, `caster_id`, `caster_type`, `spell_id`, `target_guid`, `target_id`, `target_type` FROM `%s`.`spell_cast_start` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 casterGuid = pFields[1].getUInt32();
            uint32 casterId = pFields[2].getUInt32();
            std::string casterType = pFields[3].getCppString();
            uint32 spellId = pFields[4].getUInt32();
            uint32 targetGuid = pFields[5].getUInt32();
            uint32 targetId = pFields[6].getUInt32();
            std::string targetType = pFields[7].getCppString();

            std::shared_ptr<SniffedEvent_SpellCastStart> newEvent = std::make_shared<SniffedEvent_SpellCastStart>(spellId, casterGuid, casterId, casterType, targetGuid, targetId, targetType);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

std::map<uint32, std::vector<KnownObject>> SniffDatabase::m_spellGoHitTargets;

void SniffDatabase::LoadSpellCastGoHitTargets()
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `list_id`, `target_guid`, `target_id`, `target_type` FROM `%s`.`spell_cast_go_target` ORDER BY `list_id`", SniffDatabase::m_databaseName.c_str()))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 listId = pFields[0].getUInt32();
            KnownObject target;
            target.m_guid = pFields[1].getUInt32();
            target.m_entry = pFields[2].getUInt32();
            target.m_type = pFields[3].getCppString();
            m_spellGoHitTargets[listId].push_back(target);

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadSpellCastGo(char const* whereClause)
{
    static bool loadedTargets = false;
    if (!loadedTargets)
    {
        LoadSpellCastGoHitTargets();
        loadedTargets = true;
    }
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `caster_guid`, `caster_id`, `caster_type`, `spell_id`, `main_target_guid`, `main_target_id`, `main_target_type`, `hit_targets_count`, `hit_targets_list_id` FROM `%s`.`spell_cast_go` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 casterGuid = pFields[1].getUInt32();
            uint32 casterId = pFields[2].getUInt32();
            std::string casterType = pFields[3].getCppString();
            uint32 spellId = pFields[4].getUInt32();
            uint32 targetGuid = pFields[5].getUInt32();
            uint32 targetId = pFields[6].getUInt32();
            std::string targetType = pFields[7].getCppString();
            uint32 hitTargetsCount = pFields[8].getUInt32();
            uint32 hitTargetsListId = pFields[9].getUInt32();

            std::shared_ptr<SniffedEvent_SpellCastGo> newEvent = std::make_shared<SniffedEvent_SpellCastGo>(spellId, casterGuid, casterId, casterType, targetGuid, targetId, targetType, hitTargetsCount, hitTargetsListId);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadPlaySound(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `sound`, `source_guid`, `source_id`, `source_type` FROM `%s`.`play_sound` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 soundId = pFields[1].getUInt32();
            uint32 sourceGuid = pFields[2].getUInt32();
            uint32 sourceId = pFields[3].getUInt32();
            std::string sourceType = pFields[4].getCppString();

            std::shared_ptr<SniffedEvent_PlaySound> newEvent = std::make_shared<SniffedEvent_PlaySound>(soundId, sourceGuid, sourceId, sourceType);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadPlayMusic(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `music` FROM `%s`.`play_music` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 musicId = pFields[1].getUInt32();

            std::shared_ptr<SniffedEvent_PlayMusic> newEvent = std::make_shared<SniffedEvent_PlayMusic>(musicId);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

template void SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_unit_flags>(char const* fieldName, char const* whereClause);
template void SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_npc_flags>(char const* fieldName, char const* whereClause);
template void SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_stand_state>(char const* fieldName, char const* whereClause);
template void SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_emote_state>(char const* fieldName, char const* whereClause);
template void SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_faction>(char const* fieldName, char const* whereClause);
template void SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_display_id>(char const* fieldName, char const* whereClause);
template void SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_entry>(char const* fieldName, char const* whereClause);

template <class T>
void SniffDatabase::LoadCreatureUpdate(char const* fieldName, char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `unixtimems`, `%s` FROM `%s`.`creature_values_update` WHERE %s && (`%s` IS NOT NULL) ORDER BY `unixtimems`", fieldName, SniffDatabase::m_databaseName.c_str(), whereClause, fieldName))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();;
            uint32 creatureId = GetCreatureEntryFromGuid(guid);
            uint64 unixtimems = pFields[1].getUInt64();
            uint32 value = pFields[2].getUInt32();

            std::shared_ptr<T> newEvent = std::make_shared<T>(guid, creatureId, value);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadCreatureText(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `guid`, `entry`, `group_id` FROM `%s`.`creature_text` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 creatureGuid = pFields[1].getUInt32();
            uint32 creatureId = pFields[2].getUInt32();
            uint32 groupId = pFields[3].getUInt32();

            CreatureText const* textEntry = SniffDatabase::GetCreatureTextTemplate(creatureId, groupId);
            std::string text = textEntry ? textEntry->text : "<error>";
            uint32 chatType = textEntry ? textEntry->chatType : 0;
            std::string comment = textEntry ? textEntry->comment : "<error>";

            std::shared_ptr<SniffedEvent_CreatureText> newEvent = std::make_shared<SniffedEvent_CreatureText>(creatureGuid, creatureId, text, chatType, comment);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadCreatureMovement(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `point`, `move_time`, `start_position_x`, `start_position_y`, `start_position_z`, `end_position_x`, `end_position_y`, `end_position_z`, `orientation`, `unixtimems` FROM `%s`.`creature_movement_server` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();
            uint32 creatureId = GetCreatureEntryFromGuid(guid);
            uint32 point = pFields[1].getUInt32();
            uint32 moveTime = pFields[2].getUInt32();
            float startX = pFields[3].getFloat();
            float startY = pFields[4].getFloat();
            float startZ = pFields[5].getFloat();
            float endX = pFields[6].getFloat();
            float endY = pFields[7].getFloat();
            float endZ = pFields[8].getFloat();
            float orientation = pFields[9].getFloat();
            uint64 unixtimems = pFields[10].getUInt64();

            std::shared_ptr<SniffedEvent_CreatureMovement> newEvent = std::make_shared<SniffedEvent_CreatureMovement>(guid, creatureId, point, moveTime, startX, startY, startZ, endX, endY, endZ, orientation);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadCreatureEmote(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `emote_id`, `emote_name`, `guid` FROM `%s`.`creature_emote` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 emoteId = pFields[1].getUInt32();
            std::string emoteName = pFields[2].getCppString();
            uint32 guid = pFields[3].getUInt32();
            uint32 creatureId = GetCreatureEntryFromGuid(guid);

            std::shared_ptr<SniffedEvent_CreatureEmote> newEvent = std::make_shared<SniffedEvent_CreatureEmote>(guid, creatureId, emoteId, emoteName);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadCreatureAttackStart(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `victim_guid`, `victim_id`, `victim_type`, `guid` FROM `%s`.`creature_attack_start` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 victimGuid = pFields[1].getUInt32();
            uint32 victimId = pFields[2].getUInt32();
            std::string victimType = pFields[3].getCppString();
            uint32 guid = pFields[4].getUInt32();
            uint32 creatureId = GetCreatureEntryFromGuid(guid);

            std::shared_ptr<SniffedEvent_CreatureAttackStart> newEvent = std::make_shared<SniffedEvent_CreatureAttackStart>(guid, creatureId, victimGuid, victimId, victimType);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadCreatureAttackStop(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `victim_guid`, `victim_id`, `victim_type`, `guid` FROM `%s`.`creature_attack_stop` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 victimGuid = pFields[1].getUInt32();
            uint32 victimId = pFields[2].getUInt32();
            std::string victimType = pFields[3].getCppString();
            uint32 guid = pFields[4].getUInt32();
            uint32 creatureId = GetCreatureEntryFromGuid(guid);

            std::shared_ptr<SniffedEvent_CreatureAttackStop> newEvent = std::make_shared<SniffedEvent_CreatureAttackStop>(guid, creatureId, victimGuid, victimId, victimType);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadCreatureDeath(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `guid` FROM `%s`.`creature_values_update` WHERE (`current_health`=0) && %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 guid = pFields[1].getUInt32();
            uint32 creatureId = GetCreatureEntryFromGuid(guid);

            std::shared_ptr<SniffedEvent_CreatureDeath> newEvent = std::make_shared<SniffedEvent_CreatureDeath>(guid, creatureId);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadCreatureDestroy(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `unixtimems` FROM `%s`.`creature_destroy_time` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();
            uint32 creatureId = GetCreatureEntryFromGuid(guid);
            uint64 unixtimems = pFields[1].getUInt64();

            std::shared_ptr<SniffedEvent_CreatureDestroy> newEvent = std::make_shared<SniffedEvent_CreatureDestroy>(guid, creatureId);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadCreatureCreate2(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `unixtimems`, `position_x`, `position_y`, `position_z`, `orientation` FROM `%s`.`creature_create2_time` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();
            uint32 creatureId = GetCreatureEntryFromGuid(guid);
            uint64 unixtimems = pFields[1].getUInt64();
            float position_x = pFields[2].getFloat();
            float position_y = pFields[3].getFloat();
            float position_z = pFields[4].getFloat();
            float orientation = pFields[5].getFloat();

            std::shared_ptr<SniffedEvent_CreatureCreate2> newEvent = std::make_shared<SniffedEvent_CreatureCreate2>(guid, creatureId, position_x, position_y, position_z, orientation);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadCreatureCreate1(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `unixtimems`, `position_x`, `position_y`, `position_z`, `orientation` FROM `%s`.`creature_create1_time` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();
            uint32 creatureId = GetCreatureEntryFromGuid(guid);
            uint64 unixtimems = pFields[1].getUInt64();
            float position_x = pFields[2].getFloat();
            float position_y = pFields[3].getFloat();
            float position_z = pFields[4].getFloat();
            float orientation = pFields[5].getFloat();

            std::shared_ptr<SniffedEvent_CreatureCreate1> newEvent = std::make_shared<SniffedEvent_CreatureCreate1>(guid, creatureId, position_x, position_y, position_z, orientation);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadGameObjectDestroy(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `unixtimems` FROM `%s`.`gameobject_destroy_time` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();
            uint32 entry = GetGameObjectEntryFromGuid(guid);
            uint64 unixtimems = pFields[1].getUInt64();

            std::shared_ptr<SniffedEvent_GameObjectDestroy> newEvent = std::make_shared<SniffedEvent_GameObjectDestroy>(guid, entry);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadGameObjectCreate2(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `unixtimems`, `position_x`, `position_y`, `position_z`, `orientation` FROM `%s`.`gameobject_create2_time` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();
            uint32 entry = GetGameObjectEntryFromGuid(guid);
            uint64 unixtimems = pFields[1].getUInt64();
            float position_x = pFields[2].getFloat();
            float position_y = pFields[3].getFloat();
            float position_z = pFields[4].getFloat();
            float orientation = pFields[5].getFloat();

            std::shared_ptr<SniffedEvent_GameObjectCreate2> newEvent = std::make_shared<SniffedEvent_GameObjectCreate2>(guid, entry, position_x, position_y, position_z, orientation);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadGameObjectCreate1(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `unixtimems`, `position_x`, `position_y`, `position_z`, `orientation` FROM `%s`.`gameobject_create1_time` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();
            uint32 entry = GetGameObjectEntryFromGuid(guid);
            uint64 unixtimems = pFields[1].getUInt64();
            float position_x = pFields[2].getFloat();
            float position_y = pFields[3].getFloat();
            float position_z = pFields[4].getFloat();
            float orientation = pFields[5].getFloat();

            std::shared_ptr<SniffedEvent_GameObjectCreate1> newEvent = std::make_shared<SniffedEvent_GameObjectCreate1>(guid, entry, position_x, position_y, position_z, orientation);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadGameObjectCustomAnim(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `anim_id`, `unixtimems` FROM `%s`.`gameobject_custom_anim` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();
            uint32 entry = GetGameObjectEntryFromGuid(guid);
            uint32 animId = pFields[1].getUInt32();
            uint64 unixtimems = pFields[2].getUInt64();

            std::shared_ptr<SniffedEvent_GameObjectCustomAnim> newEvent = std::make_shared<SniffedEvent_GameObjectCustomAnim>(guid, entry, animId);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

template void SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_flags>(char const* fieldName, char const* whereClause);
template void SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_state>(char const* fieldName, char const* whereClause);

template <class T>
void SniffDatabase::LoadGameObjectUpdate(char const* fieldName, char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `unixtimems`, `%s` FROM `%s`.`gameobject_values_update` WHERE %s && (`%s` IS NOT NULL) ORDER BY `unixtimems`", fieldName, SniffDatabase::m_databaseName.c_str(), whereClause, fieldName))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 guid = pFields[0].getUInt32();;
            uint32 entry = GetGameObjectEntryFromGuid(guid);
            uint64 unixtimems = pFields[1].getUInt64();
            uint32 value = pFields[2].getUInt32();

            std::shared_ptr<T> newEvent = std::make_shared<T>(guid, entry, value);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadQuestAcceptTimes(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `object_guid`, `object_id`, `object_type`, `quest_id` FROM `%s`.`client_quest_accept` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 objectGuid = pFields[1].getUInt32();
            uint32 objectId = pFields[2].getUInt32();
            std::string objectType = pFields[3].getCppString();
            uint32 questId = pFields[4].getUInt32();

            std::shared_ptr<SniffedEvent_QuestAccept> newEvent = std::make_shared<SniffedEvent_QuestAccept>(questId, objectGuid, objectId, objectType);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadQuestCompleteTimes(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `object_guid`, `object_id`, `object_type`, `quest_id` FROM `%s`.`client_quest_complete` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 objectGuid = pFields[1].getUInt32();
            uint32 objectId = pFields[2].getUInt32();
            std::string objectType = pFields[3].getCppString();
            uint32 questId = pFields[4].getUInt32();

            std::shared_ptr<SniffedEvent_QuestComplete> newEvent = std::make_shared<SniffedEvent_QuestComplete>(questId, objectGuid, objectId, objectType);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadCreatureInteractTimes(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `guid` FROM `%s`.`client_creature_interact` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 guid = pFields[1].getUInt32();
            uint32 entry = GetCreatureEntryFromGuid(guid);

            std::shared_ptr<SniffedEvent_CreatureInteract> newEvent = std::make_shared<SniffedEvent_CreatureInteract>(guid, entry);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadGameObjectUseTimes(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `guid` FROM `%s`.`client_gameobject_use` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 guid = pFields[1].getUInt32();
            uint32 entry = GetGameObjectEntryFromGuid(guid);

            std::shared_ptr<SniffedEvent_GameObjectUse> newEvent = std::make_shared<SniffedEvent_GameObjectUse>(guid, entry);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadItemUseTimes(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems`, `entry` FROM `%s`.`client_item_use` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();
            uint32 entry = pFields[1].getUInt32();

            std::shared_ptr<SniffedEvent_ItemUse> newEvent = std::make_shared<SniffedEvent_ItemUse>(entry);
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadClientReclaimCorpse(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems` FROM `%s`.`client_reclaim_corpse` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();

            std::shared_ptr<SniffedEvent_ReclaimCorpse> newEvent = std::make_shared<SniffedEvent_ReclaimCorpse>();
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffDatabase::LoadClientReleaseSpirit(char const* whereClause)
{
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `unixtimems` FROM `%s`.`client_release_spirit` WHERE %s ORDER BY `unixtimems`", SniffDatabase::m_databaseName.c_str(), whereClause))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint64 unixtimems = pFields[0].getUInt64();

            std::shared_ptr<SniffedEvent_ReleaseSpirit> newEvent = std::make_shared<SniffedEvent_ReleaseSpirit>();
            TimelineMaker::m_eventsMap.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

uint32 SniffDatabase::GetCreatureFieldValueBeforeTime(uint32 guid, uint64 unixtimems, char const* fieldName)
{
    uint32 field = 0;
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `%s` FROM `%s`.`creature` WHERE `guid`=%u", fieldName, SniffDatabase::m_databaseName.c_str(), guid))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            field = pFields[0].getUInt32();

        } while (result->NextRow());
    }

    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `%s` FROM `%s`.`creature_values_update` WHERE (`guid` = %u) && (`unixtimems` < %llu) && (`%s` IS NOT NULL) ORDER BY `unixtimems`", fieldName, SniffDatabase::m_databaseName.c_str(), guid, unixtimems, fieldName))
    {
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            field = pFields[0].getUInt32();

        } while (result->NextRow());
    }
    return field;
}
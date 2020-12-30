#include <map>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include "Defines\SniffedEvents.h"
#include "Defines\SniffDatabase.h"
#include "Defines\TimelineMaker.h"
#include "Defines\ScriptCommands.h"
#include "Defines\Helpers.h"
#include "Defines\WorldDatabase.h"
#include "Database\Database.h"

extern Database GameDb;
std::multimap<uint64, std::shared_ptr<SniffedEvent>> TimelineMaker::m_eventsMap;

void TimelineMaker::CreateTimelineForGuids(uint32 uiStartTime, std::vector<uint32>& vCreatureGuids, std::vector<uint32> vGameObjectGuids, bool showReclaimCorpse, bool showReleaseSpirit, bool showQuests, bool showCreatureInteract, bool showGameObjectUse, bool showItemUse, bool showDeaths, bool showAttacks, bool showTexts, bool showEmotes, bool showMoves, bool showUpdates, bool showCasts, bool showSounds)
{
    for (const auto& guid : vCreatureGuids)
    {
        //uint32 creatureId = SniffDatabase::GetCreatureEntryFromGuid(guid);

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
            SniffDatabase::LoadCreatureCreate1(whereClause);
        }

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
            SniffDatabase::LoadCreatureCreate2(whereClause);
        }

        if (!showCreatureInteract)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
            SniffDatabase::LoadCreatureInteractTimes(whereClause);
        }

        if (showAttacks)
        {
            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadCreatureAttackStart(whereClause);
            }

            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadCreatureAttackStop(whereClause);
            }
        }

        if (showTexts)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
            SniffDatabase::LoadCreatureText(whereClause);
        }

        if (showEmotes)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
            SniffDatabase::LoadCreatureEmote(whereClause);
        }

        if (showMoves)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`id` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadCreatureMovement(whereClause);
        }

        if (!showDeaths)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
            SniffDatabase::LoadCreatureDeath(whereClause);
        }

        if (showCasts)
        {
            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`caster_guid` = %u) && (`caster_type` = 'Creature') && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadSpellCastStart(whereClause);
            }

            {
                char whereClause[256] = {};
                snprintf(whereClause, 255, "(`caster_guid` != %u) && (`target_guid` = %u) && (`target_type` = 'Creature') && (`unixtimems` >= (%u * 1000))", guid, guid, uiStartTime);
                SniffDatabase::LoadSpellCastStart(whereClause);
            }

            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`caster_guid` = %u) && (`caster_type` = 'Creature') && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadSpellCastGo(whereClause);
            }

            {
                char whereClause[256] = {};
                snprintf(whereClause, 255, "(`caster_guid` != %u) && (`main_target_guid` = %u) && (`main_target_type` = 'Creature') && (`unixtimems` >= (%u * 1000))", guid, guid, uiStartTime);
                SniffDatabase::LoadSpellCastGo(whereClause);
            }
        }

        if (showUpdates)
        {
            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_entry>("entry", whereClause);
            }

            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_display_id>("display_id", whereClause);
            }

            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_faction>("faction", whereClause);
            }

            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_emote_state>("emote_state", whereClause);
            }

            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_stand_state>("stand_state", whereClause);
            }

            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_npc_flags>("npc_flags", whereClause);
            }

            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_unit_flags>("unit_flags", whereClause);
            }
        }

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
            SniffDatabase::LoadCreatureDestroy(whereClause);
        }
    }

    for (const auto& guid : vGameObjectGuids)
    {
        //uint32 gameObjectId = SniffDatabase::GetGameObjectEntryFromGuid(guid);

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
            SniffDatabase::LoadGameObjectCreate1(whereClause);
        }

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
            SniffDatabase::LoadGameObjectCreate2(whereClause);
        }

        if (!showGameObjectUse)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
            SniffDatabase::LoadGameObjectUseTimes(whereClause);
        }

        if (showUpdates)
        {
            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_flags>("flags", whereClause);
            }

            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_state>("state", whereClause);
            }
        }

        if (showCasts)
        {
            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`caster_guid` = %u) && (`caster_type` = 'GameObject') && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadSpellCastStart(whereClause);
            }

            {
                char whereClause[256] = {};
                snprintf(whereClause, 255, "(`caster_guid` != %u) && (`target_guid` = %u) && (`target_type` = 'GameObject') && (`unixtimems` >= (%u * 1000))", guid, guid, uiStartTime);
                SniffDatabase::LoadSpellCastStart(whereClause);
            }

            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`caster_guid` = %u) && (`caster_type` = 'GameObject') && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
                SniffDatabase::LoadSpellCastGo(whereClause);
            }

            {
                char whereClause[256] = {};
                snprintf(whereClause, 255, "(`caster_guid` != %u) && (`main_target_guid` = %u) && (`main_target_type` = 'GameObject') && (`unixtimems` >= (%u * 1000))", guid, guid, uiStartTime);
                SniffDatabase::LoadSpellCastGo(whereClause);
            }
        }

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, uiStartTime);
            SniffDatabase::LoadGameObjectDestroy(whereClause);
        }
    }

    uint32 uiEndTime = !m_eventsMap.empty() ? uint32(m_eventsMap.rbegin()->first / 1000) : UINT32_MAX;

    if (showSounds)
    {
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadPlayMusic(whereClause);
        }

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadPlaySound(whereClause);
        }
    }

    if (showReclaimCorpse)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadClientReclaimCorpse(whereClause);
    }

    if (showReleaseSpirit)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadClientReleaseSpirit(whereClause);
    }

    if (showQuests)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadQuestAcceptTimes(whereClause);
    }

    if (showQuests)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadQuestCompleteTimes(whereClause);
    }

    if (showItemUse)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadItemUseTimes(whereClause);
    }

    if (showCreatureInteract)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureInteractTimes(whereClause);
    }

    if (showGameObjectUse)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadGameObjectUseTimes(whereClause);
    }
}

void TimelineMaker::CreateTimelineForAll(uint32 uiStartTime, uint32 uiEndTime, bool showReclaimCorpse, bool showReleaseSpirit, bool showQuests, bool showUseItem, bool showCreatures, bool showCreatureInteract, bool showCreatureDeaths, bool showCreatureAttacks, bool showCreatureTexts, bool showCreatureEmotes, bool showCreatureMoves, bool showCreatureCasts, bool showCreatureUpdates, bool showGameObjects, bool showGameObjectUse, bool showGameObjectCasts, bool showGameObjectUpdates, bool showSounds)
{
    // Client Actions

    if (showReclaimCorpse)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadClientReclaimCorpse(whereClause);
    }

    if (showReleaseSpirit)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadClientReleaseSpirit(whereClause);
    }

    if (showGameObjectUse)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadGameObjectUseTimes(whereClause);
    }

    if (showCreatureInteract)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureInteractTimes(whereClause);
    }

    if (showUseItem)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadItemUseTimes(whereClause);
    }

    if (showQuests)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadQuestAcceptTimes(whereClause);
    }

    if (showQuests)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadQuestCompleteTimes(whereClause);
    }

    // Creatures

    if (showCreatures)
    {
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureCreate1(whereClause);
        }

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureCreate2(whereClause);
        }

        if (showCreatureAttacks)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureAttackStart(whereClause);
        }

        if (showCreatureAttacks)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureAttackStop(whereClause);
        }

        if (showCreatureTexts)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureText(whereClause);
        }

        if (showCreatureEmotes)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureEmote(whereClause);
        }

        if (showCreatureMoves)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureMovement(whereClause);
        }

        if (showCreatureDeaths)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureDeath(whereClause);
        }

        if (showCreatureCasts)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000)) && (`caster_type`='Creature')", uiStartTime, uiEndTime);
            SniffDatabase::LoadSpellCastStart(whereClause);
        }

        if (showCreatureCasts)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000)) && (`caster_type`='Creature')", uiStartTime, uiEndTime);
            SniffDatabase::LoadSpellCastGo(whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_entry>("entry", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_display_id>("display_id", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_faction>("faction", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_emote_state>("emote_state", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_stand_state>("stand_state", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_npc_flags>("npc_flags", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_unit_flags>("unit_flags", whereClause);
        }

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureDestroy(whereClause);
        }
    }

    // GameObjects

    if (showGameObjects)
    {
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadGameObjectCreate1(whereClause);
        }

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadGameObjectCreate2(whereClause);
        }

        if (showGameObjectCasts)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000)) && (`caster_type`='GameObject')", uiStartTime, uiEndTime);
            SniffDatabase::LoadSpellCastStart(whereClause);
        }

        if (showGameObjectCasts)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000)) && (`caster_type`='GameObject')", uiStartTime, uiEndTime);
            SniffDatabase::LoadSpellCastGo(whereClause);
        }

        if (showGameObjectUpdates)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_flags>("flags", whereClause);
        }

        if (showGameObjectUpdates)
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_state>("state", whereClause);
        }

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
            SniffDatabase::LoadGameObjectDestroy(whereClause);
        }
    }

    // Sounds and Music

    if (showSounds)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadPlayMusic(whereClause);
    }

    if (showSounds)
    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", uiStartTime, uiEndTime);
        SniffDatabase::LoadPlaySound(whereClause);
    }
}

void TimelineMaker::PromptTimelineSaveMethod(uint32 startTime)
{
    printf("Total events: %u\n", TimelineMaker::m_eventsMap.size());
    if (TimelineMaker::m_eventsMap.size())
    {
        printf("Do you want to save timeline to file? (y/n)\n> ");
        if (GetChar() == 'y')
            TimelineMaker::SaveTimelineToFile(startTime);
        printf("Do you want to show timeline on screen? (y/n)\n> ");
        if (GetChar() == 'y')
            TimelineMaker::PrintTimelineToScreen(startTime);
    }
}

void TimelineMaker::PrintTimelineToScreen(uint32 startTime)
{
    uint64 lastEventTime = uint64(startTime) * 1000;
    for (const auto& itr : m_eventsMap)
    {
        uint64 timeDiff = itr.first - lastEventTime;
        printf("\n\n----------------------\n");
        if (timeDiff < 1000)
            printf("%llu MS LATER\n", timeDiff);
        else
            printf("%llu SECONDS LATER\n", timeDiff / 1000);
        printf("----------------------\n\n");
        printf("%s", itr.second->ToString(false).c_str());
        lastEventTime = itr.first;
    }
}

std::string GetTimeString(uint64 eventTime)
{
    time_t eventUnixTime = eventTime / 1000;
    uint32 milliseconds = eventTime % 1000;
    struct tm* ptime = gmtime(&eventUnixTime);
    char buff[13];
    snprintf(buff, sizeof(buff), "%02d:%02d:%02d.%03d", ptime->tm_hour, ptime->tm_min, ptime->tm_sec, milliseconds);
    return std::string(buff);
}

void TimelineMaker::SaveTimelineToFile(uint32 startTime)
{
    std::ofstream log("timeline.txt");
    if (!log.is_open())
        return;

    log << "Total events: " << m_eventsMap.size() << "\n";
    log << "Start time: " << startTime;

    uint64 lastEventTime = startTime;
    for (const auto& itr : m_eventsMap)
    {
        uint64 timeDiff = itr.first - lastEventTime;
        log << "\n\n------------------------------\n";
        if (timeDiff < 1000)
            log << timeDiff << " MS LATER";
        else
            log << (timeDiff / 1000) << " SECONDS LATER";
        log << " (" << GetTimeString(itr.first) << ")\n";
        log << "------------------------------\n\n";
        log << itr.second->ToString(false);
        lastEventTime = itr.first;
    }

    printf("Timeline has been saved to file.\n");

    log.close();
}

struct CreatureSplineData
{
    uint32 spline_point = 0;

    float position_x = 0.0f;
    float position_y = 0.0f;
    float position_z = 0.0f;
};

std::string GetListOfPointsWithSamePosition(float posX, float posY, float posZ, uint32 point)
{
    std::string points;
    for (const auto& itr : TimelineMaker::m_eventsMap)
    {
        if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_mangosWaypoints>(itr.second))
        {
            if (ptr->m_position_x == posX && ptr->m_position_y == posY && ptr->m_position_z == posZ && (ptr->m_point != point - 1))
            {
                if (!points.empty())
                    points += ", ";
                points += std::to_string(ptr->m_point);
            }
        }
    }
    return points;
}

void TimelineMaker::CreateWaypoints(uint32 guid, bool useStartPosition)
{
    std::map<uint32 /*point*/, std::vector<CreatureSplineData>> splinesMap;
    if (!useStartPosition)
    {
        //                                                              0               1               2             3             4
        if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `parent_point`, `spline_point`, `position_x`, `position_y`, `position_z` FROM `%s`.`creature_movement_server_spline` WHERE `guid`=%u", SniffDatabase::m_databaseName.c_str(), guid))
        {
            do
            {
                DbField* pFields = result->fetchCurrentRow();

                CreatureSplineData spline;
                uint32 parent_point = pFields[0].getUInt32();
                spline.spline_point = pFields[1].getUInt32();

                spline.position_x = pFields[2].getFloat();
                spline.position_y = pFields[3].getFloat();
                spline.position_z = pFields[4].getFloat();

                splinesMap[parent_point].push_back(spline);
            } while (result->NextRow());
        }
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u)", guid);
        SniffDatabase::LoadCreatureCreate1(whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u)", guid);
        SniffDatabase::LoadCreatureCreate2(whereClause);
    }

    uint32 firstMoveTime = 0;

    //                                                              0       1        2            3               4               5                   6                   7                   8                 9                 10                11             12
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `guid`, `point`, `move_time`, `spline_flags`, `spline_count`, `start_position_x`, `start_position_y`, `start_position_z`, `end_position_x`, `end_position_y`, `end_position_z`, `orientation`, `unixtime` FROM `%s`.`creature_movement_server` WHERE `guid`=%u", SniffDatabase::m_databaseName.c_str(), guid))
    {
        uint32 pointCounter = 1;
        std::shared_ptr<SniffedEvent_mangosWaypoints> lastPoint = nullptr;
        uint32 lastMoveTime = 0;
        uint32 lastUnixTime = 0;
        float lastOrientation = 100.0f;
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 const id = pFields[0].getUInt32();
            uint32 const point = pFields[1].getUInt32();

            uint32 const move_time = pFields[2].getUInt32();
            //uint32 const spline_flags = pFields[3].getUInt32();
            uint32 const spline_count = pFields[4].getUInt32();

            float const start_position_x = pFields[5].getFloat();
            float const start_position_y = pFields[6].getFloat();
            float const start_position_z = pFields[7].getFloat();

            float const end_position_x = pFields[8].getFloat();
            float const end_position_y = pFields[9].getFloat();
            float const end_position_z = pFields[10].getFloat();
            float const final_orientation = pFields[11].getFloat();

            uint32 unixtime = pFields[12].getUInt32();

            if (point == 1)
                firstMoveTime = unixtime;

            uint32 waittime = 0;

            if (lastPoint)
            {
                float fMoveTime = (float)lastMoveTime;
                fMoveTime = fMoveTime / 1000.0f;
                fMoveTime = ceilf(fMoveTime);
                uint32 roundedUpMoveTime = (uint32)fMoveTime;
                uint32 timeDiff = unixtime - lastUnixTime;

                if (timeDiff > (roundedUpMoveTime * 2))
                {
                    if (useStartPosition)
                        waittime = (timeDiff - roundedUpMoveTime) * 1000;
                    else
                        lastPoint->m_waittime = (timeDiff - roundedUpMoveTime) * 1000;
                }
            }

            if (useStartPosition)
            {
                float orientation = lastOrientation;
                lastOrientation = final_orientation;

                std::string comment = GetListOfPointsWithSamePosition(start_position_x, start_position_y, start_position_z, point);
                if (!comment.empty())
                    comment = "position seen before in points: " + comment;
                std::shared_ptr<SniffedEvent_mangosWaypoints> newEvent = std::make_shared<SniffedEvent_mangosWaypoints>(id, pointCounter, start_position_x, start_position_y, start_position_z, orientation, waittime, 0.0f, 0, comment);
                m_eventsMap.insert(std::make_pair(uint64(unixtime) * 1000, newEvent));

                lastPoint = newEvent;
                pointCounter++;
            }
            else
            {
                if (spline_count > 1)
                {
                    std::vector<CreatureSplineData> const& splines = splinesMap[point];
                    for (uint32 i = 0; i < splines.size(); i++)
                    {
                        CreatureSplineData const& spline = splines[i];
                        uint32 splinesCount = (splines.size() - 1);
                        float orientation = (i == splinesCount) ? final_orientation : 100.0f;
                        std::string comment = "spline " + std::to_string(i) + "/" + std::to_string(splinesCount);
                        std::shared_ptr<SniffedEvent_mangosWaypoints> newEvent = std::make_shared<SniffedEvent_mangosWaypoints>(id, pointCounter, spline.position_x, spline.position_y, spline.position_z, orientation, 0, 0.0f, 0, comment);
                        m_eventsMap.insert(std::make_pair(uint64(unixtime) * 1000, newEvent));

                        lastPoint = newEvent;
                        pointCounter++;
                    }
                }
                else
                {
                    float posX = (spline_count == 0) ? start_position_x : end_position_x;
                    float posY = (spline_count == 0) ? start_position_y : end_position_y;
                    float posZ = (spline_count == 0) ? start_position_z : end_position_z;

                    std::string comment;
                    if (spline_count == 0)
                    {
                        comment = "no splines in this packet";
                    }
                    else
                    {
                        std::string samePointsList = GetListOfPointsWithSamePosition(posX, posY, posZ, point);
                        if (!samePointsList.empty())
                            comment = "position seen before in points: " + samePointsList;
                    }

                    std::shared_ptr<SniffedEvent_mangosWaypoints> newEvent = std::make_shared<SniffedEvent_mangosWaypoints>(id, pointCounter, posX, posY, posZ, final_orientation, 0, 0.0f, 0, comment);
                    m_eventsMap.insert(std::make_pair(uint64(unixtime) * 1000, newEvent));

                    lastPoint = newEvent;
                    pointCounter++;
                }
            }

            lastMoveTime = move_time;
            lastUnixTime = unixtime;
        } while (result->NextRow());
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureInteractTimes(whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureAttackStart(whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureAttackStop(whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureEmote(whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureText(whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_entry>("entry", whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_display_id>("display_id", whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_faction>("faction", whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_emote_state>("emote_state", whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_stand_state>("stand_state", whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_npc_flags>("npc_flags", whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_unit_flags>("unit_flags", whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`caster_guid` = %u) && (`caster_type` = 'Creature') && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadSpellCastStart(whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`caster_guid` = %u) && (`caster_type` = 'Creature') && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadSpellCastGo(whereClause);
    }

    {
        char whereClause[128] = {};
        snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000))", guid, firstMoveTime);
        SniffDatabase::LoadCreatureDestroy(whereClause);
    }
}

uint32 TimelineMaker::SaveWaypointsToFile()
{
    if (m_eventsMap.empty())
        return 0;

    std::time_t result = std::time(nullptr);
    std::stringstream ss;
    ss << result;
    std::string ts = ss.str();
    std::ofstream log("waypoints_" + ts + ".sql");
    if (!log.is_open())
        return 0;

    log << (CURRENT_BUILD >= TBC_START_BUILD ? "INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `waittime`, `script_id`) VALUES\n" : "INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `waittime`, `wander_distance`, `script_id`) VALUES\n");

    uint32 totalWaypointRows = 0;
    for (const auto& itr : m_eventsMap)
    {
        if (itr.second->GetType() == SE_CREATURE_WAYPOINT)
            totalWaypointRows++;
    }

    uint64 lastEventTime = 0;
    uint32 waypointRows = 0;
    for (const auto& itr : m_eventsMap)
    {
        if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_mangosWaypoints>(itr.second))
        {
            log << ptr->ToString(true);
            waypointRows++;
            if (waypointRows < totalWaypointRows)
                log << ",";
            else
                log << ";";
            if (!ptr->m_comment.empty())
                log << " -- " << ptr->m_comment;
            log << "\n";
        }
        else
        {
            if (waypointRows == 0)
                continue;

            uint64 timeDiff = itr.first - lastEventTime;
            log << "-- " << timeDiff / 1000 << " SECONDS LATER: ";
            log << itr.second->ToString(true) << "\n";
        }

        lastEventTime = itr.first;
    }

    log.close();
    return totalWaypointRows;
}

enum QuestEventType
{
    QUEST_NONE,
    QUEST_ACCEPT,
    QUEST_COMPLETE
};

struct QuestEventData
{
    uint32 questId = 0;
    QuestEventType type = QUEST_NONE;
    uint32 startTime = 0;
    uint32 duration = 0;
    uint32 objectGuid = 0;
    std::string objectType;
};

#ifdef min
#undef min
#endif

bool TimelineMaker::FindQuestsWithRpEvents(uint32 const duration)
{
    SniffDatabase::LoadQuestAcceptTimes("(`unixtimems` != 0)");
    SniffDatabase::LoadQuestCompleteTimes("(`unixtimems` != 0)");

    if (m_eventsMap.empty())
        return false;

    std::vector<QuestEventData> questsToCheck;

    QuestEventData lastQuestEvent;
    for (const auto& itr : m_eventsMap)
    {
        if (lastQuestEvent.type != QUEST_NONE)
        {
            lastQuestEvent.duration = uint32(itr.first / 1000) - lastQuestEvent.startTime;
            if (lastQuestEvent.duration = std::min(duration, lastQuestEvent.duration))
                questsToCheck.push_back(lastQuestEvent);
        }
        if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_QuestAccept>(itr.second))
        {
            lastQuestEvent.questId = ptr->m_questId;
            lastQuestEvent.startTime = uint32(itr.first / 1000);
            lastQuestEvent.duration = duration;
            lastQuestEvent.type = QUEST_ACCEPT;
            lastQuestEvent.objectGuid = ptr->m_objectGuid;
            lastQuestEvent.objectType = ptr->m_objectType;
        }
        else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_QuestComplete>(itr.second))
        {
            lastQuestEvent.questId = ptr->m_questId;
            lastQuestEvent.startTime = uint32(itr.first / 1000);
            lastQuestEvent.duration = duration;
            lastQuestEvent.type = QUEST_COMPLETE;
            lastQuestEvent.objectGuid = ptr->m_objectGuid;
            lastQuestEvent.objectType = ptr->m_objectType;
        }
    }
    if (lastQuestEvent.type != QUEST_NONE)
        questsToCheck.push_back(lastQuestEvent);

    ASSERT(!questsToCheck.empty());

    std::map<uint32, std::string> questAcceptEvents;
    std::map<uint32, std::string> questCompleteEvents;

    for (const auto& itr : questsToCheck)
    {
        m_eventsMap.clear();
        uint32 startTime = itr.startTime;
        uint32 endTime = startTime + itr.duration;

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", startTime, endTime);
            SniffDatabase::LoadCreatureCreate2(whereClause);
        }
        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", startTime, endTime);
            SniffDatabase::LoadGameObjectCreate2(whereClause);
        }

        if (itr.objectType == "Creature")
        {
            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadCreatureEmote(whereClause);
            }
            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadCreatureText(whereClause);
            }
            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`id` = %u) && (`unixtime` >= %u) && (`unixtime` <= %u)", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadCreatureMovement(whereClause);
            }
            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_npc_flags>("npc_flags", whereClause);
            }
        }
        else if (itr.objectType == "GameObject")
        {
            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_flags>("flags", whereClause);
            }

            {
                char whereClause[128] = {};
                snprintf(whereClause, 127, "(`guid` = %u) && (`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_state>("state", whereClause);
            }
        }

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`caster_guid` = %u) && (`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", itr.objectGuid, startTime, endTime);
            SniffDatabase::LoadSpellCastStart(whereClause);
        }

        {
            char whereClause[128] = {};
            snprintf(whereClause, 127, "(`caster_guid` = %u) && (`unixtimems` >= (%u * 1000)) && (`unixtimems` <= (%u * 1000))", itr.objectGuid, startTime, endTime);
            SniffDatabase::LoadSpellCastGo(whereClause);
        }

        if (!m_eventsMap.empty())
        {
            std::set<std::string> eventTypes;
            for (const auto& sniffedEvent : m_eventsMap)
            {
                if (sniffedEvent.second->GetType() == SE_CREATURE_CREATE2)
                    eventTypes.insert(std::string("Creature Spawn"));
                else if (sniffedEvent.second->GetType() == SE_GAMEOBJECT_CREATE2)
                    eventTypes.insert(std::string("GameObject Spawn"));
                else if (sniffedEvent.second->GetType() == SE_CREATURE_EMOTE)
                    eventTypes.insert(std::string("Emote"));
                else if (sniffedEvent.second->GetType() == SE_CREATURE_TEXT)
                    eventTypes.insert(std::string("Text"));
                else if (sniffedEvent.second->GetType() == SE_CREATURE_MOVEMENT)
                    eventTypes.insert(std::string("Movement"));
                else if (sniffedEvent.second->GetType() == SE_SPELL_CAST_START ||
                    sniffedEvent.second->GetType() == SE_SPELL_CAST_GO)
                    eventTypes.insert(std::string("Spell Cast"));
                else if (sniffedEvent.second->GetType() == SE_CREATURE_UPDATE_NPC_FLAGS ||
                    sniffedEvent.second->GetType() == SE_GAMEOBJECT_UPDATE_FLAGS ||
                    sniffedEvent.second->GetType() == SE_GAMEOBJECT_UPDATE_STATE)
                    eventTypes.insert(std::string("Values Update"));
            }
            std::string eventTypesList;
            for (const auto& eventType : eventTypes)
            {
                if (!eventTypesList.empty())
                    eventTypesList += ", ";
                eventTypesList += eventType;
            }
            if (itr.type == QUEST_ACCEPT)
                questAcceptEvents.insert(std::make_pair(itr.questId, eventTypesList));
            else if (itr.type == QUEST_COMPLETE)
                questCompleteEvents.insert(std::make_pair(itr.questId, eventTypesList));
        }
    }

    if (!questAcceptEvents.empty())
    {
        printf("Quests with an event on accepting:\n");
        for (auto questId : questAcceptEvents)
        {
            printf("%s (%u) - Events: %s\n", WorldDatabase::GetQuestName(questId.first).c_str(), questId.first, questId.second.c_str());
        }
        printf("\n");
    }
    if (!questCompleteEvents.empty())
    {
        printf("Quests with an event on completion:\n");
        for (auto questId : questCompleteEvents)
        {
            printf("%s (%u) - Events: %s\n", WorldDatabase::GetQuestName(questId.first).c_str(), questId.first, questId.second.c_str());
        }
        printf("\n");
    }

    return !questCompleteEvents.empty() || !questAcceptEvents.empty();
}

#define UNKNOWN_TEXTS_START 200000
#define GENERIC_SCRIPTS_START 300000

void TimelineMaker::CreateScriptFromEvents(uint32 uiStartTime, uint32 uiEndTime)
{
    CreateTimelineForAll(uiStartTime, uiEndTime, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true);
    if (m_eventsMap.empty())
    {
        printf("No events found in time period.\n");
        return;
    }

    std::multimap<uint32, std::pair<std::shared_ptr<SniffedEvent>, std::vector<ScriptInfo>>> scriptEventsMap;

    uint64 lastEventTime = uiStartTime;
    for (const auto& itr : m_eventsMap)
    {
        uint64 timeDiff = itr.first - lastEventTime;
        printf("\n\n----------------------\n");
        if (timeDiff < 1000)
            printf("%llu MS LATER\n", timeDiff);
        else
            printf("%llu SECONDS LATER\n", timeDiff / 1000);
        printf("----------------------\n\n");
        printf("%s", itr.second->ToString(false).c_str());
        lastEventTime = itr.first;

        std::vector<ScriptInfo> vScriptActions;
        GetScriptInfoFromSniffedEvent(itr.first, itr.second, vScriptActions);
        if (vScriptActions.empty())
            printf("\n\nCannot generate script for this event. Press any key.\n> ");
        else
            printf("\n\nDo you want to include this event in the script? (y/n)\n> ");

        if ((GetChar() == 'y') && !vScriptActions.empty())
            scriptEventsMap.insert(std::make_pair(uint32(itr.first / 1000), std::make_pair(itr.second, vScriptActions)));
    }

    m_eventsMap.clear();

    // Make an unique list of objects which are sources of events.
    // We will refer to them as Actors.
    std::vector<KnownObject> actorsList;
    for (const auto& itr : scriptEventsMap)
    {
        KnownObject actor = itr.second.first.get()->GetSourceObject();
        if (std::find(actorsList.begin(), actorsList.end(), actor) == actorsList.end())
            actorsList.push_back(actor);
    }

    printf("List of actors:\n");
    printf("0. None\n");
    for (uint32 i = 0; i < actorsList.size(); i++)
    {
        KnownObject const& actor = actorsList[i];
        printf("%u. %s\n", i + 1, FormatObjectName(actor).c_str());
    }

    printf("Main actor: ");
    uint32 actorId = GetUInt32();
    KnownObject mainActor = actorId ? actorsList[actorId - 1] : KnownObject();

    printf("Main script id: ");
    uint32 mainScriptId = GetUInt32();

    printf("Main table name: ");
    std::string mainTableName = GetString("generic_scripts");

    std::ofstream log("script.sql");
    if (!log.is_open())
        return;

    // Write header comment section.
    if (!m_unknownScriptTexts.empty() || !actorsList.empty())
    {
        log << "/*\n";
        if (!actorsList.empty())
        {
            log << "Objects involved in the script:\n";
            for (uint32 i = 0; i < actorsList.size(); i++)
            {
                KnownObject const& actor = actorsList[i];
                log << i + 1 << ". " << FormatObjectName(actor) << "\n";
            }
            log << "\n";
        }

        if (!m_unknownScriptTexts.empty())
        {
            log << "Texts with placeholder broadcast ids:\n";
            for (uint32 i = 0; i < m_unknownScriptTexts.size(); i++)
            {
                log << UNKNOWN_TEXTS_START + 1 + i << " - " << m_unknownScriptTexts[i] << "\n";
            }
            log << "\n";
        }

        log << "*/\n\n";
    }

    auto SetTargetParamsForScript = [&actorsList](ScriptInfo& script, KnownObject const& target) -> bool
    {
        // Set target by guid if multiple objects with same entry are involved.
        uint32 objectsWithSameEntryCount = 0;
        for (const auto& itr : actorsList)
        {
            if (itr.m_entry == target.m_entry &&
                itr.m_type == target.m_type)
                objectsWithSameEntryCount++;
        }

        if (target.m_type == "Creature")
        {
            if (objectsWithSameEntryCount > 1)
            {
                script.target_type = TARGET_T_CREATURE_WITH_GUID;
                script.target_param1 = target.m_guid;
            }
            else
            {
                script.target_type = TARGET_T_CREATURE_WITH_ENTRY;
                script.target_param1 = target.m_entry;
                script.target_param2 = 30;
            }
            return true;
        }
        else if (target.m_type == "GameObject")
        {
            if (objectsWithSameEntryCount > 1)
            {
                script.target_type = TARGET_T_GAMEOBJECT_WITH_GUID;
                script.target_param1 = target.m_guid;
            }
            else
            {
                script.target_type = TARGET_T_GAMEOBJECT_WITH_ENTRY;
                script.target_param1 = target.m_entry;
                script.target_param2 = 30;
            }
            return true;
        }
        return false;
    };

    std::map<KnownObject, std::pair<uint32, std::vector<ScriptInfo>>> genericScriptsMap;

    // Find which commands need to target another object, yet their source is also different from the main actor.
    // They need to be part of a separate generic script, so add those actors to the map above.
    for (auto& itr : scriptEventsMap)
    {
        KnownObject source = itr.second.first.get()->GetSourceObject();
        KnownObject target = itr.second.first.get()->GetTargetObject();
        if (target.IsEmpty())
            continue;

        for (auto& script : itr.second.second)
        {
            if (source == target)
            {
                script.raw.data[4] = SF_GENERAL_TARGET_SELF;
                if (mainActor != source)
                {
                    if (genericScriptsMap.find(source) == genericScriptsMap.end())
                        genericScriptsMap[source].first = genericScriptsMap.size() + 1;
                }
            }
            else if (SetTargetParamsForScript(script, target))
            {
                if (mainActor != source)
                {
                    if (genericScriptsMap.find(source) == genericScriptsMap.end())
                        genericScriptsMap[source].first = genericScriptsMap.size() + 1;
                }
            }
        }
    }

    std::vector<ScriptInfo> mainScriptVector;

    // Check if any of the commands that require a separate script are by a creature
    // which is summoned in the main script, and assign the script id there in this case.
    std::vector<KnownObject> creaturesSummonedByMainScript;
    for (auto& itr : scriptEventsMap)
    {
        KnownObject source = itr.second.first.get()->GetSourceObject();
        auto genericItr = genericScriptsMap.find(source);
        if (genericItr == genericScriptsMap.end())
            continue;

        for (auto& script : itr.second.second)
        {
            if (script.command == SCRIPT_COMMAND_TEMP_SUMMON_CREATURE)
            {
                creaturesSummonedByMainScript.push_back(genericItr->first);
                script.summonCreature.scriptId = GENERIC_SCRIPTS_START + genericItr->second.first;
                break;
            }
        }
    }
    for (const auto& itr : genericScriptsMap)
    {
        // Its not summoned from the main script, so add a START SCRIPT command.
        if (std::find(creaturesSummonedByMainScript.begin(), creaturesSummonedByMainScript.end(), itr.first) == creaturesSummonedByMainScript.end())
        {
            ScriptInfo script;
            script.id = mainScriptId;
            script.command = SCRIPT_COMMAND_START_SCRIPT;
            script.startScript.scriptId[0] = GENERIC_SCRIPTS_START + itr.second.first;
            script.startScript.chance[0] = 100;
            script.comment = "Start Script for " + EscapeString(GetObjectName(itr.first));

            if (SetTargetParamsForScript(script, itr.first))
                script.raw.data[4] |= SF_GENERAL_SWAP_FINAL_TARGETS;

            mainScriptVector.push_back(script);
        }
    }

    for (auto& itr : scriptEventsMap)
    {
        uint32 timeDiff = itr.first - uiStartTime;
        KnownObject source = itr.second.first.get()->GetSourceObject();

        for (auto& script : itr.second.second)
        {
            // Assign delay for all scripts.
            script.delay = timeDiff;

            // Add source name to the comment.
            if (!source.IsEmpty())
                script.comment = EscapeString(GetObjectName(source) + " - " + script.comment);

            // Assign script id for commands with source present in the map above.
            auto genericItr = genericScriptsMap.find(source);

            if (genericItr != genericScriptsMap.end() &&
                script.command != SCRIPT_COMMAND_TEMP_SUMMON_CREATURE &&
                script.command != SCRIPT_COMMAND_SUMMON_OBJECT)
            {
                script.id = GENERIC_SCRIPTS_START + genericItr->second.first;
                genericItr->second.second.push_back(script);
            }
            // Command does not require separate script id.
            else
            {
                script.id = mainScriptId;

                // Swap targets so that the correct source executes the command.
                if (mainActor != source &&
                    script.command != SCRIPT_COMMAND_TEMP_SUMMON_CREATURE &&
                    script.command != SCRIPT_COMMAND_SUMMON_OBJECT)
                {
                    if (SetTargetParamsForScript(script, source))
                        script.raw.data[4] |= SF_GENERAL_SWAP_FINAL_TARGETS;
                }
                mainScriptVector.push_back(script);
            }
        }
    }

    // Save all the separate scripts first.
    for (const auto& itr : genericScriptsMap)
    {
        // Correct delay for the generic script, if its started from the SUMMON_CREATURE command.
        // The delay for that command needs to be substracted from all actions in the generic script.
        uint32 delayOffset = 0;
        if (std::find(creaturesSummonedByMainScript.begin(), creaturesSummonedByMainScript.end(), itr.first) != creaturesSummonedByMainScript.end())
        {
            for (const auto itr2 : mainScriptVector)
            {
                if (itr2.command == SCRIPT_COMMAND_TEMP_SUMMON_CREATURE)
                {
                    delayOffset = itr2.delay;
                    break;
                }
            }
        }

        log << "-- Script for " << FormatObjectName(itr.first) << "\n";
        SaveScriptToFile(log, GENERIC_SCRIPTS_START + itr.second.first, "generic_scripts", itr.second.second, delayOffset);
    }

    log << "-- Main script.\n";
    SaveScriptToFile(log, mainScriptId, mainTableName, mainScriptVector, 0);

    printf("Script has been saved to file.\n");

    log.close();
}

void TimelineMaker::SaveScriptToFile(std::ofstream& log, uint32 scriptId, std::string tableName, std::vector<ScriptInfo> const& vScripts, uint32 delayOffset)
{
    uint32 count = 0;
    log << "DELETE FROM `" << tableName << "` WHERE `id`=" << scriptId << ";\n";
    log << "INSERT INTO `" << tableName << (CURRENT_BUILD >= TBC_START_BUILD) ? "` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `buddy_entry`, `search_radius`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `condition_id`, `comments`) VALUES\n" : "` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `target_param1`, `target_param2`, `target_type`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `condition_id`, `comments`) VALUES\n";
    for (const auto& script : vScripts)
    {
        if (count > 0)
            log << ",\n";
        log << "(" << script.id << ", " << script.delay - delayOffset << ", " << script.command << ", "
            << script.raw.data[0] << ", " << script.raw.data[1] << ", " << script.raw.data[2] << ", " << (CURRENT_BUILD >= TBC_START_BUILD ? "" : script.raw.data[3] + ", ")
            << script.target_param1 << ", " << script.target_param2 << ", " << (CURRENT_BUILD >= TBC_START_BUILD ? "" : script.target_type + ", ")
            << script.raw.data[4] << ", " << script.raw.data[5] << ", " << script.raw.data[6] << ", " << script.raw.data[7] << ", "
            << script.raw.data[8] << ", " << script.x << ", " << script.y << ", " << script.z << ", " << script.o << ", "
            << script.condition << ", '" << script.comment << "')";

        count++;
    }
    log << ";\n\n";
}

std::vector<std::string> TimelineMaker::m_unknownScriptTexts;

uint32 TimelineMaker::GetTemporaryIdForUnknownBroadcastText(std::string text)
{
    auto itr = std::find(m_unknownScriptTexts.begin(), m_unknownScriptTexts.end(), text);
    if (itr == m_unknownScriptTexts.end())
    {
        m_unknownScriptTexts.push_back(text);
        return UNKNOWN_TEXTS_START + m_unknownScriptTexts.size();
    }

    return UNKNOWN_TEXTS_START + std::distance(m_unknownScriptTexts.begin(), itr);
}

void TimelineMaker::GetScriptInfoFromSniffedEvent(uint64 unixtimems, std::shared_ptr<SniffedEvent> sniffedEvent, std::vector<ScriptInfo>& scriptActions)
{
    if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureCreate2>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_TEMP_SUMMON_CREATURE;
        script.summonCreature.attackTarget = TARGET_T_OWNER_OR_SELF;
        script.summonCreature.despawnType = TEMPSUMMON_TIMED_OR_DEAD_DESPAWN;
        script.summonCreature.despawnDelay = 60000;
        script.summonCreature.creatureEntry = ptr->m_entry;
        script.x = ptr->m_x;
        script.y = ptr->m_y;
        script.z = ptr->m_z;
        script.o = ptr->m_o;
        script.comment = "Summon Creature " + WorldDatabase::GetCreatureName(ptr->m_entry);
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureDestroy>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_DESPAWN_CREATURE;
        script.comment = "Despawn Creature";
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureText>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_TALK;
        uint32 textId = WorldDatabase::GetBroadcastTextId(ptr->m_text);
        if (!textId)
            textId = GetTemporaryIdForUnknownBroadcastText(ptr->m_text);
        script.talk.textId[0] = textId;
        script.comment = "Say Text";
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureEmote>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_EMOTE;
        script.emote.emoteId[0] = ptr->m_emoteId;
        script.comment = "Emote " + ptr->m_emoteName;
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureAttackStart>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_ATTACK_START;
        script.comment = "Attack Start";
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureMovement>(sniffedEvent))
    {
        ScriptInfo script;
        if (ptr->m_endX == 0 && ptr->m_endY == 0 && ptr->m_endX == 0)
        {
            script.command = SCRIPT_COMMAND_TURN_TO;
            script.turnTo.facingLogic = SO_TURNTO_PROVIDED_ORIENTATION;
            script.comment = "Set Orientation";
        }
        else
        {
            script.command = SCRIPT_COMMAND_MOVE_TO;
            script.moveTo.flags = SF_MOVETO_POINT_MOVEGEN;
            script.moveTo.travelTime = ptr->m_moveTime;
            script.x = ptr->m_endX;
            script.y = ptr->m_endY;
            script.z = ptr->m_endZ;
            script.comment = "Move";
        }
        script.o = ptr->m_orientation;
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureUpdate_entry>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_UPDATE_ENTRY;
        script.updateEntry.creatureEntry = ptr->m_value;
        script.comment = "Update Entry to " + WorldDatabase::GetCreatureName(ptr->m_value);
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureUpdate_display_id>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_MORPH_TO_ENTRY_OR_MODEL;
        script.morph.creatureOrModelEntry = ptr->m_value;
        script.morph.isDisplayId = 1;
        script.comment = "Morph to " + std::to_string(ptr->m_value);
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureUpdate_faction>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_SET_FACTION;
        script.faction.factionId = ptr->m_value;
        script.faction.flags = TEMPFACTION_RESTORE_RESPAWN;
        script.comment = "Set Faction to " + WorldDatabase::GetFactionName(ptr->m_value);
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureUpdate_emote_state>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_EMOTE;
        script.emote.emoteId[0] = ptr->m_value;
        script.comment = "Emote State";
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureUpdate_stand_state>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_STAND_STATE;
        script.standState.standState = ptr->m_value;
        script.comment = "Set Stand State";
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureUpdate_npc_flags>(sniffedEvent))
    {
        uint32 oldFlags = SniffDatabase::GetCreatureFieldValueBeforeTime(ptr->m_guid, unixtimems, "npc_flags");
        uint32 removedFlags = 0;
        uint32 addedFlags = 0;
        for (uint32 i = 0; i < 32; i++)
        {
            uint32 flag = (uint32)pow(2, i);
            if ((oldFlags & flag) && !(ptr->m_value & flag))
            {
                removedFlags |= ConvertClassicNpcFlagToVanilla(flag);
            }
            else if (!(oldFlags & flag) && (ptr->m_value & flag))
            {
                addedFlags |= ConvertClassicNpcFlagToVanilla(flag);
            }
        }

        if (addedFlags)
        {
            ScriptInfo script;
            script.command = SCRIPT_COMMAND_MODIFY_FLAGS;
            script.modFlags.fieldId = FIELD_UNIT_NPC_FLAGS;
            script.modFlags.fieldValue = addedFlags;
            script.modFlags.mode = SO_MODIFYFLAGS_SET;
            script.comment = "Add Npc Flags";
            scriptActions.push_back(script);
        }

        if (removedFlags)
        {
            ScriptInfo script;
            script.command = SCRIPT_COMMAND_MODIFY_FLAGS;
            script.modFlags.fieldId = FIELD_UNIT_NPC_FLAGS;
            script.modFlags.fieldValue = removedFlags;
            script.modFlags.mode = SO_MODIFYFLAGS_REMOVE;
            script.comment = "Remove Npc Flags";
            scriptActions.push_back(script);
        }
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_CreatureUpdate_unit_flags>(sniffedEvent))
    {
        uint32 oldFlags = SniffDatabase::GetCreatureFieldValueBeforeTime(ptr->m_guid, unixtimems, "unit_flags");
        uint32 removedFlags = 0;
        uint32 addedFlags = 0;
        for (uint32 i = 0; i < 32; i++)
        {
            uint32 flag = (uint32)pow(2, i);
            if ((oldFlags & flag) && !(ptr->m_value & flag))
            {
                if (IsScriptRelevantUnitFlag(flag))
                    removedFlags |= flag;
            }
            else if (!(oldFlags & flag) && (ptr->m_value & flag))
            {
                if (IsScriptRelevantUnitFlag(flag))
                    addedFlags |= flag;
            }
        }

        if (addedFlags)
        {
            ScriptInfo script;
            script.command = SCRIPT_COMMAND_MODIFY_FLAGS;
            script.modFlags.fieldId = FIELD_UNIT_FIELD_FLAGS;
            script.modFlags.fieldValue = addedFlags;
            script.modFlags.mode = SO_MODIFYFLAGS_SET;
            script.comment = "Add Unit Flags";
            scriptActions.push_back(script);
        }

        if (removedFlags)
        {
            ScriptInfo script;
            script.command = SCRIPT_COMMAND_MODIFY_FLAGS;
            script.modFlags.fieldId = FIELD_UNIT_FIELD_FLAGS;
            script.modFlags.fieldValue = removedFlags;
            script.modFlags.mode = SO_MODIFYFLAGS_REMOVE;
            script.comment = "Remove Unit Flags";
            scriptActions.push_back(script);
        }
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_GameObjectCreate2>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_SUMMON_OBJECT;
        script.summonObject.gameobject_entry = ptr->m_entry;
        script.summonObject.respawn_time = 60000;
        script.x = ptr->m_x;
        script.y = ptr->m_y;
        script.z = ptr->m_z;
        script.o = ptr->m_o;
        script.comment = "Summon GameObject " + WorldDatabase::GetGameObjectName(ptr->m_entry);
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_GameObjectDestroy>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_REMOVE_OBJECT;
        script.raw.data[4] = SF_GENERAL_TARGET_SELF; // this command takes target first
        script.comment = "Despawn GameObject";
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_GameObjectUpdate_state>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_SET_GO_STATE;
        script.setGoState.state = ptr->m_value;
        script.comment = "Set Go State to " + GetGameObjectStateName(ptr->m_value);
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_PlaySound>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_PLAY_SOUND;
        script.playSound.soundId = ptr->m_sound;
        script.comment = "Play Sound " + WorldDatabase::GetSoundName(ptr->m_sound);
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_SpellCastStart>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_CAST_SPELL;
        script.castSpell.spellId = ptr->m_spellId;
        script.comment = "Cast Spell " + WorldDatabase::GetSpellName(ptr->m_spellId);
        scriptActions.push_back(script);
    }
    else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_SpellCastGo>(sniffedEvent))
    {
        ScriptInfo script;
        script.command = SCRIPT_COMMAND_CAST_SPELL;
        script.castSpell.spellId = ptr->m_spellId;
        script.comment = "Cast Spell " + WorldDatabase::GetSpellName(ptr->m_spellId);
        scriptActions.push_back(script);
    }
}
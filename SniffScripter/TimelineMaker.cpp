#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include "Defines\SniffedEvents.h"
#include "Defines\SniffDatabase.h"
#include "Defines\TimelineMaker.h"
#include "Defines\ScriptCommands.h"
#include "Defines\Helpers.h"
#include "Database\Database.h"

extern Database GameDb;
std::multimap<time_t, std::shared_ptr<SniffedEvent>> TimelineMaker::m_eventsMap;

void TimelineMaker::CreateTimelineForGuids(uint32 uiStartTime, std::vector<uint32>& vCreatureGuids, std::vector<uint32> vGameObjectGuids, bool showQuests, bool showGoUse, bool showItemUse, bool showAttacks, bool showTexts, bool showEmotes, bool showMoves, bool showUpdates, bool showCasts, bool showSounds)
{
    for (const auto& guid : vCreatureGuids)
    {
        //uint32 creatureId = SniffDatabase::GetCreatureEntryFromGuid(guid);

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadCreatureCreate1(whereClause);
        }

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadCreatureCreate2(whereClause);
        }

        if (showAttacks)
        {
            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadCreatureAttackStart(whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadCreatureAttackStop(whereClause);
            }
        }

        if (showTexts)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`CreatureGuid` = %u) && (`UnixTime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadCreatureText(whereClause);
        }

        if (showEmotes)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadCreatureEmote(whereClause);
        }

        if (showMoves)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`id` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadCreatureMovement(whereClause);
        }

        if (showUpdates)
        {
            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_entry>("entry", whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_display_id>("display_id", whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_faction>("faction", whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_emote_state>("emote_state", whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_stand_state>("stand_state", whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_npc_flags>("npc_flags", whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_unit_flags>("unit_flags", whereClause);
            }
        }

        if (showCasts)
        {
            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`CasterGuid` = %u) && (`CasterType` = 'Creature') && (`UnixTime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadSpellCastStart(whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`CasterGuid` != %u) && (`TargetGuid` = %u) && (`TargetType` = 'Creature') && (`UnixTime` >= %u)", guid, guid, uiStartTime);
                SniffDatabase::LoadSpellCastStart(whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`CasterGuid` = %u) && (`CasterType` = 'Creature') && (`UnixTime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadSpellCastGo(whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`CasterGuid` != %u) && (`MainTargetGuid` = %u) && (`MainTargetType` = 'Creature') && (`UnixTime` >= %u)", guid, guid, uiStartTime);
                SniffDatabase::LoadSpellCastGo(whereClause);
            }
        }

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadCreatureDestroy(whereClause);
        }
    }

    for (const auto& guid : vGameObjectGuids)
    {
        //uint32 gameObjectId = SniffDatabase::GetGameObjectEntryFromGuid(guid);

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadGameObjectCreate1(whereClause);
        }

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadGameObjectCreate2(whereClause);
        }

        if (!showGoUse)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadGameObjectUseTimes(whereClause);
        }

        if (showUpdates)
        {
            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_flags>("flags", whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_state>("state", whereClause);
            }
        }
        
        if (showCasts)
        {
            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`CasterGuid` = %u) && (`CasterType` = 'GameObject') && (`UnixTime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadSpellCastStart(whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`CasterGuid` != %u) && (`TargetGuid` = %u) && (`TargetType` = 'GameObject') && (`UnixTime` >= %u)", guid, guid, uiStartTime);
                SniffDatabase::LoadSpellCastStart(whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`CasterGuid` = %u) && (`CasterType` = 'GameObject') && (`UnixTime` >= %u)", guid, uiStartTime);
                SniffDatabase::LoadSpellCastGo(whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`CasterGuid` != %u) && (`MainTargetGuid` = %u) && (`MainTargetType` = 'GameObject') && (`UnixTime` >= %u)", guid, guid, uiStartTime);
                SniffDatabase::LoadSpellCastGo(whereClause);
            }
        }

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadGameObjectDestroy(whereClause);
        }
    }

    uint32 uiEndTime = !m_eventsMap.empty() ? m_eventsMap.rbegin()->first : UINT32_MAX;

    if (showSounds)
    {
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadPlayMusic(whereClause);
        }

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadPlaySound(whereClause);
        }
    }

    if (showQuests)
    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadQuestAcceptTimes(whereClause);
    }

    if (showQuests)
    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadQuestCompleteTimes(whereClause);
    }

    if (showItemUse)
    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadItemUseTimes(whereClause);
    }

    if (showGoUse)
    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadGameObjectUseTimes(whereClause);
    }
}

void TimelineMaker::CreateTimelineForAll(uint32 uiStartTime, uint32 uiEndTime, bool showQuests, bool showUseGo, bool showUseItem, bool showCreatures, bool showCreatureAttacks, bool showCreatureTexts, bool showCreatureEmotes, bool showCreatureMoves, bool showCreatureCasts, bool showCreatureUpdates, bool showGameObjects, bool showGameObjectCasts, bool showGameObjectUpdates, bool showSounds)
{
    // Client Actions

    if (showQuests)
    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadQuestAcceptTimes(whereClause);
    }

    if (showQuests)
    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadQuestCompleteTimes(whereClause);
    }

    if (showUseItem)
    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadItemUseTimes(whereClause);
    }

    if (showUseGo)
    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadGameObjectUseTimes(whereClause);
    }

    // Creatures

    if (showCreatures)
    {
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureCreate1(whereClause);
        }

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureCreate2(whereClause);
        }

        if (showCreatureAttacks)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureAttackStart(whereClause);
        }

        if (showCreatureAttacks)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureAttackStop(whereClause);
        }

        if (showCreatureTexts)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`UnixTime` >= %u) && (`UnixTime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureText(whereClause);
        }

        if (showCreatureEmotes)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureEmote(whereClause);
        }

        if (showCreatureMoves)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureMovement(whereClause);
        }

        if (showCreatureCasts)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`UnixTime` >= %u) && (`UnixTime` <= %u) && (`CasterType`='Creature')", uiStartTime, uiEndTime);
            SniffDatabase::LoadSpellCastStart(whereClause);
        }

        if (showCreatureCasts)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`UnixTime` >= %u) && (`UnixTime` <= %u) && (`CasterType`='Creature')", uiStartTime, uiEndTime);
            SniffDatabase::LoadSpellCastGo(whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_entry>("entry", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_display_id>("display_id", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_faction>("faction", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_emote_state>("emote_state", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_stand_state>("stand_state", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_npc_flags>("npc_flags", whereClause);
        }

        if (showCreatureUpdates)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_unit_flags>("unit_flags", whereClause);
        }

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadCreatureDestroy(whereClause);
        }
    }
    

    // GameObjects

    if (showGameObjects)
    {
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadGameObjectCreate1(whereClause);
        }

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadGameObjectCreate2(whereClause);
        }

        if (showGameObjectCasts)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`UnixTime` >= %u) && (`UnixTime` <= %u) && (`CasterType`='GameObject')", uiStartTime, uiEndTime);
            SniffDatabase::LoadSpellCastStart(whereClause);
        }

        if (showGameObjectCasts)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`UnixTime` >= %u) && (`UnixTime` <= %u) && (`CasterType`='GameObject')", uiStartTime, uiEndTime);
            SniffDatabase::LoadSpellCastGo(whereClause);
        }

        if (showGameObjectUpdates)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_flags>("flags", whereClause);
        }

        if (showGameObjectUpdates)
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_state>("state", whereClause);
        }

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
            SniffDatabase::LoadGameObjectDestroy(whereClause);
        }
    }
    
    // Sounds and Music

    if (showSounds)
    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadPlayMusic(whereClause);
    }

    if (showSounds)
    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadPlaySound(whereClause);
    }
}

void TimelineMaker::PromptTimelineSaveMethod(time_t startTime)
{
    printf("Total events: %u\n", TimelineMaker::m_eventsMap.size());
    if (TimelineMaker::m_eventsMap.size())
    {
        printf("Do you want to save timeline to file? (y/n)\n> ");
        if (GetChar() == 'y')
            TimelineMaker::PrintTimelineToFile(startTime);
        printf("Do you want to show timeline on screen? (y/n)\n> ");
        if (GetChar() == 'y')
            TimelineMaker::PrintTimelineToScreen(startTime);
    }
}

void TimelineMaker::PrintTimelineToScreen(time_t startTime)
{
    time_t lastEventTime = startTime;
    for (const auto& itr : m_eventsMap)
    {
        time_t timeDiff = itr.first - lastEventTime;
        printf("\n\n----------------------\n");
        printf("%u SECONDS LATER\n", (uint32)timeDiff);
        printf("----------------------\n\n");
        printf("%s", itr.second->ToString(false).c_str());
        lastEventTime = itr.first;
    }
}

std::string GetTimeString(time_t eventTime)
{
    struct tm* ptime = gmtime(&eventTime);
    char buff[10];
    snprintf(buff, sizeof(buff), "%02d:%02d:%02d", ptime->tm_hour, ptime->tm_min, ptime->tm_sec);
    return std::string(buff);
}

void TimelineMaker::PrintTimelineToFile(time_t startTime)
{
    std::ofstream log("timeline.txt");
    if (!log.is_open())
        return;

    log << "Total events: " << m_eventsMap.size() << "\n";
    log << "Start time: " << startTime;

    time_t lastEventTime = startTime;
    for (const auto& itr : m_eventsMap)
    {
        time_t timeDiff = itr.first - lastEventTime;
        log << "\n\n------------------------------\n";
        log << (uint32)timeDiff << " SECONDS LATER (" + GetTimeString(itr.first) + ")\n";
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
        if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_VmangosWaypoints>(itr.second))
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
        if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `parent_point`, `spline_point`, `position_x`, `position_y`, `position_z` FROM `%s`.`creature_movement_spline` WHERE `guid`=%u", SniffDatabase::m_databaseName.c_str(), guid))
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
        sprintf(whereClause, "(`guid` = %u)", guid);
        SniffDatabase::LoadCreatureCreate1(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`guid` = %u)", guid);
        SniffDatabase::LoadCreatureCreate2(whereClause);
    }

    uint32 firstMoveTime = 0;

    //                                                              0     1        2            3               4               5                   6                   7                   8                 9                 10                11             12
    if (std::shared_ptr<QueryResult> result = GameDb.Query("SELECT `id`, `point`, `move_time`, `spline_flags`, `spline_count`, `start_position_x`, `start_position_y`, `start_position_z`, `end_position_x`, `end_position_y`, `end_position_z`, `orientation`, `unixtime` FROM `%s`.`creature_movement` WHERE `id`=%u", SniffDatabase::m_databaseName.c_str(), guid))
    {
        uint32 pointCounter = 1;
        std::shared_ptr<SniffedEvent_VmangosWaypoints> lastPoint = nullptr;
        uint32 lastMoveTime = 0;
        time_t lastUnixTime = 0;
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

            time_t unixtime = pFields[12].getUInt32();

            if (point == 1)
                firstMoveTime = unixtime;

            uint32 waittime = 0;

            if (lastPoint)
            {
                float fMoveTime = lastMoveTime;
                fMoveTime = fMoveTime / 1000.0f;
                fMoveTime = ceilf(fMoveTime);
                uint32 roundedUpMoveTime = fMoveTime;
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
                std::shared_ptr<SniffedEvent_VmangosWaypoints> newEvent = std::make_shared<SniffedEvent_VmangosWaypoints>(id, pointCounter, start_position_x, start_position_y, start_position_z, orientation, waittime, 0.0f, 0, comment);
                m_eventsMap.insert(std::make_pair(unixtime, newEvent));

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
                        std::shared_ptr<SniffedEvent_VmangosWaypoints> newEvent = std::make_shared<SniffedEvent_VmangosWaypoints>(id, pointCounter, spline.position_x, spline.position_y, spline.position_z, orientation, 0, 0.0f, 0, comment);
                        m_eventsMap.insert(std::make_pair(unixtime, newEvent));

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
                    
                    std::shared_ptr<SniffedEvent_VmangosWaypoints> newEvent = std::make_shared<SniffedEvent_VmangosWaypoints>(id, pointCounter, posX, posY, posZ, final_orientation, 0, 0.0f, 0, comment);
                    m_eventsMap.insert(std::make_pair(unixtime, newEvent));

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
        sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureDestroy(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureAttackStart(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureAttackStop(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureEmote(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`CreatureGuid` = %u) && (`UnixTime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureText(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_entry>("entry", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_display_id>("display_id", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_faction>("faction", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_emote_state>("emote_state", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_stand_state>("stand_state", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_npc_flags>("npc_flags", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_unit_flags>("unit_flags", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`CasterGuid` = %u) && (`CasterType` = 'Creature') && (`UnixTime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadSpellCastStart(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`CasterGuid` = %u) && (`CasterType` = 'Creature') && (`UnixTime` >= %u)", guid, firstMoveTime);
        SniffDatabase::LoadSpellCastGo(whereClause);
    }
}

uint32 TimelineMaker::PrintWaypointsToFile()
{
    if (m_eventsMap.empty())
        return 0;

    std::ofstream log("waypoints.sql");
    if (!log.is_open())
        return 0;

    log << "INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `waittime`, `wander_distance`, `script_id`) VALUES\n";

    uint32 totalWaypointRows = 0;
    for (const auto& itr : m_eventsMap)
    {
        if (itr.second->GetType() == SE_CREATURE_WAYPOINT)
            totalWaypointRows++;
    }

    time_t lastEventTime = 0;
    uint32 waypointRows = 0;
    for (const auto& itr : m_eventsMap)
    {
        if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_VmangosWaypoints>(itr.second))
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

            time_t timeDiff = itr.first - lastEventTime;
            log << "-- " << timeDiff << " SECONDS LATER: " << itr.second->ToString(true) << "\n";
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
    time_t startTime = 0;
    uint32 duration = 0;
    uint32 objectGuid = 0;
    std::string objectType;
};

#ifdef min
#undef min
#endif

bool TimelineMaker::FindQuestsWithRpEvents(uint32 const duration)
{
    SniffDatabase::LoadQuestAcceptTimes("(`unixtime` != 0)");
    SniffDatabase::LoadQuestCompleteTimes("(`unixtime` != 0)");

    if (m_eventsMap.empty())
        return false;

    std::vector<QuestEventData> questsToCheck;

    QuestEventData lastQuestEvent;
    for (const auto& itr : m_eventsMap)
    {
        if (lastQuestEvent.type != QUEST_NONE)
        {
            lastQuestEvent.duration = itr.first - lastQuestEvent.startTime;
            if (lastQuestEvent.duration = std::min(duration, lastQuestEvent.duration))
                questsToCheck.push_back(lastQuestEvent);
        }
        if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_QuestAccept>(itr.second))
        {
            lastQuestEvent.questId = ptr->m_questId;
            lastQuestEvent.startTime = itr.first;
            lastQuestEvent.duration = duration;
            lastQuestEvent.type = QUEST_ACCEPT;
            lastQuestEvent.objectGuid = ptr->m_objectGuid;
            lastQuestEvent.objectType = ptr->m_objectType;
        }
        else if (auto ptr = std::dynamic_pointer_cast<SniffedEvent_QuestComplete>(itr.second))
        {
            lastQuestEvent.questId = ptr->m_questId;
            lastQuestEvent.startTime = itr.first;
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
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", startTime, endTime);
            SniffDatabase::LoadCreatureCreate2(whereClause);
        }
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", startTime, endTime);
            SniffDatabase::LoadGameObjectCreate2(whereClause);
        }

        if (itr.objectType == "Creature")
        {
            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u) && (`unixtime` <= %u)", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadCreatureEmote(whereClause);
            }
            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`CreatureGuid` = %u) && (`UnixTime` >= %u) && (`UnixTime` <= %u)", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadCreatureText(whereClause);
            }
            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`id` = %u) && (`unixtime` >= %u) && (`unixtime` <= %u)", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadCreatureMovement(whereClause);
            }
            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u) && (`unixtime` <= %u)", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_npc_flags>("npc_flags", whereClause);
            }
        }
        else if (itr.objectType == "GameObject")
        {
            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u) && (`unixtime` <= %u)", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_flags>("flags", whereClause);
            }

            {
                char whereClause[128] = {};
                sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u) && (`unixtime` <= %u)", itr.objectGuid, startTime, endTime);
                SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_state>("state", whereClause);
            }
        }
        
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`CasterGuid` = %u) && (`UnixTime` >= %u) && (`UnixTime`<= %u)", itr.objectGuid, startTime, endTime);
            SniffDatabase::LoadSpellCastStart(whereClause);
        }
        
        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`CasterGuid` = %u) && (`UnixTime` >= %u) && (`UnixTime`<= %u)", itr.objectGuid, startTime, endTime);
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
    CreateTimelineForAll(uiStartTime, uiEndTime, true, true, true, true, true, true, true, true, true, true, true, true, true, true);
    if (m_eventsMap.empty())
    {
        printf("No events found in time period.\n");
        return;
    }

    std::multimap<time_t, std::pair<std::shared_ptr<SniffedEvent>, std::vector<ScriptInfo>>> scriptEventsMap;

    time_t lastEventTime = uiStartTime;
    for (const auto& itr : m_eventsMap)
    {
        time_t timeDiff = itr.first - lastEventTime;
        printf("\n\n----------------------\n");
        printf("%u SECONDS LATER\n", (uint32)timeDiff);
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
            scriptEventsMap.insert(std::make_pair(itr.first, std::make_pair(itr.second, vScriptActions)));
    }

    m_eventsMap.clear();

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
    KnownObject mainActor;
    if (actorId)
        mainActor = actorsList[actorId - 1];

    std::ofstream log("script.sql");
    if (!log.is_open())
        return;

    printf("Main script id: ");
    uint32 mainScriptId = GetUInt32();

    printf("Main table name: ");
    std::string mainTableName = GetString("generic_scripts");

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
            log << "The following texts need to have their broadcast id fixed:\n";
            for (uint32 i = 0; i < m_unknownScriptTexts.size(); i++)
            {
                log << UNKNOWN_TEXTS_START + 1 + i << " - " << m_unknownScriptTexts[i] << "\n";
            }
            log << "\n";
        }
        
        log << "*/\n\n";
    }

    std::map<KnownObject, uint32> scriptIdsForObjects;

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
                script.raw.data[4] = SF_GENERAL_TARGET_SELF;
            else if (target.m_type == "Creature")
            {
                script.target_type = TARGET_T_CREATURE_WITH_ENTRY;
                script.target_param1 = target.m_entry;
                script.target_param2 = 30;

                if (mainActor != source)
                {
                    if (scriptIdsForObjects.find(source) == scriptIdsForObjects.end())
                        scriptIdsForObjects[source] = scriptIdsForObjects.size() + 1;
                }
            }
            else if (target.m_type == "GameObject")
            {
                script.target_type = TARGET_T_GAMEOBJECT_WITH_ENTRY;
                script.target_param1 = target.m_entry;
                script.target_param2 = 30;

                if (mainActor != source)
                {
                    if (scriptIdsForObjects.find(source) == scriptIdsForObjects.end())
                        scriptIdsForObjects[source] = scriptIdsForObjects.size() + 1;
                }
            }
        }
    }
    
    for (auto& itr : scriptEventsMap)
    {
        KnownObject source = itr.second.first.get()->GetSourceObject();

        for (auto& script : itr.second.second)
        {
            // Assign script id for commands with source present in the map above.
            auto scriptIdItr = scriptIdsForObjects.find(source);
            if (scriptIdItr != scriptIdsForObjects.end())
            {
                script.id = scriptIdItr->second;
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
                    if (source.m_type == "Creature")
                    {
                        script.target_type = TARGET_T_CREATURE_WITH_ENTRY;
                        script.target_param1 = source.m_entry;
                        script.target_param2 = 30;
                        script.raw.data[4] |= SF_GENERAL_SWAP_FINAL_TARGETS;
                    }
                    else if (source.m_type == "GameObject")
                    {
                        script.target_type = TARGET_T_GAMEOBJECT_WITH_ENTRY;
                        script.target_param1 = source.m_entry;
                        script.target_param2 = 30;
                        script.raw.data[4] |= SF_GENERAL_SWAP_FINAL_TARGETS;
                    }
                }
            }
        }
    }

    // Assign delay for all the scripts.
    for (auto& itr : scriptEventsMap)
    {
        KnownObject source = itr.second.first.get()->GetSourceObject();
        uint32 timeDiff = itr.first - uiStartTime;
        for (auto& script : itr.second.second)
        {
            script.delay = timeDiff;

            if (!source.IsEmpty())
            {
                script.comment = EscapeString(GetObjectName(source) + " - " + script.comment);
            }
        }
    }

    // Save all the separate scripts first.
    for (const auto& genericScriptItr : scriptIdsForObjects)
    {
        uint32 count = 0;
        log << "-- Script for " << FormatObjectName(genericScriptItr.first) << "\n";
        log << "DELETE FROM `generic_scripts` WHERE `id`=" << (GENERIC_SCRIPTS_START + genericScriptItr.second) << ";\n";
        log << "INSERT INTO `generic_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `target_param1`, `target_param2`, `target_type`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `condition_id`, `comments`) VALUES\n";
        for (const auto& itr : scriptEventsMap)
        {
            KnownObject source = itr.second.first.get()->GetSourceObject();
            if (source != genericScriptItr.first)
                continue;

            for (auto& script : itr.second.second)
            {
                // Don't include the spawn in the separate script.
                if (script.command == SCRIPT_COMMAND_TEMP_SUMMON_CREATURE ||
                    script.command == SCRIPT_COMMAND_SUMMON_OBJECT)
                    break;

                if (count > 0)
                    log << ",\n";
                log << "(" << (GENERIC_SCRIPTS_START + script.id) << ", " << script.delay << ", " << script.command << ", "
                    << script.raw.data[0] << ", " << script.raw.data[1] << ", " << script.raw.data[2] << ", " << script.raw.data[3] << ", " 
                    << script.target_param1 << ", " << script.target_param2 << ", " << script.target_type << ", "
                    << script.raw.data[4] << ", " << script.raw.data[5] << ", " << script.raw.data[6] << ", " << script.raw.data[7] << ", " 
                    << script.raw.data[8] << ", "<< script.x << ", " << script.y << ", " << script.z << ", " << script.o << ", "
                    << script.condition << ", '" << script.comment << "')";

                count++;
            }
        }
        log << ";\n\n";
    }

    // Check if any of the commands that require a separate script are by a creature
    // which is summoned in the main script, and assign the script id there in this case.
    for (auto& itr : scriptEventsMap)
    {
        KnownObject source = itr.second.first.get()->GetSourceObject();
        auto scriptIdItr = scriptIdsForObjects.find(source);
        if (scriptIdItr == scriptIdsForObjects.end())
            continue;

        for (auto& script : itr.second.second)
        {
            if (script.command == SCRIPT_COMMAND_TEMP_SUMMON_CREATURE)
            {
                script.summonCreature.scriptId = GENERIC_SCRIPTS_START + scriptIdItr->second;
                scriptIdsForObjects.erase(scriptIdItr);
                break;
            }
        }
    }

    // Now export the main script.
    {
        uint32 count = 0;
        log << "-- Main script.\n";
        log << "DELETE FROM `" << mainTableName << "` WHERE `id`=" << mainScriptId << ";\n";
        log << "INSERT INTO `" << mainTableName << "` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `target_param1`, `target_param2`, `target_type`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `condition_id`, `comments`) VALUES\n";
        // Add START_SCRIPT commands for objects that have separate scripts.
        for (const auto& genericScriptItr : scriptIdsForObjects)
        {
            if (count > 0)
                log << ",\n";

            ScriptInfo script;
            script.id = mainScriptId;
            script.command = SCRIPT_COMMAND_START_SCRIPT;
            script.startScript.scriptId[0] = GENERIC_SCRIPTS_START + genericScriptItr.second;
            script.startScript.chance[0] = 100;
            script.comment = "Start Script for " + EscapeString(GetObjectName(genericScriptItr.first));
            if (genericScriptItr.first.m_type == "Creature")
            {
                script.target_type = TARGET_T_CREATURE_WITH_ENTRY;
                script.target_param1 = genericScriptItr.first.m_entry;
                script.target_param2 = 30;
                script.raw.data[4] |= SF_GENERAL_SWAP_FINAL_TARGETS;
            }
            else if (genericScriptItr.first.m_type == "GameObject")
            {
                script.target_type = TARGET_T_GAMEOBJECT_WITH_ENTRY;
                script.target_param1 = genericScriptItr.first.m_entry;
                script.target_param2 = 30;
                script.raw.data[4] |= SF_GENERAL_SWAP_FINAL_TARGETS;
            }

            log << "(" << script.id << ", " << script.delay << ", " << script.command << ", "
                << script.raw.data[0] << ", " << script.raw.data[1] << ", " << script.raw.data[2] << ", " << script.raw.data[3] << ", "
                << script.target_param1 << ", " << script.target_param2 << ", " << script.target_type << ", "
                << script.raw.data[4] << ", " << script.raw.data[5] << ", " << script.raw.data[6] << ", " << script.raw.data[7] << ", "
                << script.raw.data[8] << ", " << script.x << ", " << script.y << ", " << script.z << ", " << script.o << ", "
                << script.condition << ", '" << script.comment << "')";

            count++;
        }
        // Actually export the main script now.
        for (const auto& itr : scriptEventsMap)
        {
            KnownObject source = itr.second.first.get()->GetSourceObject();
            auto scriptIdItr = scriptIdsForObjects.find(source);

            for (const auto& script : itr.second.second)
            {
                // Skip objects that have a separate script.
                if (scriptIdItr != scriptIdsForObjects.end() &&
                    // Include the spawn command in the main script,
                    // even if this object has its own separate script.
                    script.command != SCRIPT_COMMAND_TEMP_SUMMON_CREATURE &&
                    script.command != SCRIPT_COMMAND_SUMMON_OBJECT)
                    break;

                if (count > 0)
                    log << ",\n";
                log << "(" << script.id << ", " << script.delay << ", " << script.command << ", "
                    << script.raw.data[0] << ", " << script.raw.data[1] << ", " << script.raw.data[2] << ", " << script.raw.data[3] << ", "
                    << script.target_param1 << ", " << script.target_param2 << ", " << script.target_type << ", "
                    << script.raw.data[4] << ", " << script.raw.data[5] << ", " << script.raw.data[6] << ", " << script.raw.data[7] << ", "
                    << script.raw.data[8] << ", " << script.x << ", " << script.y << ", " << script.z << ", " << script.o << ", "
                    << script.condition << ", '" << script.comment << "')";

                count++;
            }
        }
        log << ";\n\n";
    }

    printf("Script has been saved to file.\n");

    log.close();
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

void TimelineMaker::GetScriptInfoFromSniffedEvent(time_t unixtime, std::shared_ptr<SniffedEvent> sniffedEvent, std::vector<ScriptInfo>& scriptActions)
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
        uint32 oldFlags = SniffDatabase::GetCreatureFieldValueBeforeTime(ptr->m_guid, unixtime, "npc_flags");
        uint32 removedFlags = 0;
        uint32 addedFlags = 0;
        for (uint32 i = 0; i < 32; i++)
        {
            uint32 flag = pow(2, i);
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
        uint32 oldFlags = SniffDatabase::GetCreatureFieldValueBeforeTime(ptr->m_guid, unixtime, "unit_flags");
        uint32 removedFlags = 0;
        uint32 addedFlags = 0;
        for (uint32 i = 0; i < 32; i++)
        {
            uint32 flag = pow(2, i);
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

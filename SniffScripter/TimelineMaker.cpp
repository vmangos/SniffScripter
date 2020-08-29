#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include "Defines\SniffedEvents.h"
#include "Defines\SniffDatabase.h"
#include "Defines\TimelineMaker.h"
#include "Database\Database.h"

extern Database GameDb;
std::multimap<time_t, std::shared_ptr<SniffedEvent>> TimelineMaker::m_eventsMap;

void TimelineMaker::CreateTimelineForGuids(uint32 uiStartTime, std::vector<uint32>& vCreatureGuids, std::vector<uint32> vGameObjectGuids, bool showQuests, bool showGoUse, bool showItemUse)
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

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadCreatureDestroy(whereClause);
        }

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadCreatureEmote(whereClause);
        }

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

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`CreatureGuid` = %u) && (`UnixTime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadCreatureText(whereClause);
        }

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`id` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadCreatureMovement(whereClause);
        }

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

        {
            char whereClause[128] = {};
            sprintf(whereClause, "(`guid` = %u) && (`unixtime` >= %u)", guid, uiStartTime);
            SniffDatabase::LoadGameObjectDestroy(whereClause);
        }
    }

    uint32 uiEndTime = !m_eventsMap.empty() ? m_eventsMap.rbegin()->first : UINT32_MAX;

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

void TimelineMaker::CreateTimelineForAll(uint32 uiStartTime, uint32 uiEndTime)
{
    // Client Actions

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadQuestAcceptTimes(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadQuestCompleteTimes(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadItemUseTimes(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadGameObjectUseTimes(whereClause);
    }

    // Creatures

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

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureDestroy(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureEmote(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureAttackStart(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureAttackStop(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`UnixTime` >= %u) && (`UnixTime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureText(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureMovement(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_entry>("entry", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_display_id>("display_id", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_faction>("faction", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_emote_state>("emote_state", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_stand_state>("stand_state", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_npc_flags>("npc_flags", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadCreatureUpdate<SniffedEvent_CreatureUpdate_unit_flags>("unit_flags", whereClause);
    }

    // GameObjects

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

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadGameObjectDestroy(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_flags>("flags", whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`unixtime` >= %u) && (`unixtime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadGameObjectUpdate<SniffedEvent_GameObjectUpdate_state>("state", whereClause);
    }

    // Sounds and Music

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

    // Casts

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`UnixTime` >= %u) && (`UnixTime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadSpellCastStart(whereClause);
    }

    {
        char whereClause[128] = {};
        sprintf(whereClause, "(`UnixTime` >= %u) && (`UnixTime` <= %u)", uiStartTime, uiEndTime);
        SniffDatabase::LoadSpellCastGo(whereClause);
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

    std::set<uint32> questAcceptEvents;
    std::set<uint32> questCompleteEvents;

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
            if (itr.type == QUEST_ACCEPT)
                questAcceptEvents.insert(itr.questId);
            else if (itr.type == QUEST_COMPLETE)
                questCompleteEvents.insert(itr.questId);
        }
    }

    if (!questAcceptEvents.empty())
    {
        printf("Quests with an event on accepting:\n");
        for (auto questId : questAcceptEvents)
        {
            printf("%s (%u)\n", WorldDatabase::GetQuestName(questId).c_str(), questId);
        }
        printf("\n");
    }
    if (!questCompleteEvents.empty())
    {
        printf("Quests with an event on completion:\n");
        for (auto questId : questCompleteEvents)
        {
            printf("%s (%u)\n", WorldDatabase::GetQuestName(questId).c_str(), questId);
        }
        printf("\n");
    }

    return !questCompleteEvents.empty() || !questAcceptEvents.empty();
}
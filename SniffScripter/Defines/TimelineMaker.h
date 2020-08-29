#ifndef _TIMELINE_MAKER_H
#define _TIMELINE_MAKER_H

#include <vector>
#include <map>
#include <memory>
#include "Common.h"
#include "SniffedEvents.h"

class TimelineMaker
{
public:
    static void PrintTimelineToScreen(time_t startTime);
    static void PrintTimelineToFile(time_t startTime);
    static uint32 PrintWaypointsToFile();
    static void CreateTimelineForGuids(uint32 uiStartTime, std::vector<uint32>& vCreatureGuids, std::vector<uint32> vGameObjectGuids, bool showQuests, bool showGoUse, bool showItemUse);
    static void CreateTimelineForAll(uint32 uiStartTime, uint32 uiEndTime);
    static void CreateWaypoints(uint32 guid, bool useStartPosition);
    static bool FindQuestsWithRpEvents(uint32 duration);
    static std::multimap<time_t, std::shared_ptr<SniffedEvent>> m_eventsMap;
};


#endif
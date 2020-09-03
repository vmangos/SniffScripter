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
    static void CreateTimelineForGuids(uint32 uiStartTime, std::vector<uint32>& vCreatureGuids, std::vector<uint32> vGameObjectGuids, bool showQuests, bool showGoUse, bool showItemUse, bool showAttacks, bool showTexts, bool showEmotes, bool showMoves, bool showUpdates, bool showCasts, bool showSounds);
    static void CreateTimelineForAll(uint32 uiStartTime, uint32 uiEndTime, bool showQuests, bool showUseGo, bool showUseItem, bool showCreatures, bool showCreatureAttacks, bool showCreatureTexts, bool showCreatureEmotes, bool showCreatureMoves, bool showCreatureCasts, bool showCreatureUpdates, bool showGameObjects, bool showGameObjectCasts, bool showGameObjectUpdates, bool showSounds);
    static void CreateWaypoints(uint32 guid, bool useStartPosition);
    static bool FindQuestsWithRpEvents(uint32 duration);
    static std::multimap<time_t, std::shared_ptr<SniffedEvent>> m_eventsMap;
};

#endif

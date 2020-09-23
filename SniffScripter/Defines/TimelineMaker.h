#ifndef _TIMELINE_MAKER_H
#define _TIMELINE_MAKER_H

#include <vector>
#include <map>
#include <memory>
#include "Common.h"
#include "SniffedEvents.h"
#include "ScriptCommands.h"

class TimelineMaker
{
public:
    static void PrintTimelineToScreen(uint32 startTime);
    static void SaveTimelineToFile(uint32 startTime);
    static void PromptTimelineSaveMethod(uint32 startTime);
    static void CreateTimelineForGuids(uint32 uiStartTime, std::vector<uint32>& vCreatureGuids, std::vector<uint32> vGameObjectGuids, bool showReclaimCorpse, bool showReleaseSpirit, bool showQuests, bool showCreatureInteract, bool showGameObjectUse, bool showItemUse, bool showAttacks, bool showTexts, bool showEmotes, bool showMoves, bool showUpdates, bool showCasts, bool showSounds);
    static void CreateTimelineForAll(uint32 uiStartTime, uint32 uiEndTime, bool showReclaimCorpse, bool showReleaseSpirit, bool showQuests, bool showUseItem, bool showCreatures, bool showCreatureInteract, bool showCreatureAttacks, bool showCreatureTexts, bool showCreatureEmotes, bool showCreatureMoves, bool showCreatureCasts, bool showCreatureUpdates, bool showGameObjects, bool showGameObjectUse, bool showGameObjectCasts, bool showGameObjectUpdates, bool showSounds);
    
    static uint32 SaveWaypointsToFile();
    static void CreateWaypoints(uint32 guid, bool useStartPosition);

    static bool FindQuestsWithRpEvents(uint32 duration);

    static void CreateScriptFromEvents(uint32 uiStartTime, uint32 uiEndTime);
    static void SaveScriptToFile(std::ofstream& log, uint32 scriptId, std::string tableName, std::vector<ScriptInfo> const& vScripts, uint32 delayOffset);
    static void GetScriptInfoFromSniffedEvent(uint32 unixtime, std::shared_ptr<SniffedEvent> sniffedEvent, std::vector<ScriptInfo>& scriptActions);
    static uint32 GetTemporaryIdForUnknownBroadcastText(std::string text);
    static std::vector<std::string> m_unknownScriptTexts;

    static std::multimap<uint32, std::shared_ptr<SniffedEvent>> m_eventsMap;
};

#endif

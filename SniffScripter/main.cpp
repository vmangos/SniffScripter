// This tool is designed to help with making scripts based on sniff data.
// Author: brotalnia
//

#include <iostream>
#include <string>
#include <vector>

#include "Database\Database.h"
#include "Defines\WorldDatabase.h"
#include "Defines\SniffDatabase.h"
#include "Defines\SniffedEvents.h"
#include "Defines\TimelineMaker.h"
#include "Defines\\Helpers.h"

Database GameDb;

std::string MakeConnectionString()
{
    std::string mysql_host;
    std::string mysql_port;
    std::string mysql_user;
    std::string mysql_pass;
    std::string mysql_db;

    fseek(stdin, 0, SEEK_END);

    printf("Host: ");
    getline(std::cin, mysql_host);
    if (mysql_host.empty())
        mysql_host = "127.0.0.1";

    printf("Port: ");
    getline(std::cin, mysql_port);
    if (mysql_port.empty())
        mysql_port = "3306";

    printf("User: ");
    getline(std::cin, mysql_user);
    if (mysql_user.empty())
        mysql_user = "root";

    printf("Password: ");
    getline(std::cin, mysql_pass);
    if (mysql_pass.empty())
        mysql_pass = "root";

    printf("World db: ");
    getline(std::cin, mysql_db);
    if (mysql_db.empty())
        mysql_db = "mangos";

    fseek(stdin, 0, SEEK_END);

    return mysql_host + ";" + mysql_port + ";" + mysql_user + ";" + mysql_pass + ";" + mysql_db;
}

enum
{
    OPTION_TIMELINE_SPECIFIC_GUIDS          = 1,
    OPTION_TIMELINE_ALL_EVENTS              = 2,
    OPTION_TIMELINE_WAYPOINTS               = 3,
    OPTION_GENERATE_SCRIPT                  = 4,
    OPTION_QUESTS_WITH_RP_EVENTS            = 5,
    OPTION_CALCULATE_ARMOR                  = 6,
    OPTION_SPELL_TIMERS                     = 7,
    OPTION_BREAKDOWN_NPC_FLAGS              = 8,
    OPTION_BREAKDOWN_UNIT_FLAGS             = 9,
    OPTION_BREAKDOWN_MECHANIC_IMMUNE_MASK   = 10,
};

void AskAboutClientEvents(bool& showReclaimCorpse, bool& showReleaseSpirit, bool& showQuests, bool& showCreatureInteract, bool& showGameObjectUse, bool& showUseItem)
{
    printf("Show when client reclaimed his corpse? (y/n)\n> ");
    showReclaimCorpse = GetChar() == 'y';

    printf("Show when client released his spirit? (y/n)\n> ");
    showReleaseSpirit = GetChar() == 'y';

    printf("Show when client accepted or turned in quests? (y/n)\n> ");
    showQuests = GetChar() == 'y';

    printf("Show when client interacted with creatures? (y/n)\n> ");
    showCreatureInteract = GetChar() == 'y';

    printf("Show when client used gameobjects? (y/n)\n> ");
    showGameObjectUse = GetChar() == 'y';

    printf("Show when client used items? (y/n)\n> ");
    showUseItem = GetChar() == 'y';
}

void AskAboutCreatureEvents(bool& showCreatureDeaths, bool& showCreatureAttacks, bool& showCreatureTexts, bool& showCreatureEmotes, bool& showCreatureMoves, bool& showCreatureCasts, bool& showCreatureUpdates)
{
    printf("Show when creatures died? (y/n)\n> ");
    showCreatureDeaths = GetChar() == 'y';

    printf("Show when creatures attacked something? (y/n)\n> ");
    showCreatureAttacks = GetChar() == 'y';

    printf("Show when creatures said something? (y/n)\n> ");
    showCreatureTexts = GetChar() == 'y';

    printf("Show when creatures played an emote? (y/n)\n> ");
    showCreatureEmotes = GetChar() == 'y';

    printf("Show when creatures moved? (y/n)\n> ");
    showCreatureMoves = GetChar() == 'y';

    printf("Show when creatures casted spells? (y/n)\n> ");
    showCreatureCasts = GetChar() == 'y';

    printf("Show changes to creature update fields? (y/n)\n> ");
    showCreatureUpdates = GetChar() == 'y';
}

void AskAboutGameObjectEvents(bool& showGameObjectCustomAnims, bool& showGameObjectCasts, bool& showGameObjectUpdates)
{
    printf("Show when gameobjects played a custom animation? (y/n)\n> ");
    showGameObjectCustomAnims = GetChar() == 'y';

    printf("Show when gameobjects casted spells? (y/n)\n> ");
    showGameObjectCasts = GetChar() == 'y';

    printf("Show changes to gameobject update fields? (y/n)\n> ");
    showGameObjectUpdates = GetChar() == 'y';
}

int main()
{
    printf("Options:\n");
    printf("1. Create timeline for specific guids\n");
    printf("2. Create timeline for all in time period\n");
    printf("3. Create waypoints and show events as comments\n");
    printf("4. Create database script from selected events\n");
    printf("5. List quests with RP events\n");
    printf("6. Calculate creature armor\n");
    printf("7. Calculate spell timers\n");
    printf("8. Breakdown NPC Flags\n");
    printf("9. Breakdown Unit Flags\n");
    printf("10. Breakdown Mechanic Immune Mask\n");
    printf("> ");

    uint32 option = GetUInt32();

    if (option == OPTION_TIMELINE_SPECIFIC_GUIDS ||
        option == OPTION_TIMELINE_ALL_EVENTS ||
        option == OPTION_TIMELINE_WAYPOINTS ||
        option == OPTION_QUESTS_WITH_RP_EVENTS ||
        option == OPTION_GENERATE_SCRIPT ||
        option == OPTION_CALCULATE_ARMOR ||
        option == OPTION_SPELL_TIMERS)
    {
        printf("\nEnter your database connection info.\n");
        std::string const connection_string = MakeConnectionString();

        printf("\nConnecting to database.\n");
        if (!GameDb.Initialize(connection_string.c_str()))
        {
            printf("\nError: Cannot connect to world database!\n");
            GetChar();
            return 1;
        }

        WorldDatabase::LoadWorldDatabase();
        printf("\n");

        printf("Enter sniff database name: ");
        SniffDatabase::m_databaseName = GetString("sniffs_new_test");
        SniffDatabase::LoadSniffDatabase();
        printf("\n");

        if (option == OPTION_TIMELINE_SPECIFIC_GUIDS)
        {
            std::vector<uint32> vCreatureGuids;
            std::vector<uint32> vGameObjectGuids;

            printf("Do you want to enter a creature guid? (y/n)\n> ");
            while (GetChar() == 'y')
            {
                printf("Guid: ");
                if (uint32 id = GetUInt32())
                    vCreatureGuids.push_back(id);
                printf("Do you want to enter another creature guid? (y/n)\n> ");
            }

            printf("Do you want to enter a gameobject guid? (y/n)\n> ");
            while (GetChar() == 'y')
            {
                printf("Guid: ");
                if (uint32 id = GetUInt32())
                    vGameObjectGuids.push_back(id);
                printf("Do you want to enter another gameobject guid? (y/n)\n> ");
            }

            if (vCreatureGuids.empty() && vGameObjectGuids.empty())
            {
                printf("You didn't enter any guids to watch!\n");
                GetChar();
                return 1;
            }

            bool showReclaimCorpse = false;
            bool showReleaseSpirit = false;
            bool showQuests = false;
            bool showCreatureInteract = false;
            bool showGameObjectUse = false;
            bool showUseItem = false;
            printf("Show client related events (y/n)\n> ");
            if (GetChar() == 'y')
                AskAboutClientEvents(showReclaimCorpse, showReleaseSpirit, showQuests, showCreatureInteract, showGameObjectUse, showUseItem);

            bool showCreatureDeaths = false;
            bool showCreatureAttacks = false;
            bool showCreatureTexts = false;
            bool showCreatureEmotes = false;
            bool showCreatureMoves = false;
            bool showCreatureCasts = false;
            bool showCreatureUpdates = false;
            printf("Show creature related events? (y/n)\n> ");
            if (GetChar() == 'y')
                AskAboutCreatureEvents(showCreatureDeaths, showCreatureAttacks, showCreatureTexts, showCreatureEmotes, showCreatureMoves, showCreatureCasts, showCreatureUpdates);

            bool showGameObjectCustomAnims = false;
            bool showGameObjectCasts = false;
            bool showGameObjectUpdates = false;
            printf("Show gameobject related events? (y/n)\n> ");
            if (GetChar() == 'y')
                AskAboutGameObjectEvents(showGameObjectCustomAnims, showGameObjectCasts, showGameObjectUpdates);

            printf("Show when sounds or music played? (y/n)\n> ");
            bool showSounds = GetChar() == 'y';

            printf("Start time: ");
            uint32 uiStartTime = GetUInt32();

            TimelineMaker::CreateTimelineForGuids(uiStartTime, vCreatureGuids, vGameObjectGuids, showReclaimCorpse, showReleaseSpirit, showQuests, showCreatureInteract, showGameObjectUse, showUseItem, showCreatureDeaths, showCreatureAttacks, showCreatureTexts, showCreatureEmotes, showCreatureMoves, showCreatureUpdates, showCreatureCasts, showGameObjectCustomAnims, showGameObjectUpdates, showGameObjectCasts, showSounds);
            TimelineMaker::PromptTimelineSaveMethod(uiStartTime);
            return 0;
        }
        else if (option == OPTION_TIMELINE_ALL_EVENTS)
        {
            bool showReclaimCorpse = false;
            bool showReleaseSpirit = false;
            bool showQuests = false;
            bool showCreatureInteract = false;
            bool showGameObjectUse = false;
            bool showUseItem = false;
            printf("Show client related events (y/n)\n> ");
            if (GetChar() == 'y')
                AskAboutClientEvents(showReclaimCorpse, showReleaseSpirit, showQuests, showCreatureInteract, showGameObjectUse, showUseItem);

            printf("Show creature related events? (y/n)\n> ");
            bool showCreatures = GetChar() == 'y';
            bool showCreatureDeaths = false;
            bool showCreatureAttacks = false;
            bool showCreatureTexts = false;
            bool showCreatureEmotes = false;
            bool showCreatureMoves = false;
            bool showCreatureCasts = false;
            bool showCreatureUpdates = false;
            if (showCreatures)
                AskAboutCreatureEvents(showCreatureDeaths, showCreatureAttacks, showCreatureTexts, showCreatureEmotes, showCreatureMoves, showCreatureCasts, showCreatureUpdates);

            printf("Show gameobject related events? (y/n)\n> ");
            bool showGameObjects = GetChar() == 'y';
            bool showGameObjectCustomAnims = false;
            bool showGameObjectCasts = false;
            bool showGameObjectUpdates = false;
            if (showGameObjects)
                AskAboutGameObjectEvents(showGameObjectCustomAnims, showGameObjectCasts, showGameObjectUpdates);

            printf("Show when sounds or music played? (y/n)\n> ");
            bool showSounds = GetChar() == 'y';

            printf("Start time: ");
            uint32 uiStartTime = GetUInt32();

            printf("Duration: ");
            uint32 uiEndTime = GetUInt32();
            if (uiEndTime != 0)
                uiEndTime = uiStartTime + uiEndTime;
            else
                uiEndTime = UINT32_MAX;

            TimelineMaker::CreateTimelineForAll(uiStartTime, uiEndTime, showReclaimCorpse, showReleaseSpirit, showQuests, showUseItem, showCreatures, showCreatureInteract, showCreatureDeaths, showCreatureAttacks, showCreatureTexts, showCreatureEmotes, showCreatureMoves, showCreatureCasts, showCreatureUpdates, showGameObjects, showGameObjectUse, showGameObjectCustomAnims, showGameObjectCasts, showGameObjectUpdates, showSounds);
            TimelineMaker::PromptTimelineSaveMethod(uiStartTime);
            return 0;
        }
        else if (option == OPTION_TIMELINE_WAYPOINTS)
        {
            printf("Guid: ");
            if (uint32 guid = GetUInt32())
            {
                printf("Use start position instead of destination? (y/n)\n> ");
                bool useStartPosition = GetChar() == 'y';

                std::vector<uint32> vCreatureGuids;
                std::vector<uint32> vGameObjectGuids;

                printf("Do you want to also show events for another creature guid? (y/n)\n> ");
                while (GetChar() == 'y')
                {
                    printf("Guid: ");
                    if (uint32 id = GetUInt32())
                        vCreatureGuids.push_back(id);
                    printf("Do you want to enter another creature guid? (y/n)\n> ");
                }

                printf("Do you want to also show events for another gameobject guid? (y/n)\n> ");
                while (GetChar() == 'y')
                {
                    printf("Guid: ");
                    if (uint32 id = GetUInt32())
                        vGameObjectGuids.push_back(id);
                    printf("Do you want to enter another gameobject guid? (y/n)\n> ");
                }

                bool showReclaimCorpse = false;
                bool showReleaseSpirit = false;
                bool showQuests = false;
                bool showCreatureInteract = false;
                bool showGameObjectUse = false;
                bool showUseItem = false;
                printf("Show client related events (y/n)\n> ");
                if (GetChar() == 'y')
                    AskAboutClientEvents(showReclaimCorpse, showReleaseSpirit, showQuests, showCreatureInteract, showGameObjectUse, showUseItem);

                bool showCreatureDeaths = false;
                bool showCreatureAttacks = false;
                bool showCreatureTexts = false;
                bool showCreatureEmotes = false;
                bool showCreatureMoves = false;
                bool showCreatureCasts = false;
                bool showCreatureUpdates = false;
                if (!vCreatureGuids.empty())
                    AskAboutCreatureEvents(showCreatureDeaths, showCreatureAttacks, showCreatureTexts, showCreatureEmotes, showCreatureMoves, showCreatureCasts, showCreatureUpdates);

                bool showGameObjectCustomAnims = false;
                bool showGameObjectCasts = false;
                bool showGameObjectUpdates = false;
                if (!vGameObjectGuids.empty())
                    AskAboutGameObjectEvents(showGameObjectCustomAnims, showGameObjectCasts, showGameObjectUpdates);

                printf("Show when sounds or music played? (y/n)\n> ");
                bool showSounds = GetChar() == 'y';

                TimelineMaker::CreateTimelineForGuids(0, vCreatureGuids, vGameObjectGuids, showReclaimCorpse, showReleaseSpirit, showQuests, showCreatureInteract, showGameObjectUse, showUseItem, showCreatureDeaths, showCreatureAttacks, showCreatureTexts, showCreatureEmotes, showCreatureMoves, showCreatureUpdates, showCreatureCasts, showGameObjectCustomAnims, showGameObjectUpdates, showGameObjectCasts, showSounds);
                TimelineMaker::CreateWaypoints(guid, useStartPosition, showCreatureInteract);
                if (uint32 count = TimelineMaker::SaveWaypointsToFile())
                {
                    printf("Saved %u points to file.", count);
                    GetChar();
                    return 0;
                }
                else
                {
                    printf("No waypoints found for npc!");
                    GetChar();
                    return 1;
                }
            }
        }
        else if (option == OPTION_GENERATE_SCRIPT)
        {
            printf("Start time: ");
            uint32 uiStartTime = GetUInt32();

            printf("Duration: ");
            uint32 uiEndTime = GetUInt32();
            if (uiEndTime != 0)
                uiEndTime = uiStartTime + uiEndTime;
            else
                uiEndTime = UINT32_MAX;

            TimelineMaker::CreateScriptFromEvents(uiStartTime, uiEndTime);
            GetChar();
            return 0;
        }
        else if (option == OPTION_QUESTS_WITH_RP_EVENTS)
        {
            printf("Time limit: ");
            if (uint32 duration = GetUInt32())
            {
                printf("Searching for quests with an event on accept or completion...\n");
                if (!TimelineMaker::FindQuestsWithRpEvents(duration))
                    printf("No quests with scripted events found.\n");
                GetChar();
                return 0;
            }
        }
        else if (option == OPTION_CALCULATE_ARMOR)
        {
            printf("Creature Id: ");
            if (uint32 entry = GetUInt32())
            {
                TimelineMaker::CalculateCreatureArmor(entry);
                printf("End of melee attack log data.");
                return 0;
            }
        }
        else if (option == OPTION_SPELL_TIMERS)
        {
            printf("Creature Id: ");
            if (uint32 entry = GetUInt32())
            {
                TimelineMaker::CalculateCreatureSpellTimers(entry);
                return 0;
            }
        }
    }
    else if (option == OPTION_BREAKDOWN_NPC_FLAGS)
    {
        bool repeat = true;
        while (repeat)
        {
            printf("NPC Flags: ");
            uint32 flags = GetUInt32();
            std::string flagNames = GetNpcFlagNames(flags);
            printf(flagNames.c_str());
            printf("\nAgain? (y/n)\n>");
            repeat = GetChar() == 'y';
        }
    }
    else if (option == OPTION_BREAKDOWN_UNIT_FLAGS)
    {
        bool repeat = true;
        while (repeat)
        {
            printf("Unit Flags: ");
            uint32 flags = GetUInt32();
            std::string flagNames = GetUnitFlagNames(flags);
            printf(flagNames.c_str());
            printf("\nAgain? (y/n)\n>");
            repeat = GetChar() == 'y';
        }
    }
    else if (option == OPTION_BREAKDOWN_MECHANIC_IMMUNE_MASK)
    {
        bool repeat = true;
        while (repeat)
        {
            printf("Mechanic Immune Mask: ");
            uint32 mask = GetUInt32();
            std::string flagNames = GetMechanicImmuneMaskNames(mask);
            printf(flagNames.c_str());
            printf("\nAgain? (y/n)\n>");
            repeat = GetChar() == 'y';
        }
    }

    GetChar();
    GameDb.Uninitialise();
    return 0;
}


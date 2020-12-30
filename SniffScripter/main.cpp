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
std::string mysql_host_default = "localhost";
std::string mysql_port_default = "3306";
std::string mysql_user_default = "root";
std::string mysql_pass_default = "password";
std::string mysql_world_db_default = "voamangos";
std::string mysql_sniff_db_default = "nost2";

std::string MakeConnectionString()
{
    std::string mysql_host;
    std::string mysql_port;
    std::string mysql_user;
    std::string mysql_pass;
    std::string mysql_db;

    fseek(stdin, 0, SEEK_END);

    printf("Host (or press Enter to use all defaults): ");
    getline(std::cin, mysql_host);
    if (mysql_host.empty())
    {
        mysql_host = mysql_host_default;
        mysql_port = mysql_port_default;
        mysql_user = mysql_user_default;
        mysql_pass = mysql_pass_default;
        mysql_db = mysql_world_db_default;
        return mysql_host + ";" + mysql_port + ";" + mysql_user + ";" + mysql_pass + ";" + mysql_db;
    }

    printf("Port: ");
    getline(std::cin, mysql_port);
    if (mysql_port.empty())
        mysql_port = mysql_port_default;

    printf("User: ");
    getline(std::cin, mysql_user);
    if (mysql_user.empty())
        mysql_user = mysql_user_default;

    printf("Password: ");
    getline(std::cin, mysql_pass);
    if (mysql_pass.empty())
        mysql_pass = mysql_pass_default;

    printf("World db: ");
    getline(std::cin, mysql_db);
    if (mysql_db.empty())
        mysql_db = mysql_world_db_default;

    fseek(stdin, 0, SEEK_END);

    return mysql_host + ";" + mysql_port + ";" + mysql_user + ";" + mysql_pass + ";" + mysql_db;
}

enum
{
    OPTION_TIMELINE_SPECIFIC_GUIDS  = 1,
    OPTION_TIMELINE_ALL_EVENTS      = 2,
    OPTION_TIMELINE_WAYPOINTS       = 3,
    OPTION_GENERATE_SCRIPT          = 4,
    OPTION_QUESTS_WITH_RP_EVENTS    = 5,
    OPTION_BREAKDOWN_NPC_FLAGS      = 6,
    OPTION_BREAKDOWN_UNIT_FLAGS     = 7,
    OPTION_QUIT                     = 8,
};

int runOnce(uint32 option)
{
    if (option == OPTION_TIMELINE_SPECIFIC_GUIDS ||
        option == OPTION_TIMELINE_ALL_EVENTS ||
        option == OPTION_TIMELINE_WAYPOINTS ||
        option == OPTION_QUESTS_WITH_RP_EVENTS ||
        option == OPTION_GENERATE_SCRIPT)
    {
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

            printf("Show when client reclaimed his corpse? (y/n)\n> ");
            bool showReclaimCorpse = GetChar() == 'y';

            printf("Show when client released his spirit? (y/n)\n> ");
            bool showReleaseSpirit = GetChar() == 'y';

            printf("Show when client accepted or turned in quests? (y/n)\n> ");
            bool showQuests = GetChar() == 'y';

            printf("Show when client interacted with creatures? (y/n)\n> ");
            bool showCreatureInteract = GetChar() == 'y';

            printf("Show when client used gameobjects? (y/n)\n> ");
            bool showGameObjectUse = GetChar() == 'y';

            printf("Show when client used items? (y/n)\n> ");
            bool showUseItem = GetChar() == 'y';

            printf("Show when creatures died? (y/n)\n> ");
            bool showDeaths = GetChar() == 'y';

            printf("Show when creatures attacked something? (y/n)\n> ");
            bool showAttacks = GetChar() == 'y';

            printf("Show when creatures said something? (y/n)\n> ");
            bool showTexts = GetChar() == 'y';

            printf("Show when creatures played an emote? (y/n)\n> ");
            bool showEmotes = GetChar() == 'y';

            printf("Show when creatures moved? (y/n)\n> ");
            bool showMoves = GetChar() == 'y';

            printf("Show spell casts? (y/n)\n> ");
            bool showCasts = GetChar() == 'y';

            printf("Show changes to update fields? (y/n)\n> ");
            bool showUpdates = GetChar() == 'y';

            printf("Show when sounds or music played? (y/n)\n> ");
            bool showSounds = GetChar() == 'y';

            printf("Start time: ");
            uint32 uiStartTime = GetUInt32();

            TimelineMaker::CreateTimelineForGuids(uiStartTime, vCreatureGuids, vGameObjectGuids, showReclaimCorpse, showReleaseSpirit, showQuests, showCreatureInteract, showGameObjectUse, showUseItem, showDeaths, showAttacks, showTexts, showEmotes, showMoves, showUpdates, showCasts, showSounds);
            TimelineMaker::PromptTimelineSaveMethod(uiStartTime);
            return 0;
        }
        else if (option == OPTION_TIMELINE_ALL_EVENTS)
        {
            printf("Show when client reclaimed his corpse? (y/n)\n> ");
            bool showReclaimCorpse = GetChar() == 'y';

            printf("Show when client released his spirit? (y/n)\n> ");
            bool showReleaseSpirit = GetChar() == 'y';

            printf("Show when client accepted or turned in quests? (y/n)\n> ");
            bool showQuests = GetChar() == 'y';

            printf("Show when client used items? (y/n)\n> ");
            bool showUseItem = GetChar() == 'y';

            printf("Show creature related events? (y/n)\n> ");
            bool showCreatures = GetChar() == 'y';
            bool showCreatureInteract = false;
            bool showCreatureDeaths = false;
            bool showCreatureAttacks = false;
            bool showCreatureTexts = false;
            bool showCreatureEmotes = false;
            bool showCreatureMoves = false;
            bool showCreatureCasts = false;
            bool showCreatureUpdates = false;
            if (showCreatures)
            {
                printf("Show when client interacted with creatures? (y/n)\n> ");
                showCreatureInteract = GetChar() == 'y';

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

            printf("Show gameobject related events? (y/n)\n> ");
            bool showGameObjects = GetChar() == 'y';
            bool showGameObjectUse = false;
            bool showGameObjectCasts = false;
            bool showGameObjectUpdates = false;
            if (showGameObjects)
            {
                printf("Show when client used gameobjects? (y/n)\n> ");
                showGameObjectUse = GetChar() == 'y';

                printf("Show when gameobjects casted spells? (y/n)\n> ");
                showGameObjectCasts = GetChar() == 'y';

                printf("Show changes to gameobject update fields? (y/n)\n> ");
                showGameObjectUpdates = GetChar() == 'y';
            }

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

            TimelineMaker::CreateTimelineForAll(uiStartTime, uiEndTime, showReclaimCorpse, showReleaseSpirit, showQuests, showUseItem, showCreatures, showCreatureInteract, showCreatureDeaths, showCreatureAttacks, showCreatureTexts, showCreatureEmotes, showCreatureMoves, showCreatureCasts, showCreatureUpdates, showGameObjects, showGameObjectUse, showGameObjectCasts, showGameObjectUpdates, showSounds);
            TimelineMaker::PromptTimelineSaveMethod(uiStartTime);
            return 0;
        }
        else if (option == OPTION_TIMELINE_WAYPOINTS)
        {
            printf("Guid: ");
            if (uint32 guid = GetUInt32())
            {
                printf("Use start position instead of destination? (y/n)\n> ");
                TimelineMaker::CreateWaypoints(guid, GetChar() == 'y');
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
    return 0;
}

int main()
{
    printf("Enter your database connection info.\n");
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
    printf("Enter sniff database name (or press Enter to use default): ");
    SniffDatabase::m_databaseName = GetString(mysql_sniff_db_default);
    SniffDatabase::LoadSniffDatabase();
    printf("\n");

    uint32 option = OPTION_TIMELINE_WAYPOINTS;
    while (option != OPTION_QUIT)
    {
        printf("Options:\n");
        printf("1. Create timeline for specific guids\n");
        printf("2. Create timeline for all in time period\n");
        printf("3. Create waypoints and show events as comments\n");
        printf("4. Create database script from selected events\n");
        printf("5. List quests with RP events\n");
        printf("6. Breakdown NPC Flags\n");
        printf("7. Breakdown Unit Flags\n");
        printf("8. Exit\n");
        printf("> ");
        option = GetUInt32();
        runOnce(option);
    }

    GameDb.Uninitialise();
    printf("Exited - press any key to close window.");
    GetChar();
    return 0;
}
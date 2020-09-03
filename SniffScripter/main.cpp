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

Database GameDb;

std::string MakeConnectionString()
{
    std::string mysql_host;
    std::string mysql_port;
    std::string mysql_user;
    std::string mysql_pass;
    std::string mysql_db;

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

    return mysql_host + ";" + mysql_port + ";" + mysql_user + ";" + mysql_pass + ";" + mysql_db;
}

char GetChar()
{
    fseek(stdin, 0, SEEK_END);
    char const chr = getchar();
    fseek(stdin, 0, SEEK_END);
    return chr;
}

enum
{
    OPTION_TIMELINE_SPECIFIC_GUIDS  = 1,
    OPTION_TIMELINE_ALL_EVENTS      = 2,
    OPTION_TIMELINE_WAYPOINTS       = 3,
    OPTION_QUESTS_WITH_RP_EVENTS    = 4,
};

int main()
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

    printf("Options:\n");
    printf("1. Create timeline for specific guids\n");
    printf("2. Create timeline for all in time period\n");
    printf("3. Create waypoints and show events as comments\n");
    printf("4. List quests with RP events\n");
    printf("> ");

    uint32 option = 0;
    scanf("%u", &option);
    fseek(stdin, 0, SEEK_END);

    time_t startTime = 0;

    if (option == OPTION_TIMELINE_SPECIFIC_GUIDS || option == OPTION_TIMELINE_ALL_EVENTS || option == OPTION_TIMELINE_WAYPOINTS || option == OPTION_QUESTS_WITH_RP_EVENTS)
    {
        
        printf("Enter sniff database name: ");
        getline(std::cin, SniffDatabase::m_databaseName);
        if (SniffDatabase::m_databaseName.empty())
            SniffDatabase::m_databaseName = "sniffs_new_test";
        fseek(stdin, 0, SEEK_END);

        SniffDatabase::LoadSniffDatabase();

        if (option == OPTION_TIMELINE_SPECIFIC_GUIDS)
        {
            std::vector<uint32> vCreatureGuids;
            std::vector<uint32> vGameObjectGuids;

            printf("Do you want to enter a creature guid? (y/n)\n> ");
            while (GetChar() == 'y')
            {
                printf("Guid: ");
                uint32 id = 0;
                if (scanf("%u", &id) == 1)
                    vCreatureGuids.push_back(id);
                printf("Do you want to enter another creature guid? (y/n)\n> ");
            }

            printf("Do you want to enter a gameobject guid? (y/n)\n> ");
            while (GetChar() == 'y')
            {
                printf("Guid: ");
                uint32 id = 0;
                if (scanf("%u", &id) == 1)
                    vGameObjectGuids.push_back(id);
                printf("Do you want to enter another gameobject guid? (y/n)\n> ");
            }

            if (vCreatureGuids.empty() && vGameObjectGuids.empty())
            {
                printf("You didn't enter any guids to watch!\n");
                GetChar();
                return 1;
            }

            printf("Show when client accepted or turned in quests? (y/n)\n> ");
            bool showQuests = GetChar() == 'y';

            printf("Show when client used gameobjects? (y/n)\n> ");
            bool showUseGo = GetChar() == 'y';

            printf("Show when client used items? (y/n)\n> ");
            bool showUseItem = GetChar() == 'y';

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
            
            uint32 uiStartTime = 0;
            printf("Start time: ");
            scanf("%u", &uiStartTime);
            startTime = uiStartTime;

            TimelineMaker::CreateTimelineForGuids(uiStartTime, vCreatureGuids, vGameObjectGuids, showQuests, showUseGo, showUseItem, showAttacks, showTexts, showEmotes, showMoves, showUpdates, showCasts, showSounds);
        }
        else if (option == OPTION_TIMELINE_ALL_EVENTS)
        {
            printf("Show when client accepted or turned in quests? (y/n)\n> ");
            bool showQuests = GetChar() == 'y';

            printf("Show when client used gameobjects? (y/n)\n> ");
            bool showUseGo = GetChar() == 'y';

            printf("Show when client used items? (y/n)\n> ");
            bool showUseItem = GetChar() == 'y';

            printf("Show creature related events? (y/n)\n> ");
            bool showCreatures = GetChar() == 'y';
            bool showCreatureAttacks = false;
            bool showCreatureTexts = false;
            bool showCreatureEmotes = false;
            bool showCreatureMoves = false;
            bool showCreatureCasts = false;
            bool showCreatureUpdates = false;
            if (showCreatures)
            {
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
            bool showGameObjectCasts = false;
            bool showGameObjectUpdates = false;
            if (showGameObjects)
            {
                printf("Show when gameobjects casted spells? (y/n)\n> ");
                showGameObjectCasts = GetChar() == 'y';

                printf("Show changes to gameobject update fields? (y/n)\n> ");
                showGameObjectUpdates = GetChar() == 'y';
            }

            printf("Show spell casts? (y/n)\n> ");
            bool showCasts = GetChar() == 'y';

            printf("Show when sounds or music played? (y/n)\n> ");
            bool showSounds = GetChar() == 'y';

            uint32 uiStartTime = 0;
            printf("Start time: ");
            scanf("%u", &uiStartTime);
            startTime = uiStartTime;

            uint32 uiEndTime = 0;
            printf("Duration: ");
            scanf("%u", &uiEndTime);
            uiEndTime = uiStartTime + uiEndTime;

            TimelineMaker::CreateTimelineForAll(uiStartTime, uiEndTime, showQuests, showUseGo, showUseItem, showCreatures, showCreatureAttacks, showCreatureTexts, showCreatureEmotes, showCreatureMoves, showCreatureCasts, showCreatureUpdates, showGameObjects, showGameObjectCasts, showGameObjectUpdates, showSounds);
        }
        else if (option == OPTION_TIMELINE_WAYPOINTS)
        {
            printf("Guid: ");
            uint32 guid = 0;
            if (scanf("%u", &guid) == 1)
            {
                printf("Use start position instead of destination? (y/n)\n> ");
                TimelineMaker::CreateWaypoints(guid, GetChar() == 'y');
                if (uint32 count = TimelineMaker::PrintWaypointsToFile())
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
        else if (option == OPTION_QUESTS_WITH_RP_EVENTS)
        {
            printf("Time limit: ");
            uint32 duration = 0;
            if (scanf("%u", &duration) == 1)
            {
                printf("Searching for quests with an event on accept or completion...\n");
                if (!TimelineMaker::FindQuestsWithRpEvents(duration))
                    printf("No quests with scripted events found.\n");
                GetChar();
                return 0;
            }
        }
    }

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
    
    GetChar();
    
    GameDb.Uninitialise();
    return 0;
}


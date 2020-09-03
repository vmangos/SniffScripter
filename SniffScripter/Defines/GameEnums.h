#ifndef _GAME_ENUMS_H
#define _GAME_ENUMS_H

#include <string>
#include <cmath>
#include "Common.h"

enum Emotes
{
    ONESHOT_NONE = 0,
    ONESHOT_TALK_DNR = 1,
    ONESHOT_BOW = 2,
    ONESHOT_WAVE_DNR = 3,
    ONESHOT_CHEER_DNR = 4,
    ONESHOT_EXCLAMATION_DNR = 5,
    ONESHOT_QUESTION = 6,
    ONESHOT_EAT = 7,
    STATE_DANCE = 10,
    ONESHOT_LAUGH = 11,
    STATE_SLEEP = 12,
    STATE_SIT = 13,
    ONESHOT_RUDE_DNR = 14,
    ONESHOT_ROAR_DNR = 15,
    ONESHOT_KNEEL = 16,
    ONESHOT_KISS = 17,
    ONESHOT_CRY = 18,
    ONESHOT_CHICKEN = 19,
    ONESHOT_BEG = 20,
    ONESHOT_APPLAUD = 21,
    ONESHOT_SHOUT_DNR = 22,
    ONESHOT_FLEX = 23,
    ONESHOT_SHY_DNR = 24,
    ONESHOT_POINT_DNR = 25,
    STATE_STAND = 26,
    STATE_READYUNARMED = 27,
    STATE_WORK = 28,
    STATE_POINT_DNR = 29,
    STATE_NONE = 30,
    ONESHOT_WOUND = 33,
    ONESHOT_WOUNDCRITICAL = 34,
    ONESHOT_ATTACKUNARMED = 35,
    ONESHOT_ATTACK1H = 36,
    ONESHOT_ATTACK2HTIGHT = 37,
    ONESHOT_ATTACK2HLOOSE = 38,
    ONESHOT_PARRYUNARMED = 39,
    ONESHOT_PARRYSHIELD = 43,
    ONESHOT_READYUNARMED = 44,
    ONESHOT_READY1H = 45,
    ONESHOT_READYBOW = 48,
    ONESHOT_SPELLPRECAST = 50,
    ONESHOT_SPELLCAST = 51,
    ONESHOT_BATTLEROAR = 53,
    ONESHOT_SPECIALATTACK1H = 54,
    ONESHOT_KICK = 60,
    ONESHOT_ATTACKTHROWN = 61,
    STATE_STUN = 64,
    STATE_DEAD = 65,
    ONESHOT_SALUTE = 66,
    STATE_KNEEL = 68,
    STATE_USESTANDING = 69,
    ONESHOT_WAVE_NOSHEATHE = 70,
    ONESHOT_CHEER_NOSHEATHE = 71,
    ONESHOT_EAT_NOSHEATHE = 92,
    STATE_STUN_NOSHEATHE = 93,
    ONESHOT_DANCE = 94,
    ONESHOT_SALUTE_NOSHEATH = 113,
    STATE_USESTANDING_NOSHEATHE = 133,
    ONESHOT_LAUGH_NOSHEATHE = 153,
    STATE_WORK_NOSHEATHE = 173,
    STATE_SPELLPRECAST = 193,
    ONESHOT_READYRIFLE = 213,
    STATE_READYRIFLE = 214,
    STATE_WORK_NOSHEATHE_MINING = 233,
    STATE_WORK_NOSHEATHE_CHOPWOOD = 234,
    zzOLDONESHOT_LIFTOFF = 253,
    ONESHOT_LIFTOFF = 254,
    ONESHOT_YES_DNR = 273,
    ONESHOT_NO_DNR = 274,
    ONESHOT_TRAIN_DNR = 275,
    ONESHOT_LAND = 293,
    STATE_AT_EASE = 313,
    STATE_READY1H = 333,
    STATE_SPELLKNEELSTART = 353,
    STATE_SUBMERGED = 373,
    ONESHOT_SUBMERGE = 374,
    STATE_READY2H = 375,
    STATE_READYBOW = 376,
};

inline std::string GetEmoteName(uint32 id)
{
    switch (id)
    {
        case ONESHOT_NONE:
            return "ONESHOT_NONE";
        case ONESHOT_TALK_DNR:
            return "ONESHOT_TALK_DNR";
        case ONESHOT_BOW:
            return "ONESHOT_BOW";
        case ONESHOT_WAVE_DNR:
            return "ONESHOT_WAVE_DNR";
        case ONESHOT_CHEER_DNR:
            return "ONESHOT_CHEER_DNR";
        case ONESHOT_EXCLAMATION_DNR:
            return "ONESHOT_EXCLAMATION_DNR";
        case ONESHOT_QUESTION:
            return "ONESHOT_QUESTION";
        case ONESHOT_EAT:
            return "ONESHOT_EAT";
        case STATE_DANCE:
            return "STATE_DANCE";
        case ONESHOT_LAUGH:
            return "ONESHOT_LAUGH";
        case STATE_SLEEP:
            return "STATE_SLEEP";
        case STATE_SIT:
            return "STATE_SIT";
        case ONESHOT_RUDE_DNR:
            return "ONESHOT_RUDE_DNR";
        case ONESHOT_ROAR_DNR:
            return "ONESHOT_ROAR_DNR";
        case ONESHOT_KNEEL:
            return "ONESHOT_KNEEL";
        case ONESHOT_KISS:
            return "ONESHOT_KISS";
        case ONESHOT_CRY:
            return "ONESHOT_CRY";
        case ONESHOT_CHICKEN:
            return "ONESHOT_CHICKEN";
        case ONESHOT_BEG:
            return "ONESHOT_BEG";
        case ONESHOT_APPLAUD:
            return "ONESHOT_APPLAUD";
        case ONESHOT_SHOUT_DNR:
            return "ONESHOT_SHOUT_DNR";
        case ONESHOT_FLEX:
            return "ONESHOT_FLEX";
        case ONESHOT_SHY_DNR:
            return "ONESHOT_SHY_DNR";
        case ONESHOT_POINT_DNR:
            return "ONESHOT_POINT_DNR";
        case STATE_STAND:
            return "STATE_STAND";
        case STATE_READYUNARMED:
            return "STATE_READYUNARMED";
        case STATE_WORK:
            return "STATE_WORK";
        case STATE_POINT_DNR:
            return "STATE_POINT_DNR";
        case STATE_NONE:
            return "STATE_NONE";
        case ONESHOT_WOUND:
            return "ONESHOT_WOUND";
        case ONESHOT_WOUNDCRITICAL:
            return "ONESHOT_WOUNDCRITICAL";
        case ONESHOT_ATTACKUNARMED:
            return "ONESHOT_ATTACKUNARMED";
        case ONESHOT_ATTACK1H:
            return "ONESHOT_ATTACK1H";
        case ONESHOT_ATTACK2HTIGHT:
            return "ONESHOT_ATTACK2HTIGHT";
        case ONESHOT_ATTACK2HLOOSE:
            return "ONESHOT_ATTACK2HLOOSE";
        case ONESHOT_PARRYUNARMED:
            return "ONESHOT_PARRYUNARMED";
        case ONESHOT_PARRYSHIELD:
            return "ONESHOT_PARRYSHIELD";
        case ONESHOT_READYUNARMED:
            return "ONESHOT_READYUNARMED";
        case ONESHOT_READY1H:
            return "ONESHOT_READY1H";
        case ONESHOT_READYBOW:
            return "ONESHOT_READYBOW";
        case ONESHOT_SPELLPRECAST:
            return "ONESHOT_SPELLPRECAST";
        case ONESHOT_SPELLCAST:
            return "ONESHOT_SPELLCAST";
        case ONESHOT_BATTLEROAR:
            return "ONESHOT_BATTLEROAR";
        case ONESHOT_SPECIALATTACK1H:
            return "ONESHOT_SPECIALATTACK1H";
        case ONESHOT_KICK:
            return "ONESHOT_KICK";
        case ONESHOT_ATTACKTHROWN:
            return "ONESHOT_ATTACKTHROWN";
        case STATE_STUN:
            return "STATE_STUN";
        case STATE_DEAD:
            return "STATE_DEAD";
        case ONESHOT_SALUTE:
            return "ONESHOT_SALUTE";
        case STATE_KNEEL:
            return "STATE_KNEEL";
        case STATE_USESTANDING:
            return "STATE_USESTANDING";
        case ONESHOT_WAVE_NOSHEATHE:
            return "ONESHOT_WAVE_NOSHEATHE";
        case ONESHOT_CHEER_NOSHEATHE:
            return "ONESHOT_CHEER_NOSHEATHE";
        case ONESHOT_EAT_NOSHEATHE:
            return "ONESHOT_EAT_NOSHEATHE";
        case STATE_STUN_NOSHEATHE:
            return "STATE_STUN_NOSHEATHE";
        case ONESHOT_DANCE:
            return "ONESHOT_DANCE";
        case ONESHOT_SALUTE_NOSHEATH:
            return "ONESHOT_SALUTE_NOSHEATH";
        case STATE_USESTANDING_NOSHEATHE:
            return "STATE_USESTANDING_NOSHEATHE";
        case ONESHOT_LAUGH_NOSHEATHE:
            return "ONESHOT_LAUGH_NOSHEATHE";
        case STATE_WORK_NOSHEATHE:
            return "STATE_WORK_NOSHEATHE";
        case STATE_SPELLPRECAST:
            return "STATE_SPELLPRECAST";
        case ONESHOT_READYRIFLE:
            return "ONESHOT_READYRIFLE";
        case STATE_READYRIFLE:
            return "STATE_READYRIFLE";
        case STATE_WORK_NOSHEATHE_MINING:
            return "STATE_WORK_NOSHEATHE_MINING";
        case STATE_WORK_NOSHEATHE_CHOPWOOD:
            return "STATE_WORK_NOSHEATHE_CHOPWOOD";
        case zzOLDONESHOT_LIFTOFF:
            return "zzOLDONESHOT_LIFTOFF";
        case ONESHOT_LIFTOFF:
            return "ONESHOT_LIFTOFF";
        case ONESHOT_YES_DNR:
            return "ONESHOT_YES_DNR";
        case ONESHOT_NO_DNR:
            return "ONESHOT_NO_DNR";
        case ONESHOT_TRAIN_DNR:
            return "ONESHOT_TRAIN_DNR";
        case ONESHOT_LAND:
            return "ONESHOT_LAND";
        case STATE_AT_EASE:
            return "STATE_AT_EASE";
        case STATE_READY1H:
            return "STATE_READY1H";
        case STATE_SPELLKNEELSTART:
            return "STATE_SPELLKNEELSTART";
        case STATE_SUBMERGED:
            return "STATE_SUBMERGED";
        case ONESHOT_SUBMERGE:
            return "ONESHOT_SUBMERGE";
        case STATE_READY2H:
            return "STATE_READY2H";
        case STATE_READYBOW:
            return "STATE_READYBOW";
    }
    return "UNKNOWN";
}

enum UnitStandStateType
{
    UNIT_STAND_STATE_STAND             = 0,
    UNIT_STAND_STATE_SIT               = 1,
    UNIT_STAND_STATE_SIT_CHAIR         = 2,
    UNIT_STAND_STATE_SLEEP             = 3,
    UNIT_STAND_STATE_SIT_LOW_CHAIR     = 4,
    UNIT_STAND_STATE_SIT_MEDIUM_CHAIR  = 5,
    UNIT_STAND_STATE_SIT_HIGH_CHAIR    = 6,
    UNIT_STAND_STATE_DEAD              = 7,
    UNIT_STAND_STATE_KNEEL             = 8
};

inline std::string GetStandStateName(uint32 state)
{
    switch (state)
    {
        case UNIT_STAND_STATE_STAND:
            return "UNIT_STAND_STATE_STAND";
        case UNIT_STAND_STATE_SIT:
            return "UNIT_STAND_STATE_SIT";
        case UNIT_STAND_STATE_SIT_CHAIR:
            return "UNIT_STAND_STATE_SIT_CHAIR";
        case UNIT_STAND_STATE_SLEEP:
            return "UNIT_STAND_STATE_SLEEP";
        case UNIT_STAND_STATE_SIT_LOW_CHAIR:
            return "UNIT_STAND_STATE_SIT_LOW_CHAIR";
        case UNIT_STAND_STATE_SIT_MEDIUM_CHAIR:
            return "UNIT_STAND_STATE_SIT_MEDIUM_CHAIR";
        case UNIT_STAND_STATE_SIT_HIGH_CHAIR:
            return "UNIT_STAND_STATE_SIT_HIGH_CHAIR";
        case UNIT_STAND_STATE_DEAD:
            return "UNIT_STAND_STATE_DEAD";
        case UNIT_STAND_STATE_KNEEL:
            return "UNIT_STAND_STATE_KNEEL";
    }
    return "UNKNOWN";
}

namespace Classic
{
    enum NPCFlags_Classic : uint32
    {
        UNIT_NPC_FLAG_GOSSIP                = 0x00000001,     // 100%
        UNIT_NPC_FLAG_QUESTGIVER            = 0x00000002,     // 100%
        UNIT_NPC_FLAG_UNK1                  = 0x00000004,
        UNIT_NPC_FLAG_UNK2                  = 0x00000008,
        UNIT_NPC_FLAG_TRAINER               = 0x00000010,     // 100%
        UNIT_NPC_FLAG_TRAINER_CLASS         = 0x00000020,     // 100%
        UNIT_NPC_FLAG_TRAINER_PROFESSION    = 0x00000040,     // 100%
        UNIT_NPC_FLAG_VENDOR                = 0x00000080,     // 100%
        UNIT_NPC_FLAG_VENDOR_AMMO           = 0x00000100,     // 100%, general goods vendor
        UNIT_NPC_FLAG_VENDOR_FOOD           = 0x00000200,     // 100%
        UNIT_NPC_FLAG_VENDOR_POISON         = 0x00000400,     // guessed
        UNIT_NPC_FLAG_VENDOR_REAGENT        = 0x00000800,     // 100%
        UNIT_NPC_FLAG_REPAIR                = 0x00001000,     // 100%
        UNIT_NPC_FLAG_FLIGHTMASTER          = 0x00002000,     // 100%
        UNIT_NPC_FLAG_SPIRITHEALER          = 0x00004000,     // guessed
        UNIT_NPC_FLAG_SPIRITGUIDE           = 0x00008000,     // guessed
        UNIT_NPC_FLAG_INNKEEPER             = 0x00010000,     // 100%
        UNIT_NPC_FLAG_BANKER                = 0x00020000,     // 100%
        UNIT_NPC_FLAG_PETITIONER            = 0x00040000,     // 100% 0xC0000 = guild petitions, 0x40000 = arena team petitions
        UNIT_NPC_FLAG_TABARDDESIGNER        = 0x00080000,     // 100%
        UNIT_NPC_FLAG_BATTLEMASTER          = 0x00100000,     // 100%
        UNIT_NPC_FLAG_AUCTIONEER            = 0x00200000,     // 100%
        UNIT_NPC_FLAG_STABLEMASTER          = 0x00400000,     // 100%
        UNIT_NPC_FLAG_GUILD_BANKER          = 0x00800000,     //
        UNIT_NPC_FLAG_SPELLCLICK            = 0x01000000,     //
        UNIT_NPC_FLAG_PLAYER_VEHICLE        = 0x02000000,     // players with mounts that have vehicle data should have it set
        UNIT_NPC_FLAG_MAILBOX               = 0x04000000,     // mailbox
        UNIT_NPC_FLAG_ARTIFACT_POWER_RESPEC = 0x08000000,     // artifact powers reset
        UNIT_NPC_FLAG_TRANSMOGRIFIER        = 0x10000000,     // transmogrification
        UNIT_NPC_FLAG_VAULTKEEPER           = 0x20000000,     // void storage
        UNIT_NPC_FLAG_WILD_BATTLE_PET       = 0x40000000,     // Pet that player can fight (Battle Pet)
        UNIT_NPC_FLAG_BLACK_MARKET          = 0x80000000,     // black market
        MAX_NPC_FLAGS = 32
    };
}

namespace Vanilla
{
    enum NPCFlags_Vanilla
    {
        UNIT_NPC_FLAG_NONE                  = 0x00000000,
        UNIT_NPC_FLAG_GOSSIP                = 0x00000001,       // 100%
        UNIT_NPC_FLAG_QUESTGIVER            = 0x00000002,       // 100%
        UNIT_NPC_FLAG_VENDOR                = 0x00000004,       // 100%
        UNIT_NPC_FLAG_FLIGHTMASTER          = 0x00000008,       // 100%
        UNIT_NPC_FLAG_TRAINER               = 0x00000010,       // 100%
        UNIT_NPC_FLAG_SPIRITHEALER          = 0x00000020,       // guessed
        UNIT_NPC_FLAG_SPIRITGUIDE           = 0x00000040,       // guessed
        UNIT_NPC_FLAG_INNKEEPER             = 0x00000080,       // 100%
        UNIT_NPC_FLAG_BANKER                = 0x00000100,       // 100%
        UNIT_NPC_FLAG_PETITIONER            = 0x00000200,       // 100% 0xC0000 = guild petitions
        UNIT_NPC_FLAG_TABARDDESIGNER        = 0x00000400,       // 100%
        UNIT_NPC_FLAG_BATTLEMASTER          = 0x00000800,       // 100%
        UNIT_NPC_FLAG_AUCTIONEER            = 0x00001000,       // 100%
        UNIT_NPC_FLAG_STABLEMASTER          = 0x00002000,       // 100%
        UNIT_NPC_FLAG_REPAIR                = 0x00004000,       // 100%
        UNIT_NPC_FLAG_OUTDOORPVP            = 0x20000000,       // custom flag for outdoor pvp creatures || Custom flag
    };
}

inline uint32 ConvertClassicNpcFlagToVanilla(uint32 flag)
{
    switch (flag)
    {
        case Classic::UNIT_NPC_FLAG_GOSSIP:
            return Vanilla::UNIT_NPC_FLAG_GOSSIP;
        case Classic::UNIT_NPC_FLAG_QUESTGIVER:
            return Vanilla::UNIT_NPC_FLAG_QUESTGIVER;
        case Classic::UNIT_NPC_FLAG_TRAINER:
        case Classic::UNIT_NPC_FLAG_TRAINER_CLASS:
        case Classic::UNIT_NPC_FLAG_TRAINER_PROFESSION:
            return Vanilla::UNIT_NPC_FLAG_TRAINER;
        case Classic::UNIT_NPC_FLAG_VENDOR:
        case Classic::UNIT_NPC_FLAG_VENDOR_AMMO:
        case Classic::UNIT_NPC_FLAG_VENDOR_FOOD:
        case Classic::UNIT_NPC_FLAG_VENDOR_POISON:
        case Classic::UNIT_NPC_FLAG_VENDOR_REAGENT:
            return Vanilla::UNIT_NPC_FLAG_VENDOR;
        case Classic::UNIT_NPC_FLAG_REPAIR:
            return Vanilla::UNIT_NPC_FLAG_REPAIR;
        case Classic::UNIT_NPC_FLAG_FLIGHTMASTER:
            return Vanilla::UNIT_NPC_FLAG_FLIGHTMASTER;
        case Classic::UNIT_NPC_FLAG_SPIRITHEALER:
            return Vanilla::UNIT_NPC_FLAG_SPIRITHEALER;
        case Classic::UNIT_NPC_FLAG_SPIRITGUIDE:
            return Vanilla::UNIT_NPC_FLAG_SPIRITGUIDE;
        case Classic::UNIT_NPC_FLAG_INNKEEPER:
            return Vanilla::UNIT_NPC_FLAG_INNKEEPER;
        case Classic::UNIT_NPC_FLAG_BANKER:
            return Vanilla::UNIT_NPC_FLAG_BANKER;
        case Classic::UNIT_NPC_FLAG_PETITIONER:
            return Vanilla::UNIT_NPC_FLAG_PETITIONER;
        case Classic::UNIT_NPC_FLAG_TABARDDESIGNER:
            return Vanilla::UNIT_NPC_FLAG_TABARDDESIGNER;
        case Classic::UNIT_NPC_FLAG_BATTLEMASTER:
            return Vanilla::UNIT_NPC_FLAG_BATTLEMASTER;
        case Classic::UNIT_NPC_FLAG_AUCTIONEER:
            return Vanilla::UNIT_NPC_FLAG_AUCTIONEER;
        case Classic::UNIT_NPC_FLAG_STABLEMASTER:
            return Vanilla::UNIT_NPC_FLAG_STABLEMASTER;
    }
    return 0;
}


inline std::string GetNpcFlagName(uint32 flag)
{
    switch (flag)
    {
        case Classic::UNIT_NPC_FLAG_GOSSIP:
            return "UNIT_NPC_FLAG_GOSSIP";
        case Classic::UNIT_NPC_FLAG_QUESTGIVER:
            return "UNIT_NPC_FLAG_QUESTGIVER";
        case Classic::UNIT_NPC_FLAG_UNK1:
            return "UNIT_NPC_FLAG_UNK1";
        case Classic::UNIT_NPC_FLAG_UNK2:
            return "UNIT_NPC_FLAG_UNK2";
        case Classic::UNIT_NPC_FLAG_TRAINER:
            return "UNIT_NPC_FLAG_TRAINER";
        case Classic::UNIT_NPC_FLAG_TRAINER_CLASS:
            return "UNIT_NPC_FLAG_TRAINER_CLASS";
        case Classic::UNIT_NPC_FLAG_TRAINER_PROFESSION:
            return "UNIT_NPC_FLAG_TRAINER_PROFESSION";
        case Classic::UNIT_NPC_FLAG_VENDOR:
            return "UNIT_NPC_FLAG_VENDOR";
        case Classic::UNIT_NPC_FLAG_VENDOR_AMMO:
            return "UNIT_NPC_FLAG_VENDOR_AMMO";
        case Classic::UNIT_NPC_FLAG_VENDOR_FOOD:
            return "UNIT_NPC_FLAG_VENDOR_FOOD";
        case Classic::UNIT_NPC_FLAG_VENDOR_POISON:
            return "UNIT_NPC_FLAG_VENDOR_POISON";
        case Classic::UNIT_NPC_FLAG_VENDOR_REAGENT:
            return "UNIT_NPC_FLAG_VENDOR_REAGENT";
        case Classic::UNIT_NPC_FLAG_REPAIR:
            return "UNIT_NPC_FLAG_REPAIR";
        case Classic::UNIT_NPC_FLAG_FLIGHTMASTER:
            return "UNIT_NPC_FLAG_FLIGHTMASTER";
        case Classic::UNIT_NPC_FLAG_SPIRITHEALER:
            return "UNIT_NPC_FLAG_SPIRITHEALER";
        case Classic::UNIT_NPC_FLAG_SPIRITGUIDE:
            return "UNIT_NPC_FLAG_SPIRITGUIDE";
        case Classic::UNIT_NPC_FLAG_INNKEEPER:
            return "UNIT_NPC_FLAG_INNKEEPER";
        case Classic::UNIT_NPC_FLAG_BANKER:
            return "UNIT_NPC_FLAG_BANKER";
        case Classic::UNIT_NPC_FLAG_PETITIONER:
            return "UNIT_NPC_FLAG_PETITIONER";
        case Classic::UNIT_NPC_FLAG_TABARDDESIGNER:
            return "UNIT_NPC_FLAG_TABARDDESIGNER";
        case Classic::UNIT_NPC_FLAG_BATTLEMASTER:
            return "UNIT_NPC_FLAG_BATTLEMASTER";
        case Classic::UNIT_NPC_FLAG_AUCTIONEER:
            return "UNIT_NPC_FLAG_AUCTIONEER";
        case Classic::UNIT_NPC_FLAG_STABLEMASTER:
            return "UNIT_NPC_FLAG_STABLEMASTER";
        case Classic::UNIT_NPC_FLAG_GUILD_BANKER:
            return "UNIT_NPC_FLAG_GUILD_BANKER";
        case Classic::UNIT_NPC_FLAG_SPELLCLICK:
            return "UNIT_NPC_FLAG_SPELLCLICK";
        case Classic::UNIT_NPC_FLAG_PLAYER_VEHICLE:
            return "UNIT_NPC_FLAG_PLAYER_VEHICLE";
        case Classic::UNIT_NPC_FLAG_MAILBOX:
            return "UNIT_NPC_FLAG_MAILBOX";
        case Classic::UNIT_NPC_FLAG_ARTIFACT_POWER_RESPEC:
            return "UNIT_NPC_FLAG_ARTIFACT_POWER_RESPEC";
        case Classic::UNIT_NPC_FLAG_TRANSMOGRIFIER:
            return "UNIT_NPC_FLAG_TRANSMOGRIFIER";
        case Classic::UNIT_NPC_FLAG_VAULTKEEPER:
            return "UNIT_NPC_FLAG_VAULTKEEPER";
        case Classic::UNIT_NPC_FLAG_WILD_BATTLE_PET:
            return "UNIT_NPC_FLAG_WILD_BATTLE_PET";
        case Classic::UNIT_NPC_FLAG_BLACK_MARKET:
            return "UNIT_NPC_FLAG_BLACK_MARKET";
    }
    return "UNKNOWN";
}

inline std::string GetNpcFlagNames(uint32 flags)
{
    std::string flagNames;
    for (uint32 i = 0; i < Classic::MAX_NPC_FLAGS; i++)
    {
        uint32 flag = pow(2, i);
        if (flags & flag)
        {
            if (!flagNames.empty())
                flagNames += " | ";
            flagNames += GetNpcFlagName(flag);
        }
    }
    return flagNames;
}

enum UnitFlags : uint32
{
    UNIT_FLAG_SERVER_CONTROLLED     = 0x00000001,           // set only when unit movement is controlled by server - by SPLINE/MONSTER_MOVE packets, together with UNIT_FLAG_STUNNED; only set to units controlled by client; client function CGUnit_C::IsClientControlled returns false when set for owner
    UNIT_FLAG_NON_ATTACKABLE        = 0x00000002,           // not attackable
    UNIT_FLAG_REMOVE_CLIENT_CONTROL = 0x00000004,           // This is a legacy flag used to disable movement player's movement while controlling other units, SMSG_CLIENT_CONTROL replaces this functionality clientside now. CONFUSED and FLEEING flags have the same effect on client movement asDISABLE_MOVE_CONTROL in addition to preventing spell casts/autoattack (they all allow climbing steeper hills and emotes while moving)
    UNIT_FLAG_PVP_ATTACKABLE        = 0x00000008,           // allow apply pvp rules to attackable state in addition to faction dependent state
    UNIT_FLAG_RENAME                = 0x00000010,
    UNIT_FLAG_PREPARATION           = 0x00000020,           // don't take reagents for spells with SPELL_ATTR5_NO_REAGENT_WHILE_PREP
    UNIT_FLAG_UNK_6                 = 0x00000040,
    UNIT_FLAG_NOT_ATTACKABLE_1      = 0x00000080,           // ?? (UNIT_FLAG_PVP_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1) is NON_PVP_ATTACKABLE
    UNIT_FLAG_IMMUNE_TO_PC          = 0x00000100,           // disables combat/assistance with PlayerCharacters (PC) - see Unit::_IsValidAttackTarget, Unit::_IsValidAssistTarget
    UNIT_FLAG_IMMUNE_TO_NPC         = 0x00000200,           // disables combat/assistance with NonPlayerCharacters (NPC) - see Unit::_IsValidAttackTarget, Unit::_IsValidAssistTarget
    UNIT_FLAG_LOOTING               = 0x00000400,           // loot animation
    UNIT_FLAG_PET_IN_COMBAT         = 0x00000800,           // in combat?, 2.0.8
    UNIT_FLAG_PVP                   = 0x00001000,           // changed in 3.0.3
    UNIT_FLAG_SILENCED              = 0x00002000,           // silenced, 2.1.1
    UNIT_FLAG_CANNOT_SWIM           = 0x00004000,           // 2.0.8
    UNIT_FLAG_UNK_15                = 0x00008000,
    UNIT_FLAG_UNK_16                = 0x00010000,
    UNIT_FLAG_PACIFIED              = 0x00020000,           // 3.0.3 ok
    UNIT_FLAG_STUNNED               = 0x00040000,           // 3.0.3 ok
    UNIT_FLAG_IN_COMBAT             = 0x00080000,
    UNIT_FLAG_TAXI_FLIGHT           = 0x00100000,           // disable casting at client side spell not allowed by taxi flight (mounted?), probably used with 0x4 flag
    UNIT_FLAG_DISARMED              = 0x00200000,           // 3.0.3, disable melee spells casting..., "Required melee weapon" added to melee spells tooltip.
    UNIT_FLAG_CONFUSED              = 0x00400000,
    UNIT_FLAG_FLEEING               = 0x00800000,
    UNIT_FLAG_PLAYER_CONTROLLED     = 0x01000000,           // used in spell Eyes of the Beast for pet... let attack by controlled creature
    UNIT_FLAG_NOT_SELECTABLE        = 0x02000000,
    UNIT_FLAG_SKINNABLE             = 0x04000000,
    UNIT_FLAG_MOUNT                 = 0x08000000,
    UNIT_FLAG_UNK_28                = 0x10000000,
    UNIT_FLAG_UNK_29                = 0x20000000,           // used in Feing Death spell
    UNIT_FLAG_SHEATHE               = 0x40000000,
    UNIT_FLAG_UNK_31                = 0x80000000,
    MAX_UNIT_FLAGS = 32
};

// If the flag should be changed in script commands.
inline bool IsScriptRelevantUnitFlag(uint32 flag)
{
    switch (flag)
    {
        case UNIT_FLAG_NON_ATTACKABLE:
        case UNIT_FLAG_NOT_ATTACKABLE_1:
        case UNIT_FLAG_IMMUNE_TO_PC:
        case UNIT_FLAG_IMMUNE_TO_NPC:
        case UNIT_FLAG_PVP:
        case UNIT_FLAG_NOT_SELECTABLE:
            return true;
    }
    return false;
}

inline std::string GetUnitFlagName(uint32 flag)
{
    switch (flag)
    {
        case UNIT_FLAG_SERVER_CONTROLLED:
            return "UNIT_FLAG_SERVER_CONTROLLED";
        case UNIT_FLAG_NON_ATTACKABLE:
            return "UNIT_FLAG_NON_ATTACKABLE";
        case UNIT_FLAG_REMOVE_CLIENT_CONTROL:
            return "UNIT_FLAG_REMOVE_CLIENT_CONTROL";
        case UNIT_FLAG_PVP_ATTACKABLE:
            return "UNIT_FLAG_PVP_ATTACKABLE";
        case UNIT_FLAG_RENAME:
            return "UNIT_FLAG_RENAME";
        case UNIT_FLAG_PREPARATION:
            return "UNIT_FLAG_PREPARATION";
        case UNIT_FLAG_UNK_6:
            return "UNIT_FLAG_UNK_6";
        case UNIT_FLAG_NOT_ATTACKABLE_1:
            return "UNIT_FLAG_NOT_ATTACKABLE_1";
        case UNIT_FLAG_IMMUNE_TO_PC:
            return "UNIT_FLAG_IMMUNE_TO_PC";
        case UNIT_FLAG_IMMUNE_TO_NPC:
            return "UNIT_FLAG_IMMUNE_TO_NPC";
        case UNIT_FLAG_LOOTING:
            return "UNIT_FLAG_LOOTING";
        case UNIT_FLAG_PET_IN_COMBAT:
            return "UNIT_FLAG_PET_IN_COMBAT";
        case UNIT_FLAG_PVP:
            return "UNIT_FLAG_PVP";
        case UNIT_FLAG_SILENCED:
            return "UNIT_FLAG_SILENCED";
        case UNIT_FLAG_CANNOT_SWIM:
            return "UNIT_FLAG_CANNOT_SWIM";
        case UNIT_FLAG_UNK_15:
            return "UNIT_FLAG_UNK_15";
        case UNIT_FLAG_UNK_16:
            return "UNIT_FLAG_UNK_16";
        case UNIT_FLAG_PACIFIED:
            return "UNIT_FLAG_PACIFIED";
        case UNIT_FLAG_STUNNED:
            return "UNIT_FLAG_STUNNED";
        case UNIT_FLAG_IN_COMBAT:
            return "UNIT_FLAG_IN_COMBAT";
        case UNIT_FLAG_TAXI_FLIGHT:
            return "UNIT_FLAG_TAXI_FLIGHT";
        case UNIT_FLAG_DISARMED:
            return "UNIT_FLAG_DISARMED";
        case UNIT_FLAG_CONFUSED:
            return "UNIT_FLAG_CONFUSED";
        case UNIT_FLAG_FLEEING:
            return "UNIT_FLAG_FLEEING";
        case UNIT_FLAG_PLAYER_CONTROLLED:
            return "UNIT_FLAG_PLAYER_CONTROLLED";
        case UNIT_FLAG_NOT_SELECTABLE:
            return "UNIT_FLAG_NOT_SELECTABLE";
        case UNIT_FLAG_SKINNABLE:
            return "UNIT_FLAG_SKINNABLE";
        case UNIT_FLAG_MOUNT:
            return "UNIT_FLAG_MOUNT";
        case UNIT_FLAG_UNK_28:
            return "UNIT_FLAG_UNK_28";
        case UNIT_FLAG_UNK_29:
            return "UNIT_FLAG_UNK_29";
        case UNIT_FLAG_SHEATHE:
            return "UNIT_FLAG_SHEATHE";
        case UNIT_FLAG_UNK_31:
            return "UNIT_FLAG_UNK_31";
    }
    return "UNKNOWN";
}

inline std::string GetUnitFlagNames(uint32 flags)
{
    std::string flagNames;
    for (uint32 i = 0; i < MAX_UNIT_FLAGS; i++)
    {
        uint32 flag = pow(2, i);
        if (flags & flag)
        {
            if (!flagNames.empty())
                flagNames += " | ";
            flagNames += GetUnitFlagName(flag);
        }
    }
    return flagNames;
}

enum GameObjectFlags
{
    GO_FLAG_IN_USE          = 0x00000001,                   // disables interaction while animated
    GO_FLAG_LOCKED          = 0x00000002,                   // require key, spell, event, etc to be opened. Makes "Locked" appear in tooltip
    GO_FLAG_INTERACT_COND   = 0x00000004,                   // cannot interact (condition to interact - requires GO_DYNFLAG_LO_ACTIVATE to enable interaction clientside)
    GO_FLAG_TRANSPORT       = 0x00000008,                   // any kind of transport? Object can transport (elevator, boat, car)
    GO_FLAG_NOT_SELECTABLE  = 0x00000010,                   // not selectable even in GM mode
    GO_FLAG_NODESPAWN       = 0x00000020,                   // never despawn, typically for doors, they just change state
    GO_FLAG_AI_OBSTACLE     = 0x00000040,                   // makes the client register the object in something called AIObstacleMgr, unknown what it does
    GO_FLAG_FREEZE_ANIMATION = 0x00000080,
    GO_FLAG_DAMAGED         = 0x00000200,
    GO_FLAG_DESTROYED       = 0x00000400,
    GO_FLAG_INTERACT_DISTANCE_USES_TEMPLATE_MODEL = 0x00080000, // client checks interaction distance from model sent in SMSG_QUERY_GAMEOBJECT_RESPONSE instead of GAMEOBJECT_DISPLAYID
    GO_FLAG_MAP_OBJECT      = 0x00100000                    // pre-7.0 model loading used to be controlled by file extension (wmo vs m2)
};

inline std::string GetGameObjectFlagName(uint32 flag)
{
    switch (flag)
    {
        case GO_FLAG_IN_USE:
            return "GO_FLAG_IN_USE";
        case GO_FLAG_LOCKED:
            return "GO_FLAG_LOCKED";
        case GO_FLAG_INTERACT_COND:
            return "GO_FLAG_INTERACT_COND";
        case GO_FLAG_TRANSPORT:
            return "GO_FLAG_TRANSPORT";
        case GO_FLAG_NOT_SELECTABLE:
            return "GO_FLAG_NOT_SELECTABLE";
        case GO_FLAG_NODESPAWN:
            return "GO_FLAG_NODESPAWN";
        case GO_FLAG_AI_OBSTACLE:
            return "GO_FLAG_AI_OBSTACLE";
        case GO_FLAG_FREEZE_ANIMATION:
            return "GO_FLAG_FREEZE_ANIMATION";
        case GO_FLAG_DAMAGED:
            return "GO_FLAG_DAMAGED";
        case GO_FLAG_DESTROYED:
            return "GO_FLAG_DESTROYED";
        case GO_FLAG_INTERACT_DISTANCE_USES_TEMPLATE_MODEL:
            return "GO_FLAG_INTERACT_DISTANCE_USES_TEMPLATE_MODEL";
        case GO_FLAG_MAP_OBJECT:
            return "GO_FLAG_MAP_OBJECT";
    }
    return "UNKNOWN";
}

inline std::string GetGameObjectFlagNames(uint32 flags)
{
    std::string flagNames;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = pow(2, i);
        if (flags & flag)
        {
            if (!flagNames.empty())
                flagNames += " | ";
            flagNames += GetGameObjectFlagName(flag);
        }
    }
    return flagNames;
}

enum GOState
{
    GO_STATE_ACTIVE             = 0,                        // show in world as used and not reset (closed door open)
    GO_STATE_READY              = 1,                        // show in world as ready (closed door close)
    GO_STATE_ACTIVE_ALTERNATIVE = 2                         // show in world as used in alt way and not reset (closed door open by cannon fire)
};

inline std::string GetGameObjectStateName(uint32 state)
{
    switch (state)
    {
        case GO_STATE_ACTIVE:
            return "GO_STATE_ACTIVE";
        case GO_STATE_READY:
            return "GO_STATE_READY";
        case GO_STATE_ACTIVE_ALTERNATIVE:
            return "GO_STATE_ACTIVE_ALTERNATIVE";
    }
    return "UNKNOWN";
}

enum ChatMessageType
{
    SNIFF_CHAT_TYPE_SYSTEM               = 0,
    SNIFF_CHAT_TYPE_SAY                  = 1,
    SNIFF_CHAT_TYPE_PARTY                = 2,
    SNIFF_CHAT_TYPE_RAID                 = 3,
    SNIFF_CHAT_TYPE_GUILD                = 4,
    SNIFF_CHAT_TYPE_OFFICER              = 5,
    SNIFF_CHAT_TYPE_YELL                 = 6,
    SNIFF_CHAT_TYPE_WHISPER              = 7,
    SNIFF_CHAT_TYPE_WHISPERFOREIGN       = 8,
    SNIFF_CHAT_TYPE_WHISPERINFORM        = 9,
    SNIFF_CHAT_TYPE_EMOTE                = 10,
    SNIFF_CHAT_TYPE_TEXTEMOTE            = 11,
    SNIFF_CHAT_TYPE_MONSTERSAY           = 12,
    SNIFF_CHAT_TYPE_MONSTERPARTY         = 13,
    SNIFF_CHAT_TYPE_MONSTERYELL          = 14,
    SNIFF_CHAT_TYPE_MONSTERWHISPER       = 15,
    SNIFF_CHAT_TYPE_MONSTEREMOTE         = 16,
    SNIFF_CHAT_TYPE_CHANNEL              = 17,
    SNIFF_CHAT_TYPE_CHANNELJOIN          = 18,
    SNIFF_CHAT_TYPE_CHANNELLEAVE         = 19,
    SNIFF_CHAT_TYPE_CHANNELLIST          = 20,
    SNIFF_CHAT_TYPE_CHANNELNOTICE        = 21,
    SNIFF_CHAT_TYPE_CHANNELNOTICEUSER    = 22,
    SNIFF_CHAT_TYPE_AFK                  = 23,
    SNIFF_CHAT_TYPE_DND                  = 24,
    SNIFF_CHAT_TYPE_IGNORED              = 25,
    SNIFF_CHAT_TYPE_SKILL                = 26,
    SNIFF_CHAT_TYPE_LOOT                 = 27,
    SNIFF_CHAT_TYPE_MONEY                = 28,
    SNIFF_CHAT_TYPE_OPENING              = 29,
    SNIFF_CHAT_TYPE_TRADESKILLS          = 30,
    SNIFF_CHAT_TYPE_PETINFO              = 31,
    SNIFF_CHAT_TYPE_COMBATMISCINFO       = 32,
    SNIFF_CHAT_TYPE_COMBATXPGAIN         = 33,
    SNIFF_CHAT_TYPE_COMBATHONORGAIN      = 34,
    SNIFF_CHAT_TYPE_COMBATFACTIONCHANGE  = 35,
    SNIFF_CHAT_TYPE_BATTLEGROUNDNEUTRAL  = 36,
    SNIFF_CHAT_TYPE_BATTLEGROUNDALLIANCE = 37,
    SNIFF_CHAT_TYPE_BATTLEGROUNDHORDE    = 38,
    SNIFF_CHAT_TYPE_RAIDLEADER           = 39,
    SNIFF_CHAT_TYPE_RAIDWARNING          = 40,
    SNIFF_CHAT_TYPE_RAIDBOSSEMOTE        = 41,
    SNIFF_CHAT_TYPE_RAIDBOSSWHISPER      = 42,
    SNIFF_CHAT_TYPE_FILTERED             = 43,
    SNIFF_CHAT_TYPE_BATTLEGROUND         = 44,
    SNIFF_CHAT_TYPE_BATTLEGROUNDLEADER   = 45,
    SNIFF_CHAT_TYPE_RESTRICTED           = 46,
    SNIFF_CHAT_TYPE_BATTLENET            = 47,
    SNIFF_CHAT_TYPE_ACHIEVEMENT          = 48,
    SNIFF_CHAT_TYPE_GUILDACHIEVEMENT     = 49,
    SNIFF_CHAT_TYPE_ARENAPOINTS          = 50,
    SNIFF_CHAT_TYPE_PARTYLEADER          = 51,
    SNIFF_CHAT_TYPE_ADDON                = UINT_MAX
};

enum ChatType
{
    CHAT_TYPE_SAY               = 0,
    CHAT_TYPE_YELL              = 1,
    CHAT_TYPE_TEXT_EMOTE        = 2,
    CHAT_TYPE_BOSS_EMOTE        = 3,
    CHAT_TYPE_WHISPER           = 4,
    CHAT_TYPE_BOSS_WHISPER      = 5,
    CHAT_TYPE_ZONE_YELL         = 6
};

inline std::string GetGetChatTypeName(uint32 chatType)
{
    switch (chatType)
    {
        case CHAT_TYPE_SAY:
            return "Say";
        case CHAT_TYPE_YELL:
            return "Yell";
        case CHAT_TYPE_TEXT_EMOTE:
            return "Text Emote";
        case CHAT_TYPE_BOSS_EMOTE:
            return "Boss Emote";
        case CHAT_TYPE_WHISPER:
            return "Whisper";
        case CHAT_TYPE_BOSS_WHISPER:
            return "Boss Whisper";
        case CHAT_TYPE_ZONE_YELL:
            return "Zone Yell";
    }
    return "UNKNOWN";
}

inline uint32 ConvertChatTypeToVmangosFormat(uint32 chatType)
{
    switch (chatType)
    {
        case SNIFF_CHAT_TYPE_MONSTERSAY:
            return CHAT_TYPE_SAY;
        case SNIFF_CHAT_TYPE_MONSTERYELL:
            return CHAT_TYPE_YELL;
        case SNIFF_CHAT_TYPE_MONSTEREMOTE:
            return CHAT_TYPE_TEXT_EMOTE;
        case SNIFF_CHAT_TYPE_MONSTERWHISPER:
            return CHAT_TYPE_WHISPER;
    }
    return 0;
}

enum UpdateFields5875
{
    FIELD_GAMEOBJECT_FLAGS           = 9,
    FIELD_GAMEOBJECT_DYN_FLAGS       = 19,
    FIELD_ITEM_FIELD_FLAGS           = 21,
    FIELD_CORPSE_FIELD_FLAGS         = 35,
    FIELD_CORPSE_FIELD_DYNAMIC_FLAGS = 36,
    FIELD_UNIT_FIELD_FLAGS           = 46,
    FIELD_UNIT_DYNAMIC_FLAGS         = 143,
    FIELD_UNIT_NPC_FLAGS             = 147,
    FIELD_UNIT_FIELD_RESISTANCES     = 155,
    FIELD_UNIT_FIELD_RESISTANCES_01  = 156,
    FIELD_UNIT_FIELD_RESISTANCES_02  = 157,
    FIELD_UNIT_FIELD_RESISTANCES_03  = 158,
    FIELD_UNIT_FIELD_RESISTANCES_04  = 159,
    FIELD_UNIT_FIELD_RESISTANCES_05  = 160,
    FIELD_UNIT_FIELD_RESISTANCES_06  = 161,
    FIELD_UNIT_FIELD_ATTACK_POWER    = 165,
    FIELD_PLAYER_FLAGS               = 190,
};

#endif

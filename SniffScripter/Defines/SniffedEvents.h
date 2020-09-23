#ifndef _SNIFFED_EVENTS_H
#define _SNIFFED_EVENTS_H

#include <string>
#include <vector>
#include "Common.h"
#include "GameEnums.h"
#include "WorldDatabase.h"
#include "SniffDatabase.h"

struct KnownObject
{
    KnownObject() {};
    KnownObject(uint32 guid, uint32 entry, std::string type) :
        m_guid(guid), m_entry(entry), m_type(type) {};
    uint32 m_guid;
    uint32 m_entry;
    std::string m_type;
    bool operator==(KnownObject const& other) const
    {
        return m_guid == other.m_guid &&
               m_entry == other.m_entry &&
               m_type == other.m_type;
    }
    bool operator!=(KnownObject const& other) const
    {
        return !(m_guid == other.m_guid &&
                 m_entry == other.m_entry &&
                 m_type == other.m_type);
    }
    bool operator<(KnownObject const& other) const
    {
        return m_guid < other.m_guid;
    }
    bool IsEmpty()
    {
        return m_type.empty();
    }
};

inline std::string FormatObjectName(uint32 guid, uint32 id, std::string type)
{
    std::string name;
    if (type == "Player")
        name = "Player " + SniffDatabase::GetPlayerName(guid) + " (Guid: " + std::to_string(guid) + ")";
    else if (type == "Creature")
        name = "Creature " + WorldDatabase::GetCreatureName(id) + " (Guid: " + std::to_string(guid) + " Entry: " + std::to_string(id) + ")";
    else if (type == "GameObject")
        name = "GameObject " + WorldDatabase::GetGameObjectName(id) + " (Guid: " + std::to_string(guid) + " Entry: " + std::to_string(id) + ")";
    else
        name = type + " " + std::to_string(id);
    return name;
}

inline std::string FormatObjectName(KnownObject const& object)
{
    return FormatObjectName(object.m_guid, object.m_entry, object.m_type);
}

inline std::string GetObjectName(uint32 id, std::string type)
{
    if (type == "Creature")
        return WorldDatabase::GetCreatureName(id);
    else if (type == "GameObject")
        return  WorldDatabase::GetGameObjectName(id);
    return "";
}

inline std::string GetObjectName(KnownObject const& object)
{
    return GetObjectName(object.m_entry, object.m_type);
}

enum SniffedEventType : uint8
{
    SE_CREATURE_CREATE1,
    SE_CREATURE_CREATE2,
    SE_CREATURE_DESTROY,
    SE_CREATURE_TEXT,
    SE_CREATURE_EMOTE,
    SE_CREATURE_ATTACK_START,
    SE_CREATURE_ATTACK_STOP,
    SE_CREATURE_MOVEMENT,
    SE_CREATURE_WAYPOINT, // movement but outputs waypoints table row
    SE_CREATURE_UPDATE_ENTRY,
    SE_CREATURE_UPDATE_DISPLAY_ID,
    SE_CREATURE_UPDATE_FACTION,
    SE_CREATURE_UPDATE_EMOTE_STATE,
    SE_CREATURE_UPDATE_STAND_STATE,
    SE_CREATURE_UPDATE_NPC_FLAGS,
    SE_CREATURE_UPDATE_UNIT_FLAGS,
    SE_GAMEOBJECT_CREATE1,
    SE_GAMEOBJECT_CREATE2,
    SE_GAMEOBJECT_DESTROY,
    SE_GAMEOBJECT_UPDATE_FLAGS,
    SE_GAMEOBJECT_UPDATE_STATE,
    SE_PLAY_MUSIC,
    SE_PLAY_SOUND,
    SE_SPELL_CAST_START,
    SE_SPELL_CAST_GO,
    SE_CLIENT_QUEST_ACCEPT,
    SE_CLIENT_QUEST_COMPLETE,
    SE_CLIENT_CREATURE_INTERACT,
    SE_CLIENT_GAMEOBJECT_USE,
    SE_CLIENT_ITEM_USE,
    SE_CLIENT_RECLAIM_CORPSE,
    SE_CLIENT_RELEASE_SPIRIT
};

struct SniffedEvent
{
    virtual std::string ToString(bool singleLine) const = 0;
    virtual SniffedEventType GetType() const = 0;
    virtual KnownObject GetSourceObject() const { return KnownObject(); };
    virtual KnownObject GetTargetObject() const { return KnownObject(); };
};

struct SniffedEvent_CreatureCreate1 : SniffedEvent
{
    SniffedEvent_CreatureCreate1(uint32 guid, uint32 entry, float x, float y, float z, float o) :
        m_guid(guid), m_entry(entry), m_x(x), m_y(y), m_z(z), m_o(o) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
    float m_o = 0.0f;
    std::string ToString(bool singleLine) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") becomes visible to client";
        if (singleLine)
            txt += " at " + std::to_string(m_x) + " " + std::to_string(m_y) + " " + std::to_string(m_z) + ".";
        else
            txt += ".\nPosition: " + std::to_string(m_x) + " " + std::to_string(m_y) + " " + std::to_string(m_z) + "\nOrientation: " + std::to_string(m_o);

        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_CREATE1;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_CreatureCreate2 : SniffedEvent
{
    SniffedEvent_CreatureCreate2(uint32 guid, uint32 entry, float x, float y, float z, float o) :
        m_guid(guid), m_entry(entry), m_x(x), m_y(y), m_z(z), m_o(o) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
    float m_o = 0.0f;
    std::string ToString(bool singleLine) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") spawns";
        if (singleLine)
            txt += " at " + std::to_string(m_x) + " " + std::to_string(m_y) + " " + std::to_string(m_z) + ".";
        else
            txt += ".\nPosition: " + std::to_string(m_x) + " " + std::to_string(m_y) + " " + std::to_string(m_z) + "\nOrientation: " + std::to_string(m_o);

        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_CREATE2;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_CreatureDestroy : SniffedEvent
{
    SniffedEvent_CreatureDestroy(uint32 guid, uint32 entry) : m_guid(guid), m_entry(entry) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") despawns or goes out range.";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_DESTROY;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_CreatureText : SniffedEvent
{
    SniffedEvent_CreatureText(uint32 guid, uint32 entry, std::string text, uint32 chatType, std::string comment) : 
        m_guid(guid), m_entry(entry), m_chatType(chatType), m_text(text), m_comment(comment) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_chatType = 0;
    std::string m_text;
    std::string m_comment;
    std::string ToString(bool singleLine) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") says text id " + std::to_string(WorldDatabase::GetBroadcastTextId(m_text));
        if (singleLine)
        {
            txt += ": \"" + m_text + "\"";
        }
        else
        {
            txt += ".\nText: " + m_text + "\n";
            txt += "Chat Type: " + GetGetChatTypeName(ConvertChatTypeToVmangosFormat(m_chatType)) + "\n";
            txt += "Comment: " + m_comment;
        }
        
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_TEXT;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_CreatureEmote : SniffedEvent
{
    SniffedEvent_CreatureEmote(uint32 guid, uint32 entry, uint32 emoteId, std::string emoteName) : m_guid(guid), m_entry(entry), m_emoteId(emoteId), m_emoteName(emoteName) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_emoteId = 0;
    std::string m_emoteName;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") performs emote " + m_emoteName + " (" + std::to_string(m_emoteId) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_EMOTE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_CreatureAttackStart : SniffedEvent
{
    SniffedEvent_CreatureAttackStart(uint32 guid, uint32 entry, uint32 victimGuid, uint32 victimId, std::string victimType) :
        m_guid(guid), m_entry(entry), m_victimGuid(victimGuid), m_victimId(victimId), m_victimType(victimType) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_victimGuid = 0;
    uint32 m_victimId = 0;
    std::string m_victimType;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") starts attacking " + FormatObjectName(m_victimGuid, m_victimId, m_victimType) + ".";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_ATTACK_START;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
    KnownObject GetTargetObject() const final
    {
        return KnownObject(m_victimGuid, m_victimId, m_victimType);
    }
};

struct SniffedEvent_CreatureAttackStop : SniffedEvent
{
    SniffedEvent_CreatureAttackStop(uint32 guid, uint32 entry, uint32 victimGuid, uint32 victimId, std::string victimType) :
        m_guid(guid), m_entry(entry), m_victimGuid(victimGuid), m_victimId(victimId), m_victimType(victimType) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_victimGuid = 0;
    uint32 m_victimId = 0;
    std::string m_victimType;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") stops attacking " + FormatObjectName(m_victimGuid, m_victimId, m_victimType) + ".";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_ATTACK_STOP;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
    KnownObject GetTargetObject() const final
    {
        return KnownObject(m_victimGuid, m_victimId, m_victimType);
    }
};

struct SniffedEvent_CreatureMovement : SniffedEvent
{
    SniffedEvent_CreatureMovement(uint32 guid, uint32 entry, uint32 point, uint32 moveTime, float startX, float startY, float startZ, float endX, float endY, float endZ, float orientation) :
        m_guid(guid), m_entry(entry), m_point(point), m_moveTime(moveTime), m_startX(startX), m_startY(startY), m_startZ(startZ), m_endX(endX), m_endY(endY), m_endZ(endZ), m_orientation(orientation) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_point = 0;
    uint32 m_moveTime = 0;
    float m_startX = 0.0f;
    float m_startY = 0.0f;
    float m_startZ = 0.0f;
    float m_endX = 0.0f;
    float m_endY = 0.0f;
    float m_endZ = 0.0f;
    float m_orientation = 0.0f;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") moves to point " + std::to_string(m_point) + " in " + std::to_string(m_moveTime) +" ms.\n";
        txt += "Start Position: " + std::to_string(m_startX) + " " + std::to_string(m_startY) + " " + std::to_string(m_startZ) + "\n";
        txt += "End Position: " + std::to_string(m_endX) + " " + std::to_string(m_endY) + " " + std::to_string(m_endZ) + "\n";
        txt += "Final Orientation: " + std::to_string(m_orientation);

        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_MOVEMENT;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_VmangosWaypoints : SniffedEvent
{
    SniffedEvent_VmangosWaypoints(uint32 guid, uint32 point, float position_x, float position_y, float position_z, float orientation, uint32 waittime, float wander_distance, uint32 script_id, std::string comment) :
        m_guid(guid), m_point(point), m_position_x(position_x), m_position_y(position_y), m_position_z(position_z), m_orientation(orientation), m_waittime(waittime), m_wander_distance(wander_distance), m_script_id(script_id), m_comment(comment) {};
    uint32 m_guid = 0;
    uint32 m_point = 0;
    float m_position_x = 0.0f;
    float m_position_y = 0.0f;
    float m_position_z = 0.0f;
    float m_orientation = 0.0f;
    uint32 m_waittime = 0;
    float m_wander_distance = 0.0f;
    uint32 m_script_id = 0;
    std::string m_comment;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "(" + std::to_string(m_guid) + ", " + std::to_string(m_point) + ", " + std::to_string(m_position_x) + ", " + std::to_string(m_position_y) + ", " + std::to_string(m_position_z) + ", " + std::to_string(m_orientation) + ", " + std::to_string(m_waittime) + ", " + std::to_string(m_wander_distance) + ", " + std::to_string(m_script_id) + ")";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_WAYPOINT;
    }
};

struct SniffedEvent_CreatureUpdate_entry : SniffedEvent
{
    SniffedEvent_CreatureUpdate_entry(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") updates entry to " + std::to_string(m_value) + " (" + WorldDatabase::GetCreatureName(m_value) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_UPDATE_ENTRY;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_CreatureUpdate_display_id : SniffedEvent
{
    SniffedEvent_CreatureUpdate_display_id(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") updates display_id to " + std::to_string(m_value) + ".";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_UPDATE_DISPLAY_ID;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_CreatureUpdate_faction : SniffedEvent
{
    SniffedEvent_CreatureUpdate_faction(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") updates faction to " + std::to_string(m_value) + + " (" + WorldDatabase::GetFactionName(m_value) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_UPDATE_FACTION;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_CreatureUpdate_emote_state : SniffedEvent
{
    SniffedEvent_CreatureUpdate_emote_state(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") updates emote_state to " + std::to_string(m_value) + +" (" + GetEmoteName(m_value) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_UPDATE_EMOTE_STATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_CreatureUpdate_stand_state : SniffedEvent
{
    SniffedEvent_CreatureUpdate_stand_state(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") updates stand_state to " + std::to_string(m_value) + +" (" + GetStandStateName(m_value) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_UPDATE_STAND_STATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_CreatureUpdate_npc_flags : SniffedEvent
{
    SniffedEvent_CreatureUpdate_npc_flags(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") updates npc_flags to " + std::to_string(m_value) + +" (" + GetNpcFlagNames(m_value) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_UPDATE_NPC_FLAGS;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_CreatureUpdate_unit_flags : SniffedEvent
{
    SniffedEvent_CreatureUpdate_unit_flags(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") updates unit_flags to " + std::to_string(m_value) + +" (" + GetUnitFlagNames(m_value) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_UPDATE_UNIT_FLAGS;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "Creature");
    }
};

struct SniffedEvent_GameObjectCreate1 : SniffedEvent
{
    SniffedEvent_GameObjectCreate1(uint32 guid, uint32 entry, float x, float y, float z, float o) :
        m_guid(guid), m_entry(entry), m_x(x), m_y(y), m_z(z), m_o(o) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
    float m_o = 0.0f;
    std::string ToString(bool singleLine) const final
    {
        std::string txt = "GameObject " + WorldDatabase::GetGameObjectName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") becomes visible to client";
        if (singleLine)
            txt += " at " + std::to_string(m_x) + " " + std::to_string(m_y) + " " + std::to_string(m_z) + ".";
        else
            txt += ".\nPosition: " + std::to_string(m_x) + " " + std::to_string(m_y) + " " + std::to_string(m_z) + "\nOrientation: " + std::to_string(m_o);

        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_CREATE1;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "GameObject");
    }
};

struct SniffedEvent_GameObjectCreate2 : SniffedEvent
{
    SniffedEvent_GameObjectCreate2(uint32 guid, uint32 entry, float x, float y, float z, float o) :
        m_guid(guid), m_entry(entry), m_x(x), m_y(y), m_z(z), m_o(o) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
    float m_o = 0.0f;
    std::string ToString(bool singleLine) const final
    {
        std::string txt = "GameObject " + WorldDatabase::GetGameObjectName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") spawns";
        if (singleLine)
            txt += " at " + std::to_string(m_x) + " " + std::to_string(m_y) + " " + std::to_string(m_z) + ".";
        else
            txt += ".\nPosition: " + std::to_string(m_x) + " " + std::to_string(m_y) + " " + std::to_string(m_z) + "\nOrientation: " + std::to_string(m_o);

        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_CREATE2;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "GameObject");
    }
};

struct SniffedEvent_GameObjectDestroy : SniffedEvent
{
    SniffedEvent_GameObjectDestroy(uint32 guid, uint32 entry) : m_guid(guid), m_entry(entry) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "GameObject " + WorldDatabase::GetGameObjectName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") despawns or goes out range.";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_DESTROY;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "GameObject");
    }
};

struct SniffedEvent_GameObjectUpdate_flags : SniffedEvent
{
    SniffedEvent_GameObjectUpdate_flags(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "GameObject " + WorldDatabase::GetGameObjectName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") updates flags to " + std::to_string(m_value) + +" (" + GetGameObjectFlagNames(m_value) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_UPDATE_FLAGS;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "GameObject");
    }
};

struct SniffedEvent_GameObjectUpdate_state : SniffedEvent
{
    SniffedEvent_GameObjectUpdate_state(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "GameObject " + WorldDatabase::GetGameObjectName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ") updates state to " + std::to_string(m_value) + +" (" + GetGameObjectStateName(m_value) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_UPDATE_STATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, "GameObject");
    }
};

struct SniffedEvent_PlayMusic : SniffedEvent
{
    SniffedEvent_PlayMusic(uint32 music) :
        m_music(music) {};
    uint32 m_music = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Music " + std::to_string(m_music) + " starts playing.";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_PLAY_MUSIC;
    }
};

struct SniffedEvent_PlaySound : SniffedEvent
{
    SniffedEvent_PlaySound(uint32 sound, uint32 sourceGuid, uint32 sourceId, std::string sourceType) :
        m_sound(sound), m_sourceGuid(sourceGuid), m_sourceId(sourceId), m_sourceType(sourceType) {};
    uint32 m_sound = 0;
    uint32 m_sourceGuid = 0;
    uint32 m_sourceId = 0;
    std::string m_sourceType;
    std::string ToString(bool singleLine) const final
    {
        std::string txt;
        if (singleLine)
        {
            if (m_sourceId != 0)
                txt = FormatObjectName(m_sourceGuid, m_sourceId, m_sourceType) + " plays sound " + std::to_string(m_sound) + " (" + WorldDatabase::GetSoundName(m_sound) + ").";
            else
                txt = "Sound " + std::to_string(m_sound) + " (" + WorldDatabase::GetSoundName(m_sound) + ") plays.";
        }
        else
        {
            txt = "Sound " + std::to_string(m_sound) + " (" + WorldDatabase::GetSoundName(m_sound) + ") plays.";
            if (m_sourceId != 0)
                txt += " Source is " + FormatObjectName(m_sourceGuid, m_sourceId, m_sourceType) + ".";
        }
        
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_PLAY_SOUND;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_sourceGuid, m_sourceId, m_sourceType);
    }
};

struct SniffedEvent_SpellCastStart : SniffedEvent
{
    SniffedEvent_SpellCastStart(uint32 spellId, uint32 casterGuid, uint32 casterId, std::string casterType, uint32 targetGuid, uint32 targetId, std::string targetType) :
        m_spellId(spellId), m_casterGuid(casterGuid), m_casterId(casterId), m_casterType(casterType), m_targetGuid(targetGuid), m_targetId(targetId), m_targetType(targetType) {};
    uint32 m_spellId = 0;
    uint32 m_casterGuid = 0;
    uint32 m_casterId = 0;
    std::string m_casterType;
    uint32 m_targetGuid = 0;
    uint32 m_targetId = 0;
    std::string m_targetType;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = FormatObjectName(m_casterGuid, m_casterId, m_casterType) + " starts casting spell " + std::to_string(m_spellId) + " (" + WorldDatabase::GetSpellName(m_spellId);
        if (!m_targetType.empty())
            txt += ") on " + FormatObjectName(m_targetGuid, m_targetId, m_targetType) + ".";
        else
            txt += ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CAST_START;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_casterGuid, m_casterId, m_casterType);
    }
    KnownObject GetTargetObject() const final
    {
        return KnownObject(m_targetGuid, m_targetId, m_targetType);
    }
};

struct SniffedEvent_SpellCastGo: SniffedEvent
{
    SniffedEvent_SpellCastGo(uint32 spellId, uint32 casterGuid, uint32 casterId, std::string casterType, uint32 targetGuid, uint32 targetId, std::string targetType, uint32 hitTargetsCount, uint32 hitTargetsListId) :
        m_spellId(spellId), m_casterGuid(casterGuid), m_casterId(casterId), m_casterType(casterType), m_targetGuid(targetGuid), m_targetId(targetId), m_targetType(targetType), m_hitTargetsCount(hitTargetsCount), m_hitTargetsListId(hitTargetsListId) {};
    uint32 m_spellId = 0;
    uint32 m_casterGuid = 0;
    uint32 m_casterId = 0;
    std::string m_casterType;
    uint32 m_targetGuid = 0;
    uint32 m_targetId = 0;
    std::string m_targetType;
    uint32 m_hitTargetsCount = 0;
    uint32 m_hitTargetsListId;
    std::string ToString(bool singleLine) const final
    {
        std::string txt = FormatObjectName(m_casterGuid, m_casterId, m_casterType) + " casts spell " + std::to_string(m_spellId) + " (" + WorldDatabase::GetSpellName(m_spellId);
        if (m_targetId != 0)
            txt += ") on " + FormatObjectName(m_targetGuid, m_targetId, m_targetType) + ".";
        else
            txt += ").";

        if (!singleLine)
        {
            txt += "\n" + std::to_string(m_hitTargetsCount) + " targets hit: ";
            if (std::vector<KnownObject>* pTargets = SniffDatabase::GetSpellGoHitTargets(m_hitTargetsListId))
            {
                for (uint32 i = 0; i < pTargets->size(); i++)
                {
                    if (i > 0)
                        txt += ", ";
                    txt += FormatObjectName((*pTargets)[i]);
                }
            }
        }
        
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CAST_GO;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_casterGuid, m_casterId, m_casterType);
    }
    KnownObject GetTargetObject() const final
    {
        return KnownObject(m_targetGuid, m_targetId, m_targetType);
    }
};

struct SniffedEvent_QuestAccept : SniffedEvent
{
    SniffedEvent_QuestAccept(uint32 questId, uint32 objectGuid, uint32 objectId, std::string objectType) :
        m_questId(questId), m_objectGuid(objectGuid), m_objectId(objectId), m_objectType(objectType) {};
    uint32 m_questId = 0;
    uint32 m_objectGuid = 0;
    uint32 m_objectId = 0;
    std::string m_objectType;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Client accepts Quest " + std::to_string(m_questId) + " from " + FormatObjectName(m_objectGuid, m_objectId, m_objectType) + ".";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_QUEST_ACCEPT;
    }
};

struct SniffedEvent_QuestComplete : SniffedEvent
{
    SniffedEvent_QuestComplete(uint32 questId, uint32 objectGuid, uint32 objectId, std::string objectType) :
        m_questId(questId), m_objectGuid(objectGuid), m_objectId(objectId), m_objectType(objectType) {};
    uint32 m_questId = 0;
    uint32 m_objectGuid = 0;
    uint32 m_objectId = 0;
    std::string m_objectType;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Client turns in Quest " + std::to_string(m_questId) + " to " + FormatObjectName(m_objectGuid, m_objectId, m_objectType) + ".";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_QUEST_COMPLETE;
    }
};

struct SniffedEvent_CreatureInteract : SniffedEvent
{
    SniffedEvent_CreatureInteract(uint32 guid, uint32 entry) :
        m_guid(guid), m_entry(entry) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Client interacts with Creature " + WorldDatabase::GetCreatureName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_CREATURE_INTERACT;
    }
};

struct SniffedEvent_GameObjectUse : SniffedEvent
{
    SniffedEvent_GameObjectUse(uint32 guid, uint32 entry) :
        m_guid(guid), m_entry(entry) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Client uses GameObject " + WorldDatabase::GetGameObjectName(m_entry) + " (Guid: " + std::to_string(m_guid) + " Entry: " + std::to_string(m_entry) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_GAMEOBJECT_USE;
    }
};

struct SniffedEvent_ItemUse : SniffedEvent
{
    SniffedEvent_ItemUse(uint32 itemId) :
        m_itemId(itemId) {};
    uint32 m_itemId = 0;
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Client uses Item " + std::to_string(m_itemId) + " (" + WorldDatabase::GetItemName(m_itemId) + ").";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_ITEM_USE;
    }
};

struct SniffedEvent_ReclaimCorpse : SniffedEvent
{
    SniffedEvent_ReclaimCorpse() {};
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Client reclaims his corpse.";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_RECLAIM_CORPSE;
    }
};

struct SniffedEvent_ReleaseSpirit : SniffedEvent
{
    SniffedEvent_ReleaseSpirit() {};
    std::string ToString(bool /*singleLine*/) const final
    {
        std::string txt = "Client releases his spirit.";
        return txt;
    }
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_RELEASE_SPIRIT;
    }
};

#endif

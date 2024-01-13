#pragma once
#include <string>
#include <cstring>

    enum GrowPacket : int32_t {
        NET_MESSAGE_UNKNOWN,
        NET_MESSAGE_SERVER_HELLO,
        NET_MESSAGE_GENERIC_TEXT,
        NET_MESSAGE_GAME_MESSAGE,
        NET_MESSAGE_GAME_PACKET,
        NET_MESSAGE_ERROR,
        NET_MESSAGE_TRACK,
        NET_MESSAGE_CLIENT_LOG_REQUEST,
        NET_MESSAGE_CLIENT_LOG_RESPONSE
    };
    enum GrowPacketType : uint8_t {
        NET_GAME_PACKET_STATE,
        NET_GAME_PACKET_CALL_FUNCTION,
        NET_GAME_PACKET_UPDATE_STATUS,
        NET_GAME_PACKET_TILE_CHANGE_REQUEST,
        NET_GAME_PACKET_SEND_MAP_DATA,
        NET_GAME_PACKET_SEND_TILE_UPDATE_DATA,
        NET_GAME_PACKET_SEND_TILE_UPDATE_DATA_MULTIPLE,
        NET_GAME_PACKET_TILE_ACTIVATE_REQUEST,
        NET_GAME_PACKET_TILE_APPLY_DAMAGE,
        NET_GAME_PACKET_SEND_INVENTORY_STATE,
        NET_GAME_PACKET_ITEM_ACTIVATE_REQUEST,
        NET_GAME_PACKET_ITEM_ACTIVATE_OBJECT_REQUEST,
        NET_GAME_PACKET_SEND_TILE_TREE_STATE,
        NET_GAME_PACKET_MODIFY_ITEM_INVENTORY,
        NET_GAME_PACKET_ITEM_CHANGE_OBJECT,
        NET_GAME_PACKET_SEND_LOCK,
        NET_GAME_PACKET_SEND_ITEM_DATABASE_DATA,
        NET_GAME_PACKET_SEND_PARTICLE_EFFECT,
        NET_GAME_PACKET_SET_ICON_STATE,
        NET_GAME_PACKET_ITEM_EFFECT,
        NET_GAME_PACKET_SET_CHARACTER_STATE,
        NET_GAME_PACKET_PING_REPLY,
        NET_GAME_PACKET_PING_REQUEST,
        NET_GAME_PACKET_GOT_PUNCHED,
        NET_GAME_PACKET_APP_CHECK_RESPONSE,
        NET_GAME_PACKET_APP_INTEGRITY_FAIL,
        NET_GAME_PACKET_DISCONNECT,
        NET_GAME_PACKET_BATTLE_JOIN,
        NET_GAME_PACKET_BATTLE_EVENT,
        NET_GAME_PACKET_USE_DOOR,
        NET_GAME_PACKET_SEND_PARENTAL,
        NET_GAME_PACKET_GONE_FISHIN,
        NET_GAME_PACKET_STEAM,
        NET_GAME_PACKET_PET_BATTLE,
        NET_GAME_PACKET_NPC,
        NET_GAME_PACKET_SPECIAL,
        NET_GAME_PACKET_SEND_PARTICLE_EFFECT_V2,
        NET_GAME_PACKET_ACTIVE_ARROW_TO_ITEM,
        NET_GAME_PACKET_SELECT_TILE_INDEX,
        NET_GAME_PACKET_SEND_PLAYER_TRIBUTE_DATA
    };
    enum : int32_t {
        NET_GAME_PACKET_FLAGS_NONE = 0,
        NET_GAME_PACKET_FLAGS_FLYING = 1 << 1,
        NET_GAME_PACKET_FLAGS_UPDATE = 1 << 2,
        NET_GAME_PACKET_FLAGS_EXTENDED = 1 << 3,
        NET_GAME_PACKET_FLAGS_FACINGLEFT = 1 << 4,
        NET_GAME_PACKET_FLAGS_ONGROUND = 1 << 5,
        NET_GAME_PACKET_FLAGS_LAVA = 1 << 6,
        NET_GAME_PACKET_FLAGS_JUMPSOUND = 1 << 7,
        NET_GAME_PACKET_FLAGS_DEATH = 1 << 8,
        NET_GAME_PACKET_FLAGS_PUNCH = 1 << 9,
        NET_GAME_PACKET_FLAGS_PLACE = 1 << 10,
        NET_GAME_PACKET_FLAGS_TILEACTION = 1 << 11,
        NET_GAME_PACKET_FLAGS_KNOCKBACK = 1 << 12,
        NET_GAME_PACKET_FLAGS_RESPAWN = 1 << 13,
        NET_GAME_PACKET_FLAGS_PICKUPSOUND = 1 << 14,
        NET_GAME_PACKET_FLAGS_TRAMPOLINE = 1 << 15,
        NET_GAME_PACKET_FLAGS_CACTUS = 1 << 16,
        NET_GAME_PACKET_FLAGS_SLIDING = 1 << 17,
        NET_GAME_PACKET_FLAGS_JUMPPEAK = 1 << 18,
        NET_GAME_PACKET_FLAGS_FALLING_SLOWLY = 1 << 19,
        NET_GAME_PACKET_FLAGS_SWIM_SOUND = 1 << 20,
        NET_GAME_PACKET_FLAGS_WALLHANG = 1 << 21,
        NET_GAME_PACKET_FLAGS_RAYMAN_START = 1 << 22,
        NET_GAME_PACKET_FLAGS_RAYMAN_END = 1 << 23,
        NET_GAME_PACKET_FLAGS_RAYMAN_LOAD = 1 << 24,
        NET_GAME_PACKET_FLAGS_FORCE_RING = 1 << 25,
        NET_GAME_PACKET_FLAGS_CACTUS_RAPE = 1 << 26,
        NET_GAME_PACKET_FLAGS_ACID = 1 << 28
    };

#pragma pack(push, 1)
    struct TankUpdatePacket {
        int32_t m_type;
        char* m_data;
    };
#pragma pack(pop)

#pragma pack(push, 1)
    struct GameUpdatePacket {
        uint8_t m_type = 0;

        union
        {
            uint8_t m_obj_type = 0;
            uint8_t PunchEffect;
            uint8_t m_npc_type;
        };

        union
        {
            uint8_t m_count1 = 0;
            uint8_t m_jump_count;
            uint8_t m_build_range;
            uint8_t m_npc_id;
            uint8_t m_lost_item_count;
        };

        union
        {
            uint8_t m_count2 = 0;
            uint8_t m_animation_type;
            uint8_t m_punch_range;
            uint8_t m_npc_action;
            uint8_t m_particle_id;
            uint8_t m_gained_item_count;
            uint8_t m_dice_result;
            uint8_t m_fruit_count;
        };

        union
        {
            int32_t m_net_id = 0;
            int32_t m_owner_id;
            int32_t m_effect_flags_check;
            int32_t m_object_change_type;
            int32_t m_particle_emitter_id;
        };

        union
        {
            int32_t m_item = 0;
            int32_t m_ping_hash;
            int32_t m_item_net_id;
            int32_t m_pupil_color;
            int32_t m_target_net_id;
            int32_t m_tiles_length;
        };

        int32_t m_flags = 0;

        union
        {
            float m_float_var = 0;
            float m_water_speed;
            float m_obj_alt_count;
        };

        union
        {
            int32_t m_int_data = 0;
            int32_t m_ping_item;
            int32_t m_elapsed_ms;
            int32_t m_delay;
            int32_t m_tile_damage;
            int32_t m_item_id;
            int32_t m_item_speed;
            int32_t m_effect_flags;
            int32_t m_object_id;
            int32_t m_hash;
            int32_t m_verify_pos;
            int32_t m_client_hack_type;
        };

        union
        {
            float m_vec_x = 0;
            float m_pos_x;
            float m_accel;
            float m_punch_range_in;
        };

        union
        {
            float m_vec_y = 0;
            float m_pos_y;
            float m_build_range_in;
            float m_punch_strength;
        };

        union
        {
            float m_vec2_x = 0;
            float m_dest_x;
            float m_gravity_in;
            float m_speed_out;
            float m_velocity_x;
            float m_particle_variable;
            float m_particle_size;
            float m_pos2_x;
            int m_hack_type;
        };

        union
        {
            float m_vec2_y = 0;
            float m_dest_y;
            float m_speed_in;
            float m_gravity_out;
            float m_velocity_y;
            float m_particle_alt_id;
            float m_pos2_y;
            int m_hack_type2;
        };

        union
        {
            float m_particle_rotation = 0;
            float m_npc_variable;
        };

        union
        {
            uint32_t m_int_x = 0;
            uint32_t m_tile_pos_x;
            uint32_t m_item_id_alt;
            uint32_t m_hair_color;
            uint32_t m_npc_state;
        };

        union
        {
            uint32_t m_int_y = 0;
            uint32_t m_tile_pos_y;
            uint32_t m_item_count;
            uint32_t m_eye_color;
            uint32_t m_npc_speed;
            uint32_t m_particle_size_alt;
        };
        uint32_t m_data_size = 0;
        uint8_t m_data = 0;
    };
#pragma pack(pop)

    class PacketManager {
    public:
        std::string DataToString(uint8_t* data, uint32_t data_len) {
            std::string ret{};
            ret.resize(data_len - 1);
            std::memcpy((void*)ret.data(), data, data_len - 1);
            return ret;
        }
        GameUpdatePacket* DataToUpdatePacket(ENetPacket* packet) {
            if (packet->dataLength < sizeof(GameUpdatePacket) - 5)
                return nullptr;
            GameUpdatePacket* update_packet = reinterpret_cast<GameUpdatePacket*>(packet->data + 4);
            if (!(update_packet->m_flags & NET_GAME_PACKET_FLAGS_EXTENDED))
                return update_packet;
            if (packet->dataLength < update_packet->m_data_size + sizeof(GameUpdatePacket))
                return nullptr;
            return update_packet;
        }
    };
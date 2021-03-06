#pragma once
#include <Windows.h>
#include <d3dx9math.h>
#include "Memory/Memory.hpp"
#include <string>

struct player_t
{
	uintptr_t player;
	uintptr_t soldier;
	D3DXVECTOR3 origin;
	D3DXVECTOR3 head;
	bool is_visible;
	bool is_team;
	float health;
	std::string name;
	std::string held_weapon;
};

struct localplayer_t
{
	uintptr_t player;
	D3DXVECTOR3 origin;
	D3DXVECTOR2 view_angles;
	float health;
};



struct game_t
{
	uintptr_t client_game_context;
	uintptr_t player_manager;
	uintptr_t players;
	localplayer_t local_player;
};

namespace Offsets
{
	inline uintptr_t DXRENDERER = 0x142738080; //0x142572fa0;
	inline uintptr_t CLIENTGAMECONTEXT = 0x142670d80; //0x1424abd20;
	inline uintptr_t GAMERENDERER = 0x142672378; //0x1424ad330;
	inline uintptr_t ANGLES = 0x1423b2ec0; //0x1421caee0;        
	inline uintptr_t CURRENT_WEAPONFIRING = ANGLES + 0x8;
	inline uintptr_t SETTINGS = 0x1423717C0; //0x1421AC5A0;
	inline uintptr_t SHOTSTATS = 0x142737A40; //0x142572950;
	inline uintptr_t PLAYER_MANAGER = 0x60;
	inline uintptr_t LOCAL_PLAYER_ARRAY = 0x540;
	inline uintptr_t PUBLIC_PLAYER_ARRAY = 0x548;
	inline uintptr_t TEAM_ID = 0x13CC;
	inline uintptr_t SOILDER = 0x14D0;
	inline uintptr_t OCCLUDED = 0x5B1;

}

enum Bones
{
	HEAD = 104,
	NECK = 142,
	SPINE2 = 7,
	SPINE1 = 6,
	SPINE = 5,
	LEFTSHOULDER = 9,
	RIGHTSHOULDER = 109,
	LEFTELBOWROLL = 11,
	RIGHTELBOWROLL = 111,
	LEFTHAND = 15,
	RIGHTHAND = 115,
	LEFTKNEEROLL = 188,
	RIGHTKNEEROLL = 197,
	LEFTFOOT = 184,
	RIGHTFOOT = 198
};



namespace PlayerStuff
{
	inline std::string GetSoldiersWeapon(uintptr_t soldier)
	{
		uintptr_t weapon_component = M.Read<uintptr_t>(soldier + 0x0570);

		if (!weapon_component)
			return "";

		uintptr_t weapon_handle = M.Read<uintptr_t>(weapon_component + 0x0890);
		uint32_t active_slot = M.Read<uint32_t>(weapon_component + 0x0A98);

		if (weapon_handle)
		{
			uintptr_t soldier_weapon = M.Read<uintptr_t>(weapon_handle + active_slot * 0x8);

			if (!soldier_weapon)
				return "";

			uintptr_t weapon_data = M.Read<uintptr_t>(soldier_weapon + 0x0030);

			if (!weapon_data)
				return "";

			uintptr_t weapon = M.Read<uintptr_t>(weapon_data + 0x0130);

			//uintptr_t weapon_name_ptr = M.Read<uintptr_t>(weapon_data + 0x0130);
			std::string restult = M.ReadString(weapon);
			return restult;
		}
		else
			return "";
		
	}

	inline std::string GetPlayersName(uintptr_t player)
	{
		std::string name = M.ReadString(player + 0x40);

		return name;
	}

	constexpr std::array<std::array<Bones, 2>, 12> bone_list =
	{
		{{HEAD, NECK}, {NECK, LEFTSHOULDER}, {LEFTSHOULDER, LEFTELBOWROLL}, {LEFTELBOWROLL, LEFTHAND},
		{NECK, RIGHTSHOULDER}, {RIGHTSHOULDER, RIGHTELBOWROLL}, {RIGHTELBOWROLL, RIGHTHAND}, { NECK, SPINE},
		{SPINE, LEFTKNEEROLL}, {SPINE, RIGHTKNEEROLL}, {LEFTKNEEROLL, LEFTFOOT}, {RIGHTKNEEROLL, RIGHTFOOT}}
	};
}

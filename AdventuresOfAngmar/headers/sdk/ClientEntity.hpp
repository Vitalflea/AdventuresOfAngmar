#pragma once

class unk4 {
public:
	PAD(0x80);
	std::uint32_t m_experience;
};

class unk3 {
public:
	PAD(0xC);
	unk4* m_unk4;
};

class unk2 {
public:
	PAD(0x24);
	unk3* m_unk3;
};

class unk1 {
public:
	PAD(0x50);
	unk2* m_unk2;
};

class Player {
public:
	
	std::uint32_t m_id; // 0x0 // 0xBC5FB8 is the local player i believe
	PAD(0x2B); //0x4
	std::uint8_t m_instance; //0x2F
	PAD(0x44); //0x30
	std::uint8_t m_base_x; // 0x74
	std::uint8_t m_base_y; // 0x75
	PAD(0x6); // 0x76
	Vector3 m_origin; // 0x7C
	PAD(0x20); // 0x80
	std::uint8_t m_unk1; //0xA0 // idk but its checking for something, we dont want 0xFF
	PAD(0x7); //0xA1
	std::uint64_t m_unk2; //0xA8 // i think these are another set of coords
	std::uint32_t m_unk3; //0xB0 // i think these are another set of coords

	void SetPlayerPos(class PlayerGeometry* a2) {

		using fSetPlayerPos = int(__thiscall*)(class Player* ecx, class PlayerGeometry* a2, int a3);
		static fSetPlayerPos set_player_pos = (fSetPlayerPos)g_set_player_position;

		using fSendPlayerPos = unsigned int(__thiscall*)(class Player* ecx);
		static fSendPlayerPos send_player_pos = (fSendPlayerPos)g_send_player_pos;

		set_player_pos(this, a2, 0);
		send_player_pos(this);
	}
};

class ClientEntity {
public:
	PAD(0x4); //0x0
	Player* m_player; //0x4
	PAD(0x3C); //0x8
	unk1* unk1; //0x48 // for accessing experience. likely contains a lot more neat things
	PAD(0x14); //0x4C
	std::uint32_t m_unk2; // 0x60 // something important used in pl.dll
	PAD(0x2C); // 0x64
	std::uint32_t m_player_id; //0x90
	std::uint32_t m_player_id_short; //0x94

	static ClientEntity* GetLocalEntity() {

		static ClientEntity* address = 0;

		if (address == 0) {

			auto pl_base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(g_pl_dll));
			address = *reinterpret_cast<ClientEntity**>(pl_base + g_game_pointer);
		}

		return address;
	}
};
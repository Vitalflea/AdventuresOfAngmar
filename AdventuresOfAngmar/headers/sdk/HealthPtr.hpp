#pragma once

class HealthPtr5 {
public:
	PAD(0x28);
	float m_health; //0x28
	float m_max_health; //0x2C
	PAD(0x74); //0x30
	float m_mana; //0xA8
	float m_max_mana; //0xAC
};

class HealthPtr4 {
public:
	PAD(0x24);
	HealthPtr5* m_unk5;
};

class HealthPtr3 {
public:
	HealthPtr4* m_unk4;
};

class HealthPtr2 {
public:
	HealthPtr3* m_unk3;
};

class HealthPtr1 {
public:
	PAD(0x4); //0x0
	HealthPtr2* m_unk2;
};

class HealthPtr {
public:
	PAD(0x8); //0x0
	HealthPtr1* m_unk1;

	static HealthPtr* Get() {

		static HealthPtr* address = 0;

		if (address == 0) {

			auto pl_base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(g_pl_dll));
			address = *reinterpret_cast<HealthPtr**>(pl_base + g_game_pointer);
		}

		return address;
	}
};
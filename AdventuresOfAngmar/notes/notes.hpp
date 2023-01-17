#pragma once

// used for getting the local players yaw, and not the cameras
class GameClient2 {
public:
	PAD(0x68);
	float m_yaw;

	static GameClient2* Get() {

		static GameClient2* address = 0;

		if (address == 0) {

			auto exe_base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(g_exe));
			address = *reinterpret_cast<GameClient2**>(exe_base + g_game_pointer2);
		}

		return address;
	}
};

max player coordinate length
MAX_SIZE = 160

scale factor
F = 200

coords origin
ORIGIN_X = 29360
ORIGIN_Y = 24880

formula for getting developer position of the local player
X = (bx/8) * MAX_SIZE + ox
Y = (by/8) * MAX_SIZE + oy

formula for getting the player position(like the coordinates seen on the map
X = ( DEV_X – ORIGIN_X ) / F
Y = ( DEV_Y – ORIGIN_Y ) / F

formula for getting dev pos from map coords
X = PLAYER_X * F
Y = PLAYER_Y * F
#pragma once

class ClientCamera {
public:
	PAD(0x518); //0x0
	float m_fov; //0x518
	PAD(0x24); //0x51C
	float m_yaw; //0x540
	PAD(0xC); //0x544
	float m_pitch; //0x550

	static ClientCamera* Get() {

		static ClientCamera* address = 0;

		if (address == 0) {

			auto exe_base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(g_exe));
			address = *reinterpret_cast<ClientCamera**>(exe_base + g_camera_ptr);
		}

		return address;
	}
};
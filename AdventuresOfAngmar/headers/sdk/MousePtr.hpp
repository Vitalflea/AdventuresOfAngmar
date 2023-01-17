#pragma once

class MousePtr {

	PAD(0x4); //0x0
	POINT m_screen_pos; //0x4

	static MousePtr* Get() {

		static MousePtr* address = 0;

		if (address == 0) {

			auto exe_base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(g_exe));
			address = *reinterpret_cast<MousePtr**>(exe_base + g_mouse_ptr);
		}

		return address;
	}
};
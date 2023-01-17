#pragma once

class ClientScreen {
public:
	PAD(0x40); //0x0
	std::uint32_t m_width; //0x40
	std::uint32_t m_height; //0x44

	static ClientScreen* Get() {

		static ClientScreen* address = 0;

		if (address == 0) {

			auto exe_base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(g_exe));
			address = *reinterpret_cast<ClientScreen**>(exe_base + g_screen_ptr);
		}

		return address;
	}
};
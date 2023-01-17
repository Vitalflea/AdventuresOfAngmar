#pragma once

class PlayerGeometry {
public:
	PAD(0x8);
	std::uint8_t m_base_x; //0x8
	std::uint8_t m_base_y; //0x9
	PAD(0x6); //0xA
	Vector3 m_origin; //0x10
	PAD(0x28); //0x1C
};
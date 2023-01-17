#pragma once

class Vector3 {
public:
	float m_x, m_y, m_z;
	inline Vector3 operator+(const Vector3& v) { return Vector3(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z); }
	inline Vector3 operator*(const float& v) { return Vector3(m_x * v, m_y * v, m_z * v); }
	inline bool operator==(const Vector3& v) { return m_x == v.m_x && m_y == v.m_y && m_z == v.m_z; }
	bool IsValid() { return std::isfinite(this->m_x) && std::isfinite(this->m_y) && std::isfinite(this->m_z); }
}; 
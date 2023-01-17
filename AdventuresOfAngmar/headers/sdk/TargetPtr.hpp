#pragma once

class TargetPtr3 {
public:
	PAD(0x230);
	ClientEntity* m_target;
};

class TargetPtr2 {
public:
	TargetPtr3* unk2;
};

class TargetPtr {
public:

	ClientEntity* GetTargetEntity() {

		ClientEntity* target{ nullptr };

		if (this->unk1 != nullptr) {

			auto unk2 = this->unk1->unk2;
			if (unk2 != nullptr) {

				target = unk2->m_target;
			}
		}

		return target;
	}

	static TargetPtr* Get() {

		static TargetPtr* address{ nullptr };

		if (address == nullptr) {
			auto exe_base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(g_exe));
			address = *reinterpret_cast<TargetPtr**>(exe_base + g_target_ptr);
		}

		return address;
	}
	
private:
	TargetPtr2* unk1;
	
};

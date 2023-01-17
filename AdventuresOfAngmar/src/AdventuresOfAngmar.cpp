#include <Windows.h>
#include <MinHook.h>

#include <iostream>

#include "sdk/sdk.hpp"

float speed = 0.545f;

void* g_original{ nullptr };

Vector3 g_last_server_pos{};
bool g_is_flying{ false };

int __fastcall sub_568A30(Player* ecx, void* edx, PlayerGeometry* a2, int a3)
{
	auto local = ClientEntity::GetLocalEntity();
	if (local != nullptr) {

		auto local_player = local->m_player;
		if (local_player != nullptr && local_player == ecx) {

			g_last_server_pos = a2->m_origin;

			auto client_camera = ClientCamera::Get();
			auto target = TargetPtr::Get();

			if (GetAsyncKeyState('Y')) {

				float pitchRadian = DEG2RAD(client_camera->m_pitch);
				float yawRadian = DEG2RAD(client_camera->m_yaw);

				float newPosX = speed * -sinf(yawRadian);
				float newPosZ = speed * sinf(pitchRadian);
				float newPosY = speed * cosf(yawRadian);

				Vector3 Movement{ newPosX, newPosY, newPosZ };
				a2->m_origin = a2->m_origin + Movement;
			}
#pragma region test
			// defunct
			 
			if (GetAsyncKeyState('U')) {

				auto current_target = target->GetTargetEntity();
				if (current_target != nullptr) {

					auto target_entity = current_target->m_player;
					if (target_entity != nullptr) {
			
						if (target_entity->m_origin.IsValid()) {

							a2->m_base_x = target_entity->m_base_x;
							a2->m_base_y = target_entity->m_base_y;
							a2->m_origin = target_entity->m_origin;
						}
					}
				}
			}
#pragma endregion 
		}
	}

	return reinterpret_cast<decltype(&sub_568A30)>(g_original)(ecx, edx, a2, a3);
}

DWORD WINAPI Attach(void* module) {

	AllocConsole();

	FILE* output{ nullptr };
	freopen_s(&output, "CONOUT$", "w", stdout);

	MH_Initialize();

	auto oo = MH_CreateHook(reinterpret_cast<void*>(g_set_player_position), sub_568A30, reinterpret_cast<void**>(&g_original));
	
	MH_EnableHook(MH_ALL_HOOKS);

	auto local = ClientEntity::GetLocalEntity();
	auto client_camera = ClientCamera::Get();

	while (true) {

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		if (local != nullptr && client_camera != nullptr) {

			auto local_player = local->m_player;

			if (local_player != nullptr && client_camera->m_fov != 70.0f) {
				client_camera->m_fov = 70.0f;
			}
		}
	}

	FreeLibraryAndExitThread(static_cast<HMODULE>(module), 0);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {

	UNREFERENCED_PARAMETER(reserved);

	DisableThreadLibraryCalls(module);

	if (reason == DLL_PROCESS_ATTACH) {

		auto thread = CreateThread(nullptr, 0, Attach, module, 0, nullptr);
		if (thread) {

			CloseHandle(thread);
		}
	}

	return TRUE;
}






/*
#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <Windows.h>
#include <MinHook.h>
#include <intrin.h>

#include <vector>
#include <iostream>

#include "sdk/sdk.hpp"

float speed = 0.05f;

void* g_set_player_pos_original{ nullptr };
void* g_send_original{ nullptr };
void* g_send_to_original{ nullptr };

Vector3 g_last_client_pos{};
Vector3 g_last_server_pos{};
bool g_is_flying{ false };

std::vector<std::uintptr_t> g_black_list{};
int WINAPI hook_WSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const sockaddr* to, int uh, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	//auto return_address = reinterpret_cast<std::uintptr_t>(_AddressOfReturnAddress());
	//if (GetAsyncKeyState('K') & 0x8000) {

	//	g_black_list.push_back(return_address);
	//}
	//if (GetAsyncKeyState('W') & 0x8000) {

	//	bool good{ true };
	//	for (auto address : g_black_list) {
	//		if (address == return_address) {
	//			good = false;
	//		}
	//	}
	//	if (good == true) {

	//		for (int i = 0; i < lpBuffers->len; i++) {

	//			//printf_s("%i", lpBuffers->buf[i]);
	//			std::cout << (std::uint16_t)lpBuffers->buf[i] << ' ';
	//		}

	//		std::cout << '\n';
	//	}
	//}

	return reinterpret_cast<decltype(&hook_WSASend)>(g_send_to_original)(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, to, uh, lpOverlapped, lpCompletionRoutine);
}

int __fastcall sub_568A30(Player* ecx, void* edx, PlayerGeometry* a2, int a3)
{
	auto local = ClientEntity::GetLocalEntity();
	if (local != nullptr) {

		auto local_player = local->m_player;
		if (local_player != nullptr && local_player == ecx) {
			//std::cout << local_player << '\n';
		}
		//
		//			if (g_is_flying == true && a2->m_origin == g_last_server_pos) {
		//				a2->m_origin = g_last_client_pos;
		//				reinterpret_cast<decltype(&sub_568A30)>(g_original)(ecx, edx, a2, a3);
		//				return 4;
		//			}
		//
		//			g_last_server_pos = a2->m_origin;
		//#pragma region test
		//			// defunct
		//
		//			//if (GetAsyncKeyState('Y') & 0x8000) {
		//
		//			//	auto current_target = target->GetTargetEntity();
		//			//	if (current_target != nullptr) {
		//
		//			//		auto target_entity = current_target->m_player;
		//			//		if (target_entity != nullptr) {
		//
		//			//			if (target_entity->m_origin.IsValid()) {
		//
		//			//				a2->m_base_x = target_entity->m_base_x;
		//			//				a2->m_base_y = target_entity->m_base_y;
		//			//				a2->m_origin = target_entity->m_origin;
		//			//			}
		//			//		}
		//			//	}
		//			//}
		//#pragma endregion
		//		}
		//	}

	}
	return reinterpret_cast<decltype(&sub_568A30)>(g_set_player_pos_original)(ecx, edx, a2, a3);
}

DWORD WINAPI Attach(void* module) {

	AllocConsole();

	FILE* output{ nullptr };
	freopen_s(&output, "CONOUT$", "w", stdout);

	MH_Initialize();

	auto oo = MH_CreateHook(reinterpret_cast<void*>(g_set_player_position), sub_568A30, reinterpret_cast<void**>(&g_set_player_pos_original));
	//oo = MH_CreateHook(reinterpret_cast<void*>(g_send), sub_ADB610, reinterpret_cast<void**>(&g_send_original));
	oo = MH_CreateHook(reinterpret_cast<void*>(WSASendTo), hook_WSASend, reinterpret_cast<void**>(&g_send_to_original));

	MH_EnableHook(MH_ALL_HOOKS);

	auto local = ClientEntity::GetLocalEntity();
	auto client_camera = ClientCamera::Get();

	while (true) {

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		if (local != nullptr && client_camera != nullptr) {

			auto local_player = local->m_player;

			if (local_player != nullptr && client_camera->m_fov != 70.0f) {
				client_camera->m_fov = 70.0f;
			}

			auto client_camera = ClientCamera::Get();
			auto target = TargetPtr::Get();

			if (GetAsyncKeyState(VK_MBUTTON) & 0x8000) {

				g_is_flying = true;
				float pitchRadian = DEG2RAD(client_camera->m_pitch);
				float yawRadian = DEG2RAD(client_camera->m_yaw);

				float newPosX = speed * -sinf(yawRadian);
				float newPosZ = speed * sinf(pitchRadian);
				float newPosY = speed * cosf(yawRadian);

				Vector3 Movement{ newPosX, newPosY, newPosZ };
				PlayerGeometry geometry{};
				geometry.m_origin = local_player->m_origin + Movement;
				geometry.m_base_x = local_player->m_base_x;
				geometry.m_base_y = local_player->m_base_y;

				local_player->SetPlayerPos(&geometry);
			}
			else {

				g_is_flying = false;
			}
		}
	}

	FreeLibraryAndExitThread(static_cast<HMODULE>(module), 0);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {

	UNREFERENCED_PARAMETER(reserved);

	DisableThreadLibraryCalls(module);

	if (reason == DLL_PROCESS_ATTACH) {

		auto thread = CreateThread(nullptr, 0, Attach, module, 0, nullptr);
		if (thread) {

			CloseHandle(thread);
		}
	}

	return TRUE;
}




*/
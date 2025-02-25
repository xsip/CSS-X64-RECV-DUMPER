#include <Windows.h>
#include "memory.h"
#include <tchar.h>
#include "Client.h"


int main(int argc, char* argv[]) {
	auto steamApi = LoadLibrary(_T("D:\\SteamLibrary\\steamapps\\common\\Counter-Strike Source\\bin\\x64\\steam_api64.dll"));
	if (steamApi == NULL) {
		auto err = GetLastError();
		printf("0x%x\n", err);
	}
	auto tier0 = LoadLibrary(_T("D:\\SteamLibrary\\steamapps\\common\\Counter-Strike Source\\bin\\x64\\tier0.dll"));
	if (tier0 == NULL) {
		auto err = GetLastError();
		printf("0x%x\n", err);
	}
	auto vstdlib  = LoadLibrary(_T("D:\\SteamLibrary\\steamapps\\common\\Counter-Strike Source\\bin\\x64\\vstdlib.dll"));
	if (vstdlib  == NULL) {
		auto err = GetLastError();
		printf("0x%x\n", err);
	}
	auto client = LoadLibrary(_T("D:\\SteamLibrary\\steamapps\\common\\Counter-Strike Source\\cstrike\\bin\\x64\\client.dll"));
	if (client == NULL) {
		auto err = GetLastError();
		printf("0x%x\n", err);
	}

	typedef uintptr_t (*CreateInterface)(const char* interfaceName, int unknown);

	CreateInterface createInterface = (CreateInterface)GetProcAddress(client, "CreateInterface");
	auto vClient017 = (VClient017*)createInterface("VClient017", NULL);
	printf("vClient017: 0x%p\n", vClient017);
	auto classes = vClient017->GetAllClasses();
	printf("%s\n", classes->m_pNetworkName);
	printf("%s\n", classes->m_pNext->m_pNetworkName);
	return 0;
	g_Memory.Initialize("cstrike_win64.exe");
	auto pClient = g_Memory.GetModuleAddress("client.dll");

	return 0;
}
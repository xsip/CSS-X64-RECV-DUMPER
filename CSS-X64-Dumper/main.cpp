#include <Windows.h>
#include "memory.h"
#include "ClientClassEx.h"

void PrintArrayProperties(CRecvPropEx* prop) {
	if (strstr(prop->GetArrayProp()->GetType().c_str(), "class"))
		printf("\t\t\tHas Props: %s | GetType: %s | Offset: 0x%x\n", prop->GetArrayProp()->GetName().c_str(), prop->GetArrayProp()->GetDataTable()->GetNetTableName(), prop->GetArrayProp()->GetOffset());
	else
		printf("\t\t\tHas Props: %s | GetType: %s | Offset: 0x%x\n", prop->GetArrayProp()->GetName().c_str(), prop->GetType().c_str(), prop->GetArrayProp()->GetOffset());
	if (strstr(prop->GetArrayProp()->GetType().c_str(), "class")) {
		printf("\t\t\tClass: %s\n", prop->GetArrayProp()->GetDataTable()->GetNetTableName().c_str());
	}
}

std::string GetRealType(CRecvPropEx* prop) {
	if (strstr(prop->GetArrayProp()->GetType().c_str(), "class"))
		return prop->GetArrayProp()->GetDataTable()->GetNetTableName();
	else if(strstr(prop->GetArrayProp()->GetType().c_str(), "[]")) {
		return GetRealType(prop->GetArrayProp());
	}
	return prop->GetArrayProp()->GetType().c_str();
}
void DumpProperties(CRecVTableEx* t, bool dumpOffsets) {
	for (int i = 0; i < t->GetPropCount(); i++) {
		auto prop = t->GetPropAtIndex(i);
		if (strstr(prop->GetName().c_str(), "baseclass") && !strstr(prop->GetDataTable()->GetPropAtIndex(0)->GetDataTable()->GetNetTableName().c_str(), "invalid")) {
			printf("\t\tParent: %s\n", prop->GetDataTable()->GetPropAtIndex(0)->GetDataTable()->GetNetTableName().c_str());
			DumpProperties(prop->GetDataTable(), false);
		} else if (!strstr(prop->GetName().c_str(), "baseclass")) {
			if(strstr(prop->GetType().c_str(),"class"))
				printf("\t\tProp: %s => 0x%x | %s \n", prop->GetName().c_str(), prop->GetOffset(), prop->GetDataTable()->GetNetTableName().c_str());
			else if (strstr(prop->GetType().c_str(), "[]")) {
				printf("\t\tProp: %s => 0x%x | %s[%i] \n", prop->GetName().c_str(), prop->GetOffset(), GetRealType(prop).c_str(), prop->GetNumberOfElements());
				// PrintArrayProperties(prop);
			}
			else {
				printf("\t\tProp: %s => 0x%x | %s \n", prop->GetName().c_str(), prop->GetOffset(), prop->GetType().c_str());

			}
		}
	}
}

int main(int argc, char* argv[]) {
	g_Memory.Initialize("cstrike_win64.exe");
	auto pClient = g_Memory.GetModuleAddress("client.dll");
	auto c = g_Memory.Read<ClientClassEx*>(pClient.m_uAddress + 0x6084D8);

	while (c) {
		auto networkName = c->GetNetworkName();
		// if (strstr(networkName.c_str(), "CBasePlayer")) {
		printf("%s\n", networkName.c_str());
		DumpProperties(c->GetRecVTable(), true);
		if (strstr(networkName.c_str(), "invalid")) {
			c = nullptr;
			continue;
		}
		c = c->GetNext();

	}
	return 0;
}
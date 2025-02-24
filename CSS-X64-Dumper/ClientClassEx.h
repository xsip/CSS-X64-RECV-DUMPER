#pragma once

#include "memory.h"
class CRecVTableEx;

class CRecvPropEx {
public:
	CRecvPropEx() {

	}

	inline std::string GetName() {
		return g_Memory.ReadString(g_Memory.Read<uintptr_t>((uintptr_t)this));
	}

	inline DWORD GetOffset() {
		return g_Memory.Read<DWORD>((uintptr_t)this +0x48);
	}

	inline std::string GetType() {
		int type = g_Memory.Read<int>((uintptr_t)this + 0x8);
		switch (type) {
		case 0:
			return "int";
		case 1:
			return "float";
		case 2:
			return "Vector";
		case 3:
			return "Vector2D";
		case 4:
			return "char*";
		case 5:
			return "[]";
		case 6:
			return "class";
		default:
		case 7:
			return "unknown";
		
		}
	}

	inline CRecVTableEx* GetDataTable() {
		return g_Memory.Read<CRecVTableEx*>((uintptr_t)this + 0x40);
	}
	inline int GetElementStride() {
		return g_Memory.Read<int>((uintptr_t)this + 0x4C);
	}
	inline int GetNumberOfElements() {
		return g_Memory.Read<int>((uintptr_t)this + 0x50);
	}
	inline CRecvPropEx* GetArrayProp(int idx = 0) {
		return g_Memory.Read<CRecvPropEx*>((uintptr_t)this + (0x20)) + 0x60*idx;
	}

};

class CRecVTableEx {
public:
	CRecVTableEx() {

	}

	inline int GetPropCount() {
		return g_Memory.Read<int>((uintptr_t)this + 0x8);
	}
	
	inline std::string GetNetTableName() {
		return g_Memory.ReadString(g_Memory.Read<uintptr_t>((uintptr_t)this + 0x18));
	}

	inline CRecvPropEx* GetPropAtIndex(int idx) {
			return g_Memory.Read<CRecvPropEx*>((uintptr_t)this) + (0x60 * idx);
	}

};

class ClientClassEx {
public:
	ClientClassEx() {

	}

	inline std::string GetNetworkName() {
		return g_Memory.ReadString(g_Memory.Read<uintptr_t>((uintptr_t)this + 0x10));
	}
	inline CRecVTableEx *GetRecVTable() {
		return g_Memory.Read<CRecVTableEx*>((uintptr_t)this + 0x18);
	}

	inline ClientClassEx* GetNext() {
		return g_Memory.Read<ClientClassEx*>((uintptr_t)this + 0x20);
	}

};
#include "pch.h"
#include "Debug.h"

void Debug::Log(const std::wstring& log)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWriten;
	DWORD size = static_cast<DWORD>(wcslen(log.c_str()));
	WriteConsole(handle, log.c_str(), size, &dwBytesWriten, 0);
	WriteConsole(handle, _T("\n"), 1, &dwBytesWriten, 0);
}

void Debug::Log(const D3DXVECTOR3& v)
{
	char str[64];
	std::snprintf(str, sizeof(str), "(%.3f, %.3f, %.3f)", v.x, v.y, v.z);
	std::wstring result(str, &str[sizeof(str)]);
	Log(result);
}

void Debug::Log(const D3DXQUATERNION& q)
{
	char str[64];
	std::snprintf(str, sizeof(str), "(%.3f, %.3f, %.3f, %.3f)", q.x, q.y, q.z, q.w);
	std::wstring result(str, &str[sizeof(str)]);
	Log(result);
}

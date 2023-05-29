#pragma once

class Debug
{
public:
	Debug() = delete;
	Debug(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;
	~Debug() = delete;

public:
	static void Log(const std::wstring& log);
	static void Log(const D3DXVECTOR3& v);
	static void Log(const D3DXQUATERNION& q);
};


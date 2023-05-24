#pragma once

class DXContext
{
public:
	friend class GameEngine;

public:
	DXContext() = delete;
	DXContext(const DXContext&) = delete;
	DXContext& operator=(DXContext&&) = delete;
	~DXContext() = delete;

public:
	static IDirect3DDevice9* GetDevice();

private:
	static bool init(const HWND hWnd, const int width, const int height, const bool bWindowed);
	static void release();

private:
	static bool mbInit;
	static IDirect3DDevice9* mD3DDevice;
};


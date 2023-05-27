#pragma once

class RenderEngine
{
public:
	friend class GameEngine;

public:
	RenderEngine() = delete;
	RenderEngine(const RenderEngine&) = delete;
	RenderEngine& operator=(RenderEngine&&) = delete;
	~RenderEngine() = delete;

public:
	static D3DCOLOR GetBackgroundColor();

	static void SetBackgroundColor(const D3DCOLOR color);

private:
	static bool init(const HWND hWnd, const int width, const int height, const bool bWindowed);
	static void release();

	static void preRender();
	static void render();
	static void postRender();

private:
	static bool mbInit;
	static int mWidth;
	static int mHeight;
	static IDirect3DDevice9* mD3DDevice;
	static D3DCOLOR mBackgroundColor;
};


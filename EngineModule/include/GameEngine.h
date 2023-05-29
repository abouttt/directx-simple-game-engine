#pragma once

class GameEngine
{
public:
	GameEngine() = delete;
	GameEngine(const GameEngine&) = delete;
	GameEngine& operator=(GameEngine&&) = delete;
	~GameEngine() = delete;

public:
	static bool Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed);
	static void Release();
	static void OnTick();

private:
	static void loadResources();

private:
	static bool mbInit;
};


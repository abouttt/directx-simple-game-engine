#include "pch.h"
#include "GameEngine.h"
#include "WindowsPlayer.h"
#include "WindowsUtil.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow)
{
	if (!wndplayer::InitWindowsApp(hInstance, wndplayer::gWidth, wndplayer::gHeight))
	{
		return 0;
	}

	if (!GameEngine::Init(hInstance, wndplayer::gWndHandler, wndplayer::gWidth, wndplayer::gHeight, true))
	{
		return 0;
	}

	wndutil::Show(wndplayer::gWndHandler);
	wndutil::SetCenterWindow(wndplayer::gWndHandler);

	while (wndplayer::Tick())
	{
		GameEngine::Tick();
	}

	GameEngine::Release();
	wndplayer::Destroy();

	return 0;
}
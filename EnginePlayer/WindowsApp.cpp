#include "pch.h"
#include "GameEngine.h"
#include "WindowsPlayer.h"
#include "WindowsUtil.h"
#include "Time.h"
#include "SceneManager.h"
#include "DevScene.h"

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

	SceneManager::CreateScene<DevScene>(_T("DevScene"));
	SceneManager::LoadScene(_T("DevScene"));

	wndutil::Show(wndplayer::gWndHandler);
	wndutil::SetCenterWindow(wndplayer::gWndHandler);

	static float previousTimer = 0.f;
	static float updatePeriod = 500.f;
	while (wndplayer::Tick())
	{
		GameEngine::OnTick();
		
		float currentTime = Time::GetElapsedTime();
		if (currentTime - previousTimer > updatePeriod)
		{
			float fps = Time::GetFPS();
			wndplayer::SetWindowsStatTitle(fps);
			previousTimer = currentTime;
		}
	}

	GameEngine::Release();
	wndplayer::Destroy();

	return 0;
}
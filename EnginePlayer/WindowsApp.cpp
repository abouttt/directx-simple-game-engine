#include "pch.h"
#include "WindowsPlayer.h"
#include "WindowsUtil.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow)
{
	if (!wndplayer::InitWindowsApp(hInstance, wndplayer::gWidth, wndplayer::gHeight))
	{
		::MessageBox(nullptr, _T("WinMain/InitWindowsApp : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	wndutil::Show(wndplayer::gWndHandler);
	wndutil::SetCenterWindow(wndplayer::gWndHandler);

	while (wndplayer::Tick())
	{

	}

	wndplayer::Destroy();

	return 0;
}
#include "pch.h"
#include "WindowsPlayer.h"

namespace wndplayer
{
	HINSTANCE gInstance = nullptr;
	HWND gWndHandler = nullptr;

	const TCHAR* gClassName = _T("D3D_GAME_ENGINE");
	TCHAR gTitle[64] = _T("D3D GAME ENGINE");
	TCHAR gPlayTitle[128];

	int gWidth = 800;
	int gHeight = 640;

	LRESULT WndProc(const HWND hWnd, const UINT32 msg, const WPARAM wParam, const LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
		{
			DestroyWindow(hWnd);
			return 0;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}

		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

	bool InitWindowsApp(const HINSTANCE hInstance, const int width, const int height)
	{
		gInstance = hInstance;

		WNDCLASS wc;
		::ZeroMemory(&wc, sizeof(wc));

		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = gInstance;
		wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = ::LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = gClassName;

		if (!::RegisterClass(&wc))
		{
			::MessageBox(nullptr, _T("InitWindowsApp/RegisterClass : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		RECT rect{ 0, 0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		int windowWidth = rect.right - rect.left;
		int windowHeight = rect.bottom - rect.top;

		gWndHandler = ::CreateWindow(
			gClassName, gTitle,
			WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
			0, 0, windowWidth, windowHeight,
			NULL /*parent hwnd*/, NULL /* menu */, gInstance, NULL /*extra*/);

		if (!gWndHandler)
		{
			::MessageBox(nullptr, _T("InitWindowsApp/CreateWindow : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		return true;
	}

	bool Tick()
	{
		MSG msg;
		::ZeroMemory(&msg, sizeof(msg));

		while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			::DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				return false;
			}
		}

		return true;
	}

	void Destroy()
	{
		DestroyWindow(gWndHandler);
	}

	void SetWindowsStatTitle(float frameFPS)
	{
		_stprintf_s(gPlayTitle, _T("%s  [%.2f fps]"), gTitle, frameFPS);
		::SetWindowText(gWndHandler, gPlayTitle);
	}
}
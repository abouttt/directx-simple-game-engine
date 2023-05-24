#pragma once

#include "pch.h"

namespace wndutil
{
	void GetWindowSize(const HWND hWnd, float* const outWidth, float* const outHeight)
	{
		assert(outWidth);
		assert(outHeight);

		RECT rect;
		GetClientRect(hWnd, &rect);
		*outWidth = static_cast<float>(rect.right - rect.left);
		*outHeight = static_cast<float>(rect.bottom - rect.top);
	}

	void Show(const HWND hWnd)
	{
		::ShowWindow(hWnd, SW_SHOW);
		::SetForegroundWindow(hWnd);
		::SetFocus(hWnd);
	}

	void SetCenterWindow(const HWND hWnd)
	{
		// �θ� �Ǵ� ȭ�� ����� ���´�.
		RECT rc, rcOwner, rcWindow;
		HWND ownerHandle = GetDesktopWindow();
		GetWindowRect(ownerHandle, &rcOwner);
		GetWindowRect(hWnd, &rcWindow);
		CopyRect(&rc, &rcOwner);

		OffsetRect(&rcWindow, -rcWindow.left, -rcWindow.top);
		OffsetRect(&rc, -rc.left, -rc.top);
		OffsetRect(&rc, -rcWindow.right, -rcWindow.bottom);

		SetWindowPos(hWnd, HWND_TOP,
			rcOwner.left + (rc.right / 2),
			rcOwner.top + (rc.bottom / 2),
			0, 0,
			SWP_NOSIZE);
	}
}
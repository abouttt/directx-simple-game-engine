#include "pch.h"
#include "Input.h"

bool Input::mbInit = false;
IDirectInput8* Input::mInput = nullptr;
IDirectInputDevice8* Input::mKeyboard = nullptr;
IDirectInputDevice8* Input::mMouse = nullptr;
std::array<unsigned char, 256> Input::mKeyboardKeys;
std::array<Input::State, 256> Input::mKeyboardState;
DIMOUSESTATE Input::mMouseButtons;
std::array<Input::State, 4> Input::mMouseState;

bool Input::GetKey(const unsigned int key)
{
	return mKeyboardState[key].bPressing;
}

bool Input::GetKeyDown(const unsigned int key)
{
	return mKeyboardState[key].bPressed;
}

bool Input::GetKeyUp(const unsigned int key)
{
	return mKeyboardState[key].bUp;
}

bool Input::GetMouseButton(const int button)
{
	return mMouseState[button].bPressing;
}

bool Input::GetMouseButtonDown(const int button)
{
	return mMouseState[button].bPressed;
}

bool Input::GetMouseButtonUp(const int button)
{
	return mMouseState[button].bUp;
}

LONG Input::GetAxisMouseX()
{
	return mMouseButtons.lX;
}

LONG Input::GetAxisMouseY()
{
	return mMouseButtons.lY;
}

LONG Input::GetAxisMouseZ()
{
	return mMouseButtons.lZ;
}

void Input::GetMousePosition(int* const outMouseX, int* const outMouseY)
{
	assert(outMouseX);
	assert(outMouseY);

	*outMouseX = mMouseButtons.lX;
	*outMouseY = mMouseButtons.lY;
}

void Input::update()
{
	keyboardUpdate();
	mouseUpdate();
}

void Input::keyboardUpdate()
{
	if (!readKeyboard())
	{
		return;
	}

	for (int i = 0; i < 256; i++)
	{
		if (mKeyboardKeys[i] & 0x80)
		{
			mKeyboardState[i].bPressed = !mKeyboardState[i].bPressing ? true : false;
			mKeyboardState[i].bPressing = true;
			mKeyboardState[i].bUp = false;
		}
		else
		{
			mKeyboardState[i].bUp = mKeyboardState[i].bPressing ? true : false;
			mKeyboardState[i].bPressed = false;
			mKeyboardState[i].bPressing = false;
		}
	}
}

void Input::mouseUpdate()
{
	if (!readMouse())
	{
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		if (mMouseButtons.rgbButtons[i] & 0x80)
		{
			mMouseState[i].bPressed = !mMouseState[i].bPressing ? true : false;
			mMouseState[i].bPressing = true;
			mMouseState[i].bUp = false;
		}
		else
		{
			mMouseState[i].bUp = mMouseState[i].bPressing ? true : false;
			mMouseState[i].bPressed = false;
			mMouseState[i].bPressing = false;
		}
	}
}

bool Input::readKeyboard()
{
	// 키보드 디바이스를 얻는다.
	HRESULT result = mKeyboard->GetDeviceState(sizeof(mKeyboardKeys), (LPVOID)&mKeyboardKeys);
	if (FAILED(result))
	{
		// 키보드가 포커스를 잃었거나 흭득되지 않은 경우 컨트롤을 다시 가져온다.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mKeyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool Input::readMouse()
{
	// 마우스 디바이스를 얻는다.
	HRESULT result = mMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mMouseButtons);
	if (FAILED(result))
	{
		// 마우스가 포커스를 잃었거나 흭득되지 않은 경우 컨트롤을 다시 가져온다.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mMouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool Input::init(const HINSTANCE hInstance, const HWND hWnd)
{
	if (mbInit)
	{
		return false;
	}

	// Direct Input 초기화.
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mInput, nullptr)))
	{
		::MessageBox(nullptr, _T("InputManager/Init/DirectInput8Create : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 키보드 생성.
	if (FAILED(mInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, nullptr)))
	{
		::MessageBox(nullptr, _T("InputManager/Init/Keyboard CreateDevice : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 키보드 데이터 형식 설정.
	if (FAILED(mKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		::MessageBox(nullptr, _T("InputManager/Keyboard SetDataFormat : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 키보드 협조레벨 설정.
	if (FAILED(mKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
	{
		::MessageBox(nullptr, _T("InputManager/Init/Keyboard SetCooperativeLevel : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 키보드 할당.
	mKeyboard->Acquire();

	// 마우스 생성.
	if (FAILED(mInput->CreateDevice(GUID_SysMouse, &mMouse, nullptr)))
	{
		::MessageBox(nullptr, _T("InputManager/Init/Mouse CreateDevice : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 마우스 데이터 형식 설정.
	if (FAILED(mMouse->SetDataFormat(&c_dfDIMouse)))
	{
		::MessageBox(nullptr, _T("InputManager/Init/Mouse SetDataFormat : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 마우스 협조레벨 설정.
	if (FAILED(mMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		::MessageBox(nullptr, _T("InputManager/Init/Mouse SetCooperativeLevel : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 마우스 할당.
	mMouse->Acquire();

	mbInit = true;
	return true;
}

void Input::clear()
{
	for (int i = 0; i < 256; i++)
	{
		mKeyboardState[i].bUp = false;
		mKeyboardState[i].bPressed = false;
		mKeyboardState[i].bPressing = false;
	}

	for (int i = 0; i < 4; i++)
	{
		mMouseState[i].bUp = false;
		mMouseState[i].bPressed = false;
		mMouseState[i].bPressing = false;
	}
}

void Input::release()
{
	if (!mbInit)
	{
		return;
	}

	if (mKeyboard)
	{
		mKeyboard->Unacquire();
		mKeyboard->Release();
	}

	if (mMouse)
	{
		mMouse->Unacquire();
		mMouse->Release();
	}

	if (mInput)
	{
		mInput->Release();
	}

	mbInit = false;
}

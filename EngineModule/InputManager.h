#pragma once

class InputManager
{
public:
	struct State
	{
		bool bPressed = false;
		bool bPressing = false;
		bool bUp = false;
	};

public:
	friend class GameEngine;

public:
	InputManager() = delete;
	InputManager(const InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;
	~InputManager() = delete;

public:
	// 키보드.
	static bool GetKey(const unsigned int key);
	static bool GetKeyDown(const unsigned int key);
	static bool GetKeyUp(const unsigned int key);

	// 마우스.
	static bool GetMouseButton(const int button);
	static bool GetMouseButtonDown(const int button);
	static bool GetMouseButtonUp(const int button);
	static LONG GetAxisMouseX();
	static LONG GetAxisMouseY();
	static LONG GetAxisMouseZ();
	static void GetMousePosition(int* const outMouseX, int* const outMouseY);

private:
	static bool init(const HINSTANCE hInstance, const HWND hWnd);
	static void release();
	static void update();
	static void keyboardUpdate();
	static void mouseUpdate();
	static bool readKeyboard();
	static bool readMouse();

private:
	static bool mbInit;

	static IDirectInput8* mInput;
	static IDirectInputDevice8* mKeyboard;
	static IDirectInputDevice8* mMouse;

	static std::array<unsigned char, 256> mKeyboardKeys;
	static std::array<State, 256> mKeyboardState;

	static DIMOUSESTATE mMouseButtons;
	static std::array<State, 4> mMouseState;
};


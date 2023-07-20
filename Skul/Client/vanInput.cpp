#include "vanInput.h"

namespace van
{
	int hASCII[(int)eKeyCode::End] =					// hash ASCII
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,
		VK_LBUTTON, VK_RBUTTON, VK_MBUTTON,
	};

	void Input::Init()
	{
		for (int i = 0
			; i < (int)eKeyCode::End
			; ++i)
		{
			Key key = {};								// Question) 그냥 Key key; 로 냅두면 안되는가?? -> 구조체기에 {}으로 초기화한다.
			key.code = (eKeyCode)i;						// i=0 는 eKeyCode 에서 'Q'
			key.state = eKeyState::None;				// 아무런 입력이 없는 상태
			key.isPressed = false;						// 눌리지 않은 상태

			eKeys.push_back(key);
		}
	}

	/*
		[이전프레임][현재프레임][   상태	]
		|	 x	   |	x	   |	none	|
		|	 x	   |	o	   |	down	|
		|	 o	   |	o	   |   pressed	|
		|	 o	   | 	x	   |	  up	|
	*/
	void Input::Update()
	{
		for (int i = 0
			; i < (int)eKeyCode::End
			; ++i)
		{
			// 현재 프레임에 i 에 해당하는 키가 눌려졌는가?
			if (GetAsyncKeyState(hASCII[i]) & 0x8000)
			{
				// 이전 프레임에도 눌려졌는가?
				if (eKeys[i].isPressed == true)
					eKeys[i].state = eKeyState::Pressed;	// 현재 프레임에 눌려졌고 이전 프레임에도 눌려졌다. = Pressed
				else
					eKeys[i].state = eKeyState::Down;		// 현재 프레임에 눌려졌고 이전 프레임에는 안 눌려졌다. = Down

				eKeys[i].isPressed = true;					// 현재 프레임에 눌려졌음을 표시해둔다
			}
			else											// 현재 프레임에 i 에 해당하는 키가 눌려지지 않았을때
			{
				// 이전 프레임에 눌려졌는가?
				if (eKeys[i].isPressed == true)
					eKeys[i].state = eKeyState::Up;			// 현재 프레임에 안 눌려졌고, 이전 프레임에 눌려졌다. = Up
				else
					eKeys[i].state = eKeyState::None;		// 현재 프레임에 안 눌려졌고, 이전 프레임에도 안 눌려졌다. = None

				eKeys[i].isPressed = false;					// 현재 프레임에 안눌려졌음을 표시해둔다
			}
		}
	}
	
	// [ 정적변수 namespace ]
	// public 에 정적 변수 인지라 전역변수와 같은 역할을 하긴하지만 
	// input 클래스 소속이기에 변수명 eKeys 앞에 namespace 붙여줘야한다. 
	//	-> Input::eKeys
	std::vector<Input::Key> Input::eKeys = {};	
}
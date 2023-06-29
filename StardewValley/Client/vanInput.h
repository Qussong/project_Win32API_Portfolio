#pragma once
#include "CommonInclude.h"	// vector 

namespace van
{
	enum class eKeyCode		// english key code
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		End,
	};
	enum class eKeyState	// english key state
	{
		Down,
		Up,
		Pressed,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode code;
			eKeyState state;
			bool isPressed;
		};

		static void Init();		// eKeys에 들어갈 Key 구조체의 객체들을 생성하여 넣어준다.
		static void Update();	// 매 프레임마다 키 상태를 확인하고 업데이트 시켜준다.

		/* Question) 
		GetKeyDown(),GetKeyUp(),GetKey() 함수들은 왜 header에서 정의하나?
		__forceinline 키워드랑 관련 있는건가?? 
		만약 그렇다면 __inline 키워드가 붙은 함수도 이렇게 정의해줘야 하나? */
		__forceinline static bool GetKeyDown(eKeyCode code)
		{
			return eKeys[(int)code].state == eKeyState::Down;
		}
		__forceinline static bool GetKeyUp(eKeyCode code)
		{
			return eKeys[(int)code].state == eKeyState::Up;
		}
		__forceinline static bool GetKey(eKeyCode code)
		{
			return eKeys[(int)code].state == eKeyState::Pressed;
		}
		
	private:
		static std::vector<Key> eKeys;	// english keys
	};
}
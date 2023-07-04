#pragma once
#include "CommonInclude.h"

#define OBJECT_CNT 5		// Objects cnt control
namespace van
{
	//using namespace math;	// == van::math
	class Application
	{
	public:
		Application();
		~Application();

		void Init(HWND hwnd);
		void Proc();							// 전체적인 작업 (Update, Render)
		void Update();							// 키 입력을 받아 데이터 수정
		void Render();							// 화면에 그려준다
		void ObjectGenerator(					// 객체를 생성해주는 함수
							float speed,		// 객체의 속도
							int diameter,		// 객체의 지름
							float timeGap);		// 객체 생성 주기

	private:
		HWND mHwnd;
		HDC mHdc;
		math::Vector2 playerPos;				// vanMath.h

		RECT clientArea = {};
		int curObjectCnt = 0;					// 현재 생성된 객체 개수
		std::vector<Object> objectContainer;	// 객체를 담아두는 바구니
	};
}


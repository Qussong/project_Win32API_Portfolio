#pragma once
#include "vanGameObject.h"

namespace van
{
	class Skull : public GameObject
	{
	public:
		enum class HeadDirection
		{
			Left,
			Right,
			None,
		};

	public:
		Skull();
		virtual ~Skull();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other);	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other);	// 충돌에서 벗어남

		__forceinline HeadDirection GetDirection() { return mDirection; }
		__forceinline void SetDirection(HeadDirection _direction) { mDirection = _direction; }

		__forceinline bool GetCollision() { return mbCollision; }
		__forceinline void SetCollision(bool _flag) { mbCollision = _flag; }

	private:
		HeadDirection mDirection;
		bool mbCollision = false;
	};
}


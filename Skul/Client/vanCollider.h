#pragma once
#include "vanComponent.h"

namespace van
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* _other);	// 충돌 시작
		void OnCollisionStay(Collider* _other);		// 충돌상태 유지
		void OnCollisionExit(Collider* _other);		// 충돌상태 탈출

		__forceinline math::Vector2 GetSize() { return mSize; }
		__forceinline void SetSize(math::Vector2 _size) { mSize = _size; }

		__forceinline math::Vector2 GetOffset() { return mOffset; }
		__forceinline void SetOffset(math::Vector2 _offset) { mOffset = _offset; }

		__forceinline math::Vector2 GetPos() { return mPos; }

		__forceinline UINT GetCollisionNum() { return mCollisionNum; }

	private:
		static UINT mCollisionCount;	// ???

		math::Vector2 mSize;			// 그려질 도형(사각형)의 크기
		math::Vector2 mOffset;			// 그려질 도형(사각형)의 위치조정 값
		math::Vector2 mPos;				// 그려질 도형의 중심좌표

		UINT mCollisionNum;				// 
		bool mbIsCollision;				// 충돌 여부 (충돌시 true)
	};
}


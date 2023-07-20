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

		void OnCollisionEnter(Collider* _other);
		void OnCollisionStay(Collider* _other);
		void OnCollisionExit(Collider* _other);

		__forceinline math::Vector2 GetSize() { return mSize; }
		__forceinline void SetSize(math::Vector2 _size) { mSize = _size; }
		__forceinline math::Vector2 GetOffset() { return mOffset; }
		__forceinline void SetOffset(math::Vector2 _offset) { mOffset = _offset; }
		__forceinline math::Vector2 GetPos() { return mPos; }
		__forceinline UINT GetCollisionNum() { return mCollisionNum; }

	private:
		static UINT mCollisionCount;

		math::Vector2 mSize;
		math::Vector2 mOffset;
		math::Vector2 mPos;

		UINT mCollisionNum;
		bool mbIsCollision;
	};
}


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

		__forceinline math::Vector2 GetSize() { return mSize; }
		__forceinline void SetSize(math::Vector2 size) { mSize = size; }
		__forceinline math::Vector2 GetOffset() { return mOffset; }
		__forceinline void SetOffset(math::Vector2 offset) { mOffset = offset; }

	private:
		math::Vector2 mSize;
		math::Vector2 mOffset;
	};
}


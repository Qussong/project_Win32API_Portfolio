#pragma once
#include "vanComponent.h"

namespace van
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);

	private:


	};
}
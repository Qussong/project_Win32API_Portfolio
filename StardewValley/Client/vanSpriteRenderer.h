#pragma once
#include "vanComponent.h"
#include "vanImage.h"

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

		__forceinline void SetImage(Image* _image) { mImage = _image; }

	private:
		Image* mImage;
	};
}
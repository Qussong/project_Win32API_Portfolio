#pragma once
#include "vanComponent.h"
#include "vanTexture.h"

namespace van
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		__forceinline void SetTexture(Texture* _texture) { mTexture = _texture; }
		void SetScale(math::Vector2 _scale) { mScale = _scale; }

	private:
		Texture* mTexture;
		math::Vector2 mScale;
	};
}
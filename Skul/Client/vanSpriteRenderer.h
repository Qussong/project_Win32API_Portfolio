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
		__forceinline Texture* GetTexture() { return mTexture; }
		__forceinline void SetScale(math::Vector2 _scale) { mScale = _scale; }
		__forceinline void SetAffectCamera(bool _flag) { mAffectCamera = _flag; }
		__forceinline float GetAlpha() { return mAlpha; }
		__forceinline void SetAlpha(float _value) { mAlpha = _value; }

	private:
		Texture* mTexture;
		math::Vector2 mScale;
		bool mAffectCamera;		// 카메라 영향 여부
		float mAlpha;			// 알파 값
	};
}
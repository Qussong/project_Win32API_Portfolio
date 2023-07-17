#pragma once
#include "vanResource.h"

namespace van
{
	class Animator;
	class Texture;

	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			math::Vector2 leftTop;
			math::Vector2 size;
			math::Vector2 offset;
			float duration;

			Sprite()
				: leftTop(math::Vector2::Zero)
				, size(math::Vector2::Zero)
				, offset(math::Vector2::Zero)
				, duration(0.0f)
			{
			}
		};

		Animation();
		~Animation();

		void Update();
		void Render(HDC _hdc);
		virtual HRESULT Load(const std::wstring& _path) { return S_FALSE; };
		void Create(
			const std::wstring& _name
			, class Texture* _texture
			, math::Vector2 _leftTop
			, math::Vector2 _size
			, math::Vector2 _offset
			, UINT _spriteLength
			, float _duration);
		void Reset();
		
		__forceinline bool IsComplete() { return mbComplete; }
		__forceinline void SetAnimator(Animator* _animator) { mAnimator = _animator; }
		__forceinline void SetScale(math::Vector2 _scale) { mScale = _scale; }

	private:
		Animator* mAnimator;
		Texture* mTexture;
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
		math::Vector2 mScale;
	};
}


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
			/*
				Sprite는 일반적으로 'Atlas Image' 사용을 전재로한다.
				때문에 해당 프레임에 출력할 영역이 Sprite의 어디인지 알 필요가 있다.
				Atlas는 여러 개의 프레임 이미지를 모아둔 거대한 이미지 파일이다.
				Atlas가 존재하는 이유는 '메모리의 계층구조' 때문이다.
				일반적으로 컴퓨터 구조에서 접근 속도는 아래의 순서로 빠르다.
					1. CPU -> 레지스터 
					2. 레지스터 -> 램(Memory)
					3. 램 -> 하드디스크 / SSD
				이미지 파일을 읽어오는 작업은
				하드디스크 혹은 SSD에 접근해서 파일을 읽고 이를 램(Memory)에 올리는 동작을 하기 때문에 
				Atlas에 여러 개의 프레임 이미지를 합쳐서 사용하는 것을 선호된다.
				즉 여러 개의 프레임 이미지가 파일 단위로 이루어져 있다면 각각의 이미지를 읽는 시간이 요구되어
				불필요하게 로드에 시간을 많이 할애하게된다. 
				이렇게 '불필요한 시간' 혹은 '비용'을 '오버헤드'라고한다.
			*/
			math::Vector2 leftTop;					// 좌상단
			math::Vector2 size;						// 좌상단부터 우하단까지의 크기
			math::Vector2 offset;					// 이미지 출력시 별도로 필요한 옵셋값(옵션)
			float duration;							// 각 이미지가 화면 출력시 유지되어야 할 시간(=유지시간)

			Sprite()
				: leftTop(math::Vector2::Zero)		
				, size(math::Vector2::Zero)
				, offset(math::Vector2::Zero)
				, duration(0.0f)
			{
			}
		};

		Animation();
		//Animation(const Animation& anim);	// 복사 생성자
		~Animation();

		void init();
		void Update();
		void Render(HDC _hdc);
		__forceinline virtual HRESULT Load(const std::wstring& _path) override { return S_FALSE; };
		void Create(					// Animation을 생성해준다.
			const std::wstring& _name	// Animation 이름
			, class Texture* _texture	//
			, math::Vector2 _leftTop	//
			, math::Vector2 _size		//
			, math::Vector2 _offset		//
			, UINT _spriteLength		//
			, float _duration);			//
		void Reset();
		
		__forceinline bool IsComplete() { return mbComplete; }
		__forceinline void SetAnimator(Animator* _animator) { mAnimator = _animator; }
		__forceinline void SetScale(math::Vector2 _scale) { mScale = _scale; }

		__forceinline void SetAffectCamera(bool _flag) { mAffectCamera = _flag; }


	private:
		Animator* mAnimator;
		Texture* mTexture;
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
		math::Vector2 mScale;

		bool mAffectCamera;
	};
}


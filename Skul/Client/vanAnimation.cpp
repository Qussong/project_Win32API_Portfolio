#include "vanAnimation.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanCamera.h"
#include "vanTexture.h"
#include "vanAnimator.h"

namespace van
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mTexture(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
		, mScale(math::Vector2::One)
		, mAffectCamera(true)
	{
	}

	Animation::~Animation()
	{
		// nothing
	}

	void Animation::init()
	{
		// nothing
	}

	void Animation::Update()
	{
		if (mbComplete)
		{
			return;
		}

		mTime += Time::GetDeltaTime();					// 프레임의 흐름에 따른 mTime에 시간 누적
		if (mSpriteSheet[mIndex].duration < mTime)	// mIndex에 해당하는 이미지의 유지시간과 누적시간을 비교
		{
			// 유지시간 < 누적시간
			mTime = 0.0f;							// 다음 이미지가 출력될 것이므로 mTime 초기화

			if (mIndex < mSpriteSheet.size() - 1)	// mIndex는 0부터 시작하므로 (크기 - 1)보다 작다면 인덱스 증가
			{
				mIndex++;
			}
			else
			{
				// mIndex의 값이 (mSpriteSheet크기 - 1) 보다 크거나 같다는 의미
				mbComplete = true;	// 애니메이션의 재생 완료
			}
		}
	}

	void Animation::Render(HDC _hdc)
	{
		if (mTexture == nullptr)
		{
			// 그려낼 때 참고할 Atlas 텍스처가 nullptr 이라면
			// 참고할 이미지가 없다는 것이기에 예외처리를 위해서 return
			return;
		}
		
		Sprite sprite = mSpriteSheet[mIndex];	// 현재 인덱스(mIndex)의 Sprite 이미지를 가져온다.

		Transform* tr = 
			mAnimator->GetOwner()->GetComponent<Transform>();	// 해당 Animation 객체를 관리하는 Animator를 통해 
																// GameObject 객체에 접근하여 Transform 값을 얻어온다.
		
		math::Vector2 pos = 
			tr->GetPosition() + sprite.offset;	// Transform 을통해 Animation 을 그려줄 위치를 얻어온다.
												// 해당 좌표에서 offset(기본값 : 0) 값 만큼 이동하도록 한다.

		//Animator* ani = mAnimator;
		mTexture->Render(
			_hdc
			, pos
			, sprite.size
			, sprite.leftTop
			, sprite.size
			, mAffectCamera
			, sprite.offset
			, mAnimator->GetScale()
			, mAnimator->GetAlpha());
	}

	// 전달받은 인자를 이용해서 m_SpriteSheet에 실제 프레임 정보를 넣어준다.
	// 해당 함수는 애니메이션을 만들 때, 한 줄로 프레임을 찾아내서 넣어준다.
	void Animation::Create(
		const std::wstring& _name
		, Texture* _texture
		, math::Vector2 _leftTop
		, math::Vector2 _size
		, math::Vector2 _offset
		, UINT _spriteLength	// Atals 텍스처에서 추출할 프레임의 개수
		, float _duration)
	{
		mTexture = _texture;

		for (size_t i = 0; i < _spriteLength; ++i)
		{
			Sprite sprite = {};

			sprite.leftTop.x = _leftTop.x + (_size.x * i);	// loop가 진행될수록 이미지의 x축 길이만큼 계속 길어짐
			sprite.leftTop.y = _leftTop.y;					// 일정하게 유지

			if (sprite.leftTop.x >= _texture->GetWidth())	// 다음줄에 추출할 이미지가 있을 경우
			{
				sprite.leftTop.x = sprite.leftTop.x - _texture->GetWidth();
				sprite.leftTop.y = _leftTop.y + _size.y;
			}

			sprite.size = _size;							// 각 프레임의 크기
			sprite.offset = _offset;						// 이미지 출력시 별도로 필요한 옵셋값(옵션)
			sprite.duration = _duration;					// 해당 스프라이트가 화면에 유지될 시간

			mSpriteSheet.push_back(sprite);					// Texture에서 각 프레임에대한 애니메이션 재생과 관련된 정보를 
															// Sprite에 저장하여 mSpriteSheet에 저장
		}
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
}
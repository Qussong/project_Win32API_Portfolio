#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	Animator::Animator()
		: Component(enums::eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)
		, mbAffectedCamera(true)
		, mAlpha(1.0f)
		, mScale(math::Vector2::One)
	{
		// nothing
	}

	Animator::~Animator()
	{
		for (auto iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void Animator::Init()
	{
		// nothing
	}

	void Animator::Update()
	{
		if (mActiveAnimation)	// 가리키는 Animation 객체가 있다면
		{
			mActiveAnimation->Update();
			if (mActiveAnimation->IsComplete() && mbLoop)
			{
				mActiveAnimation->Reset();
			}
		}
		else  // 가리키는 Animation 객체가 없다면
		{
			return;
		}
	}

	void Animator::Render(HDC _hdc)
	{
		// 강사님 코드)
		//mActiveAnimation->SetAffectCamera(mbAffectedCamera);
		//if (mActiveAnimation)	// 가리키는 Animation 객체가 있다면
		//	mActiveAnimation->Render(_hdc);

		// 내방식)
		if (mActiveAnimation)	// 가리키는 Animation 객체가 있다면
		{
			mActiveAnimation->SetAffectCamera(mbAffectedCamera);
			mActiveAnimation->Render(_hdc);
		}
		else  // 가리키는 Animation 객체가 없다면
		{
			return;
		}
	}

	Animation* Animator::CreateAnimation(
				const std::wstring& _name
				, Texture* _texture
				, math::Vector2 _leftTop
				, math::Vector2 _size
				, UINT _spriteLength
				, math::Vector2 _offset
				, float _duration)
	{
		Animation* animation = nullptr;
		//animation = ResourceManager::Find<Animation>(_name);
		animation = FindAnimation(_name);

		if (animation != nullptr)
		{
			return animation;
		}

		animation = new Animation();
		animation->Create(
			_name
			, _texture
			, _leftTop
			, _size
			, _offset
			, _spriteLength
			, _duration);
		animation->SetAnimator(this);
		mAnimations.insert(std::make_pair(_name, animation));

		return animation;
	}

	void Animator::CreateAnimationFolder(
		const std::wstring& _name						// 애니메이션 이름(Key)
		, const std::wstring& _path						// 애니메이션 파일 경로
		, math::Vector2 _offset							// 
		, float _duration)								// 재생시간
	{
		UINT width = 0;									// 너비
		UINT height = 0;								// 높이
		UINT fileCout = 0;								// 폴더에 들어있는 이미지 파일 개수

		std::filesystem::path fs(_path);				// 경로지정
		std::vector<Texture*> images = {};				// Texture 객체들 저장하는 곳

		for (auto& p :
			std::filesystem::directory_iterator(_path))	// recursive_directory_iterator
		{
			std::wstring  fileName = p.path().filename();
			std::wstring fullName = p.path();

			Texture* image =
				ResourceManager::Load<Texture>(fileName, fullName);

			images.push_back(image);

			if (width < image->GetWidth())
			{
				width = image->GetWidth();
			}

			if (height < image->GetHeight())
			{
				height = image->GetHeight();
			}

			++fileCout;
		}

		Texture* spriteSheet = Texture::Create(_name, width * fileCout, height);

		eTextureType imgType = images[0]->GetType();	// 0번 인덱스로 하는방법 말고 없나..?
		if (imgType == eTextureType::Bmp)
		{
			spriteSheet->SetType(eTextureType::Bmp);
		}
		if(imgType == eTextureType::AlphaBmp)
		{
			spriteSheet->SetType(eTextureType::AlphaBmp);
		}
		if (imgType == eTextureType::Png)				// 근데... png 안되는건가?
		{
			spriteSheet->SetType(eTextureType::Png);
			//spriteSheet->SetType(eTextureType::Bmp);
		}

		int idx = 0;
		for (Texture* image : images)
		{
			::BitBlt(											// BitBlt() ???
				// 타겟
				spriteSheet->GetHdc()
				, width * idx
				, 0
				, image->GetWidth() /** mScale.x*/
				, image->GetHeight() /** mScale.y*/
				// 원본
				, image->GetHdc()
				, 0, 0
				// 설정
				, SRCCOPY);
			idx++;
		}

		CreateAnimation(
			_name
			, spriteSheet
			, math::Vector2(0.0f, 0.0f)
			, math::Vector2(width, height)
			, fileCout
			, _offset
			, _duration);
	}

	Animation* Animator::FindAnimation(const std::wstring& _name)
	{
		auto iter = mAnimations.find(_name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& _name, bool _loop)
	{
		Animation* animation = FindAnimation(_name);
		if (animation == nullptr)
			return;

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = _loop;
	}

	void Animator::Reset()
	{
		mActiveAnimation = nullptr;
		mbLoop = false;
		mbAffectedCamera = true;
		mAlpha = 1.0f;
		mScale = math::Vector2::One;
	}
}
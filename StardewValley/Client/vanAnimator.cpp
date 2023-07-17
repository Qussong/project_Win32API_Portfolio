#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	Animator::Animator()
		: Component(enums::eComponentType::Animator)
		//, mAnimations()
		//, mActiveAnimation()
		//, mbLoop()
		//, mbAffectedCamera()
		, mAlpha(1.0f)
		, mScale(math::Vector2::One)
	{
		// nothing
	}

	Animator::~Animator()
	{
		// nothing
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
	}

	void Animator::Render(HDC _hdc)
	{
		if (mActiveAnimation)	// 가리키는 Animation 객체가 있다면
			mActiveAnimation->Render(_hdc);
	}

	void Animator::CreateAnimation(const std::wstring& _name
									, Texture* _texture
									, math::Vector2 _leftTop
									, math::Vector2 _size
									, UINT _spriteLength
									, math::Vector2 _offset
									, float _duration)
	{
		Animation* animation = nullptr;
		animation = ResourceManager::Find<Animation>(_name);
		if (animation != nullptr)
			return;

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
		ResourceManager::Insert<Animation>(_name, animation);
	}

	void Animator::CreateAnimationFolder(const std::wstring& _name
										, const std::wstring& _path
										, math::Vector2 _offset
										, float _duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCout = 0;

		std::filesystem::path fs(_path);	// 경로지정
		std::vector<Texture*> images = {};	// Texture 객체들 저장하는 곳
		for (auto& p : std::filesystem::recursive_directory_iterator(_path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path();

			Texture* image = ResourceManager::Load<Texture>(fileName, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			++fileCout;
		}

		Texture* spriteSheet = Texture::Create(_name, width * fileCout, height);

		eTextureType type = images[0]->GetType();
		if (type == eTextureType::Bmp)
			spriteSheet->SetType(eTextureType::Bmp);
		else if (type == eTextureType::AlphaBmp)
			spriteSheet->SetType(eTextureType::AlphaBmp);
		else if (type == eTextureType::Png)
			spriteSheet->SetType(eTextureType::Png);
		else
			__noop;

		int idx = 0;
		for (Texture* image : images)
		{
			BitBlt(
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
}
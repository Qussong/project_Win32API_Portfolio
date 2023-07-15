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
									, math::Vector2 _offset
									, UINT _spriteLength
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

	/*void Animator::CreateAnimationFolder(const std::wstring& _name
										, const std::wstring& _path
										, math::Vector2 _offset
										, float _duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCout = 0;

		std::filesystem::path fs(_path);
		std::vector<Texture*> images = {};
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
	}*/

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
#pragma once
#include "vanComponent.h"
#include "vanAnimation.h"

namespace van
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		Animation* CreateAnimation(				//
				const std::wstring& _name		//
				, class Texture* _texture		//
				, math::Vector2 _leftTop		//
				, math::Vector2 _size			//
				, UINT _spriteLength			//
				, math::Vector2 _offset 
					= math::Vector2::Zero		//
				, float _duration = 0.1f);		//									

		void CreateAnimationFolder(							
			const std::wstring& _name						
			, const std::wstring& _path						
			, math::Vector2 _offset = math::Vector2::Zero	
			, float _duration = 0.1f);

		Animation* FindAnimation(const std::wstring& _name);
		void PlayAnimation(const std::wstring& _name, bool _loop = false);
		void Reset();

		__forceinline bool GetAffectedCamera() { return mbAffectedCamera; }					//
		__forceinline void SetAffectedCamera(bool _enable) { mbAffectedCamera = _enable; }	//
		__forceinline float GetAlpha() { return mAlpha; }									//
		__forceinline void SetAlpha(float _alpha) { mAlpha = _alpha; }						//
		__forceinline math::Vector2 GetScale() { return mScale; }
		__forceinline void SetScale(math::Vector2 _scale) { mScale = _scale; }
		__forceinline bool IsActiveAnimationComplete() { return mActiveAnimation->IsComplete(); }	// 

	private:
		std::map<std::wstring, Animation*> mAnimations;		// Animation 객체를 key값과 함꼐 map으로 관리
		Animation* mActiveAnimation;						// 
		bool mbLoop;										//
		bool mbAffectedCamera;								//
		float mAlpha;										//
		math::Vector2 mScale;
	};
}


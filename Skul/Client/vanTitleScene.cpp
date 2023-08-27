#include "vanTitleScene.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanBackGround.h"
#include "vanCamera.h"
#include "vanAnimator.h"
#include "vanSound.h"

namespace van
{
	TitleScene::TitleScene()
		: mBackGround(nullptr)
	{
		// nothing
	}

	TitleScene::~TitleScene()
	{
		// nothing
	}

	void TitleScene::Init()
	{
		mBackGround = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		mBackGround->GetComponent<Animator>()->PlayAnimation(L"BG_Intro", false);
		mBackGround->GetComponent<Animator>()->SetAffectedCamera(false);
		mBackGround->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));

		// 해당 Scene에서의 카메라 최대 이동거리 설정
		SetCameraWidthLimit(math::Vector2(mBackGround->GetLimitLeft(), mBackGround->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(mBackGround->GetLimitUp(), mBackGround->GetLimitDown()));

		SetSceneTarget(nullptr);	// 기본값 nullptr이라 생략 가능
	}

	void TitleScene::Update()
	{
		Animator* at = mBackGround->GetComponent<Animator>();

		Scene::Update();						// 부모의 Update 함수 호출

		if (at->IsActiveAnimationComplete() == true)
		{
			if(mbPlayAnimation == true)
			{
				at->PlayAnimation(L"BG_Intro_Loop", true);
				mbPlayAnimation = false;
			}
		}
	}

	void TitleScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);					// 부모의 Render 함수 호출

		// Scene 구분
		const wchar_t* str = L"[ TitleScene ]";
		Text::PrintwString(_hdc, 10, 30, str);	// 아래 두면 가려지지 않는다.
	}

	void TitleScene::SceneIN()
	{
		// 배경 사운드
		SetBgSound(ResourceManager::Load<Sound>(L"TitleSound", L"..\\MyResources\\skul\\Sound\\MainTitle.wav"));
		GetBgSound()->Play(false);

		//  카메라 최대 이동 가능 거리 설정
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// 카메라로 해당 Scene의 Target 비추기
		Camera::SetTarget(GetSceneTarget());
	}

	void TitleScene::SceneOut()
	{
		// 배경 사운드 종료
		GetBgSound()->Stop(true);

		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
	}
}
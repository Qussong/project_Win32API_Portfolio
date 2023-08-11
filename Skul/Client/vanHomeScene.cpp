#include "vanHomeScene.h"
#include "vanCamera.h"
#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanFloor.h"
#include "vanObject.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanPlayer.h"
#include "vanAnimator.h"
#include "vanCollisionManager.h"

namespace van
{
	HomeScene::HomeScene()
	{
		// nothing
	}

	HomeScene::~HomeScene()
	{
		// nothing
	}

	void HomeScene::Init()
	{
		// BG
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Home_Scene"));					// BackGround 객체의 texture 설정
		bgsr->SetAffectCamera(true);														// 카메라 영향 여부설정
		// 배경이미지의 크기를 기반으로 카메라의 이동제한값 계산
		bg->SetAutoCameraLimit();
		// 해당 Scene에 카메라의 이동제한값 저장
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		Animator* at = player->GetComponent<Animator>();
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X - 700.0f, Window_Y - 3240.0f));
		at->SetScale(math::Vector2(2.0f, 2.0f));

		// Floor
		Floor* floor = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor->GetComponent<Collider>()->SetSize(math::Vector2(3860.0f, 2.0f));
		floor->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X - 1205.0f, Window_Y - 3240.0f));

		// 해당 Scene의 카메라 타겟 설정
		SetSceneTarget(player);
	}

	void HomeScene::Update()
	{
		Scene::Update();

		math::Vector2 targetPos = GetSceneTarget()->GetComponent<Transform>()->GetPosition();
		float targetPos_Y = targetPos.y;
		float cameraPosLimit_Y = GetCameraHeightLimit().y;
		float offset_Y = fabs(cameraPosLimit_Y - targetPos_Y);
		if (targetPos.x < 1320.0f)
		{
			Camera::SetCameraOffset(math::Vector2(0.0f, -offset_Y));
		}
		
	}

	void HomeScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ HomeScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void HomeScene::SceneIN()
	{
		// 해당 Scene에서의 카메라 최대 이동 가능 거리값 카메라에 세팅
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// 카메라에 해당 Scene의 타겟을 세팅
		Camera::SetTarget(GetSceneTarget());

		// 해당 Scene에서의 충돌판정 설정
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
	}

	void HomeScene::SceneOut()
	{
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
		// 카메라 offset 설정 초기화
		Camera::CameraOffsetClear();
		// 충돌판정 설정 초기화
		CollisionManager::Clear();
	}
}
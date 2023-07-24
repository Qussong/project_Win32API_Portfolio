#include "vanStageScene.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCamera.h"
#include "vanBackGround.h"

#include "vanSpearman.h"
#include "vanCarleonRecruit.h"

van::StageScene::StageScene()
{
	// nothing
}

van::StageScene::~StageScene()
{
	// nothing
}

void van::StageScene::Init()
{	

	//SetSceneTarget(nullptr);	// 기본값 nullptr이라 생략 가능
	Camera::SetTarget(GetSceneTarget());
}

void van::StageScene::Update()
{
	Camera::SetTarget(GetSceneTarget());
	Scene::Update();
}

void van::StageScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);

	// Scene 구분
	const wchar_t* str = L"[ StageScene ]";
	int len = (int)wcslen(str);
	Text::PrintwString(_hdc, 10, 30, str);
}

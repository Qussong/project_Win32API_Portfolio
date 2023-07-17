#include "vanBackGround.h"
#include "vanSpriteRenderer.h"

namespace van
{
	BackGround::BackGround()
	{

	}

	BackGround::~BackGround()
	{

	}

	void BackGround::Init()
	{

	}

	void BackGround::Update()
	{
		GameObject::Update();

		//SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		/*float alpha = sr->GetAlpha();
		alpha -= 0.2f * Time::DeltaTime();
		sr->SetAlpha(alpha);*/
	}

	void BackGround::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
}
#include "vanBackGround.h"
#include "vanSpriteRenderer.h"

namespace van
{
	BackGround::BackGround()
	{

	}

	BackGround::BackGround(math::Vector2 _offset)
	{
		// nothing
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
	}

	void BackGround::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
}
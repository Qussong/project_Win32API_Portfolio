#pragma once
#include "vanGameObject.h"

namespace van
{
	enum class PlayerState	
	{
		RightIdle,
		LeftIdle,
		None,
	};

	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:
		PlayerState state;
	};
}


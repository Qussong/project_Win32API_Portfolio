#pragma once
#include "vanGameObject.h"

namespace van
{
	

	class Player : public GameObject
	{
	public:
		enum class PlayerState
		{
			Walk,
			Idle,
		};
		
		enum class PlayerDirection
		{
			Right,
			Left,
		};

		Player();
		virtual ~Player();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		void ChangeState(PlayerState _state);
		void StillSameState();

		void Walk();
		void Idle();
		
	private:
		PlayerState mState;
		PlayerDirection mDirection;
	};
}


#pragma once
#include "vanGameObject.h"

namespace van
{
	class Animator;

	class Player : public GameObject
	{
	public:
		enum class PlayerState
		{
			Idle,
			Walk,
			Dash,
			Attack,
			Jump,
			JumpAttack,
			Death,
			Reborn,
			WaitDance,
			None,
		};
		
		enum class PlayerDirection
		{
			Left,
			Right,
			None,
		};

		Player();
		Player(math::Vector2 _offset);
		virtual ~Player();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		void MakeAnimation(math::Vector2 _offset = math::Vector2::Zero);

		void ChangeState(PlayerState _state);
		void StillSameState();

		void Walk();
		void Idle();
		void Jump();
		void Attack();
		void Dash();

		
	private:
		PlayerState mState;
		PlayerDirection mDirection;
		Animator* animator;
		bool mbDoubleKey;
	};
}


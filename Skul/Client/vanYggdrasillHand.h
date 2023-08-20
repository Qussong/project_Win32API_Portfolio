#pragma once
#include "vanGameObject.h"
#include "vanTransform.h"

namespace van
{
	class YggdrasillHand : public GameObject
	{
	public:
		enum class HandPos
		{
			Left,
			Right,
			None,
		};

	public:
		YggdrasillHand();
		virtual ~YggdrasillHand();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other);	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other);	// 충돌에서 벗어남

		__forceinline HandPos GetHandPos() { return mHandPos; }
		__forceinline void SetHandPos(HandPos _pos) { mHandPos = _pos; }

		__forceinline GameObject* GetOwner() { return mOwner; }
		__forceinline void SetOwner(GameObject* _owner) { mOwner = _owner; }

		__forceinline void SetPos(math::Vector2 _pos) { GetComponent<Transform>()->SetPosition(_pos); }
		__forceinline math::Vector2 GetPos() { return GetComponent<Transform>()->GetPosition(); }

	private:
		HandPos mHandPos = HandPos::None;
		GameObject* mOwner = nullptr;
		bool mbInitPlayAnimation = false;
	};
}


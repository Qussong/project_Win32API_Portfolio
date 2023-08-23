#pragma once
#include "vanComponent.h"

namespace van
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);

		void SetPosition(math::Vector2 position);	// Setter
		math::Vector2 GetPosition();				// Getter

	private:
		math::Vector2 mPosition = math::Vector2::Zero;
	};

}
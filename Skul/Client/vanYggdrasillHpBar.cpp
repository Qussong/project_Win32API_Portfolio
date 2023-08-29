#include "vanYggdrasillHpBar.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanYggdrasill.h"

#define YGGDRASILL_HP_POS_X		Window_X / 2 - 274.0f
#define YGGDRASILL_HP_POS_Y		56.0f

namespace van
{
	YggdrasillHpBar::YggdrasillHpBar()
	{
		// nothing
	}

	YggdrasillHpBar::~YggdrasillHpBar()
	{
		// nothing
	}

	void YggdrasillHpBar::Init()
	{
		UI::Init();

		mYggHpBar = ResourceManager::Load<Texture>(L"UI_Yggdrasill_HpBar", L"..\\MyResources\\skul\\UI\\YggdrasillHPBar.png");
		mYggDamageBar = ResourceManager::Load<Texture>(L"UI_Yggdrasill_HpBar_Damage", L"..\\MyResources\\skul\\UI\\YggdrasillHPBar_Damage.png");
	}

	void YggdrasillHpBar::Update()
	{
		UI::Update();

		if (mYgg == nullptr)
		{
			// nothing
		}
		else
		{
			if (mReductionHp >= mYgg->GetHp())
			{
				mReductionHp -= Time::GetDeltaTime() * 50.0f;
			}
			else
			{
				mReductionHp = mYgg->GetHp();
			}
		}
	}

	void YggdrasillHpBar::Render(HDC _hdc)
	{
		UI::Render(_hdc);

		if (mYgg == nullptr)
		{
			// nothing
		}
		else
		{
			float mageHP = mYgg->GetHp();
			float mageMaxHP = mYgg->GetMaxHp();
			float hpPercent = mageHP / mageMaxHP;

			// ºóÄ­ À§Ä¡ = 640.0f 59.0f
			// Damage Bar
			::TransparentBlt(
				// target
				_hdc,
				YGGDRASILL_HP_POS_X,
				YGGDRASILL_HP_POS_Y,
				mYggDamageBar->GetWidth() * (mReductionHp / mageMaxHP),
				mYggDamageBar->GetHeight(),
				// source
				mYggDamageBar->GetHdc(),
				0, 0,
				mYggDamageBar->GetWidth() * (mReductionHp / mageMaxHP),
				mYggDamageBar->GetHeight(),
				RGB(255, 0, 255));

			::TransparentBlt(
				// target
				_hdc,
				YGGDRASILL_HP_POS_X,
				YGGDRASILL_HP_POS_Y,
				mYggHpBar->GetWidth() * hpPercent,
				mYggHpBar->GetHeight(),
				// source
				mYggHpBar->GetHdc(),
				0, 0,
				mYggHpBar->GetWidth() * hpPercent,
				mYggHpBar->GetHeight(),
				RGB(255, 0, 255));
		}
	}

	void YggdrasillHpBar::MakeAnimation()
	{
		// nothing
	}

	void YggdrasillHpBar::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void YggdrasillHpBar::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void YggdrasillHpBar::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}
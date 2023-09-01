#include "vanMageHpBar.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanMage.h"

#define MAGE_HP_POS_X	1054.0f
#define MAGE_HP_POS_Y	54.0f

namespace van
{
	MageHpBar::MageHpBar()
	{
		// nothing
	}

	MageHpBar::~MageHpBar()
	{
		// nothing
	}

	void MageHpBar::Init()
	{
		UI::Init();

		mMageHpBar = ResourceManager::Load<Texture>(L"UI_Mage_HpBar", L"..\\MyResources\\skul\\UI\\MageHPBar.png");
		mMageDamageBar = ResourceManager::Load<Texture>(L"UI_Mage_HpBar_Damage", L"..\\MyResources\\skul\\UI\\MageHPBar_Damage.png");
		mMageHealBar = ResourceManager::Load<Texture>(L"UI_Mage_HpBar_Heal", L"..\\MyResources\\skul\\UI\\MageHPBar_Heal.png");
	}

	void MageHpBar::Update()
	{
		UI::Update();

		if (mMage == nullptr)
		{
			// nothing
		}
		else
		{
			if (mReductionHp >= mMage->GetHp())
			{
				mReductionHp -= Time::GetDeltaTime() * 50.0f;
			}
			else
			{
				mReductionHp = mMage->GetHp();
			}
		}
	}

	void MageHpBar::Render(HDC _hdc)
	{
		UI::Render(_hdc);

		if (mMage == nullptr)
		{
			// nothing
		}
		else
		{
			float mageHP = mMage->GetHp();
			float mageMaxHP = mMage->GetMaxHp();
			float hpPercent = mageHP / mageMaxHP;

			// ºóÄ­ À§Ä¡ = 1160.0f 40.0f
			// Damage Bar
			::TransparentBlt(
				// target
				_hdc,
				MAGE_HP_POS_X,
				MAGE_HP_POS_Y,
				mMageDamageBar->GetWidth() * (mReductionHp / mageMaxHP),
				mMageDamageBar->GetHeight(),
				// source
				mMageDamageBar->GetHdc(),
				0, 0,
				mMageDamageBar->GetWidth() * (mReductionHp / mageMaxHP),
				mMageDamageBar->GetHeight(),
				RGB(255, 0, 255));

			::TransparentBlt(
				// target
				_hdc,
				MAGE_HP_POS_X,
				MAGE_HP_POS_Y,
				mMageHpBar->GetWidth() * hpPercent,
				mMageHpBar->GetHeight(),
				// source
				mMageHpBar->GetHdc(),
				0, 0,
				mMageHpBar->GetWidth() * hpPercent,
				mMageHpBar->GetHeight(),
				RGB(255, 0, 255));
		}
	}

	void MageHpBar::MakeAnimation()
	{
		// nothing
	}

	void MageHpBar::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void MageHpBar::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void MageHpBar::OnCollisionExit(Collider* _other)
	{
		// nothing
	}
}
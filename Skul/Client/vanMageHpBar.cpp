#include "vanMageHpBar.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanMage.h"

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

		mHpBar = ResourceManager::Load<Texture>(L"UI_Mage_HpBar", L"..\\MyResources\\skul\\UI\\MageHPBar.png");
		mDamageBar = ResourceManager::Load<Texture>(L"UI_Mage_HpBar_Damage", L"..\\MyResources\\skul\\UI\\MageHealthBar_Damage.png");
		mHealBar = ResourceManager::Load<Texture>(L"UI_Mage_HpBar_Heal", L"..\\MyResources\\skul\\UI\\MageHPBar_Heal.png");
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

		if (mPlayer == nullptr)
		{
			GameObject* obj = SceneManager::GetActiveScene()->GetSceneTarget();
			mPlayer = dynamic_cast<Player*>(obj);
		}
		else
		{
			float playerHP = mPlayer->GetHp();
			float playerMaxHP = mPlayer->GetMaxHp();
			float hpPercent = playerHP / playerMaxHP;

			// ºóÄ­ À§Ä¡ = 168.0f, 654.0f
			// Damage Bar
			::TransparentBlt(
				// target
				_hdc,
				168.0f - 82.0f,
				654.0f + 22.0f,
				mDamageBar->GetWidth() * (mReductionHp / playerMaxHP) * 2.0f,
				mDamageBar->GetHeight() * 2.0f,
				// source
				mDamageBar->GetHdc(),
				0, 0,
				mDamageBar->GetWidth() * (mReductionHp / playerMaxHP),
				mDamageBar->GetHeight(),
				RGB(255, 0, 255));

			::TransparentBlt(
				// target
				_hdc,
				168.0f - 82.0f,
				654.0f + 22.0f,
				mHpBar->GetWidth() * hpPercent * 2.0f,
				mHpBar->GetHeight() * 2.0f,
				// source
				mHpBar->GetHdc(),
				0, 0,
				mHpBar->GetWidth() * hpPercent,
				mHpBar->GetHeight(),
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
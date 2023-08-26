#include "vanHpBar.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanPlayer.h"
#include "vanSceneManager.h"
namespace van
{
	HpBar::HpBar()
	{

	}

	HpBar::~HpBar()
	{

	}

	void HpBar::Init()
	{
		UI::Init();

		mHpBar = ResourceManager::Load<Texture>(L"UI_Player_HpBar", L"..\\MyResources\\skul\\UI\\HpBar.bmp");
		mDamageBar = ResourceManager::Load<Texture>(L"UI_Player_HpBar_Damage", L"..\\MyResources\\skul\\UI\\HpBar_Damage.bmp");;
	}

	void HpBar::Update()
	{
		UI::Update();

		if (mPlayer == nullptr)
		{
			GameObject* obj = SceneManager::GetActiveScene()->GetSceneTarget();
			mPlayer = dynamic_cast<Player*>(obj);
		}
		else
		{
			if (mReductionHp >= mPlayer->GetHp())
			{
				mReductionHp -= Time::GetDeltaTime() * 50.0f;
			}
			else
			{
				mReductionHp = mPlayer->GetHp();
			}
		}

	}

	void HpBar::Render(HDC _hdc)
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

	void HpBar::MakeAnimation()
	{
	}

	void HpBar::OnCollisionEnter(Collider* _other)
	{
	}

	void HpBar::OnCollisionStay(Collider* _other)
	{
	}

	void HpBar::OnCollisionExit(Collider* _other)
	{
	}
}
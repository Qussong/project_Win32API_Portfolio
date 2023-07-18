#include "vanTexture.h"
#include "vanApplication.h"
#include "vanResourceManager.h"
#include "vanCamera.h"

extern van::Application application;

namespace van
{
	Texture::Texture()
		: mImage(nullptr)
		, mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
		, mType(eTextureType::None)
		//, mbAffectCamera(true)
	{
		// nothing
	}

	Texture::~Texture()
	{
		delete mImage;	// 메모리 릭 방지
		mImage = nullptr;

		::DeleteObject(mBitmap);
		mBitmap = NULL;
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		// bmp 일때
		if (ext == L"bmp")
		{
			mType = eTextureType::Bmp;
			mBitmap = (HBITMAP)::LoadImageW(
							nullptr
							, path.c_str()
							, IMAGE_BITMAP
							, 0, 0
							, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr)
				return E_FAIL;	// 강사님 "S_FALSE" 사용

			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);

			if (info.bmBitsPixel == 32)
				mType = eTextureType::AlphaBmp;

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = application.GetHdc();
			mHdc = CreateCompatibleDC(mainDC);

			HBITMAP deafultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(deafultBitmap);
		}
		else if (ext == L"png")
		{
			mType = eTextureType::Png;
			mImage = Gdiplus::Image::FromFile(path.c_str());	// *.png 파일을 이용하여 Texture 객체를 생성

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}
		else
			__noop;

		return S_OK;		// == 0L
	}

	Texture* Texture::Create(const std::wstring& _name, UINT _width, UINT _height)
	{
		Texture* image = ResourceManager::Find<Texture>(_name);
		if (image != nullptr)
			return image;

		image = new Texture();
		image->SetWidth(_width);
		image->SetHeight(_height);
		HDC hdc = application.GetHdc();
		HBITMAP bitmap = CreateCompatibleBitmap(hdc, _width, _height);
		image->SetHBitmap(bitmap);

		HDC bitmapHdc = CreateCompatibleDC(hdc);
		image->SetHdc(bitmapHdc);

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(bitmapHdc, bitmap);
		DeleteObject(defaultBitmap);

		image->SetName(_name);
		image->SetType(eTextureType::AlphaBmp);
		ResourceManager::Insert<Texture>(_name, image);

		return image;
	}

	void Texture::Render(HDC _hdc
		, math::Vector2 _pos
		, math::Vector2 _size
		, math::Vector2 _leftTop
		, math::Vector2 _rightBottom
		, bool mbAffectCamera
		, math::Vector2 _offset
		, math::Vector2 _scale
		, float _alpha)
	{
		if (mBitmap == nullptr && mImage == nullptr)
			return;

		if (mbAffectCamera)
			_pos = Camera::CalculatePosition(_pos);

		if (mType == eTextureType::Bmp)
		{
			TransparentBlt(
				// target
				_hdc
				, (int)_pos.x - (_size.x * _scale.x / 2.0f) + _offset.x
				, (int)_pos.y - (_size.y * _scale.y / 2.0f) + _offset.y
				, _size.x * _scale.x
				, _size.y * _scale.y
				// source
				, mHdc
				, _leftTop.x
				, _leftTop.y
				, _rightBottom.x
				, _rightBottom.y
				// option
				, RGB(255, 0, 255));
		}
		else if (mType == eTextureType::AlphaBmp)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			int alpha = 1.0f;
			alpha = (int)(alpha * 255.0f);	// 0.0f ~ 1.0f -> 0 ~ 255

			if (alpha <= 0)
				alpha = 0;

			func.SourceConstantAlpha = alpha;

			AlphaBlend(
				// target
				_hdc
				, (int)_pos.x - (_size.x * _scale.x / 2.0f) + _offset.x
				, (int)_pos.y - (_size.y * _scale.y / 2.0f) + _offset.y
				, _size.x * _scale.x
				, _size.y * _scale.y
				// source
				, mHdc
				, _leftTop.x
				, _leftTop.y
				, _rightBottom.x
				, _rightBottom.y
				// option
				, func);
		}
		else if (mType == eTextureType::Png)
		{
			// 내가 원하는 픽셀을 투명화 시킬떄
			Gdiplus::ImageAttributes imageAtt = {};
			// 투명화 시킬 픽셀 색 범위
			imageAtt.SetColorKey(
				Gdiplus::Color(100, 100, 100)
				, Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(_hdc);
			graphics.DrawImage(
				mImage
				, Gdiplus::Rect(
					(int)(_pos.x - (_size.x * _scale.x / 2.0f) + _offset.x)
					, (int)(_pos.y - (_size.y * _scale.y / 2.0f) + _offset.y)
					, (int)(_size.x * _scale.x)
					, (int)(_size.y * _scale.y))
				, _leftTop.x
				, _leftTop.y
				, _rightBottom.x
				, _rightBottom.y
				, Gdiplus::UnitPixel
				, nullptr);
		}
		else
			__noop;
	}

}
#pragma once
#include "vanResource.h"

namespace van
{
	enum class eTextureType
	{
		Bmp,
		Png,
		None,
	};

	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& path) override;

		__forceinline UINT GetWidth() { return mWidth; }
		__forceinline UINT GetHeight() { return mHeight; }
		__forceinline HDC GetHdc() { return mHdc; }
		__forceinline eTextureType GetType() { return mType; }
		__forceinline Gdiplus::Image* GetImage() { return mImage; }

	private:
		eTextureType mType;
		Gdiplus::Image* mImage;
		/*
			Gdiplus::Image 안되aus "framework.h" 에서
			"#define WIN32_LEAN_AND_MEAN" 주석처리하기
		*/

		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}


#pragma once
#include "vanResource.h"

namespace van
{
	class Image : public Resource
	{
	public:
		Image();
		virtual ~Image();

		virtual HRESULT Load(const std::wstring& path) override;

		__forceinline UINT GetWidth() { return mWidth; }
		__forceinline UINT GetHeight() { return mHeight; }
		__forceinline HDC GetHdc() { return mHdc; }

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}


#pragma once
#include "vanResource.h"

namespace van
{
	enum class eTextureType
	{
		Bmp,
		AlphaBmp,
		Png,
		None,
	};

	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& path) override;

		static Texture* Create(
			const std::wstring& _name
			, UINT _width
			, UINT _height);

		void Render(
			HDC _hdc
			, math::Vector2 _pos
			, math::Vector2 _size
			, math::Vector2 _leftTop
			, math::Vector2 _rightBottom
			, bool mbAffectCamera = true
			, math::Vector2 _offset = math::Vector2::Zero
			, math::Vector2 _scale = math::Vector2::One
			, float _alpha = 1.0f);

		__forceinline UINT GetWidth() { return mWidth; }
		__forceinline void SetWidth(UINT _width) { mWidth = _width; }

		__forceinline UINT GetHeight() { return mHeight; }
		__forceinline void SetHeight(UINT _height) { mHeight = _height; }

		// static_cast : 당연히 되는 정적인 형변환만 허용한다.
		// C++ 스타일, 더 안전하다.
		math::Vector2 GetSize() { return math::Vector2(static_cast<float>(mWidth), static_cast<float>(mHeight)); }

		__forceinline HDC GetHdc() { return mHdc; }
		__forceinline void SetHdc(HDC _hdc) { mHdc = _hdc; }

		__forceinline eTextureType GetType() { return mType; }
		__forceinline void SetType(eTextureType _type) { mType = _type; }

		__forceinline Gdiplus::Image* GetImage() { return mImage; }

		__forceinline void SetHBitmap(HBITMAP _bitmap) { mBitmap = _bitmap; }

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
		//bool mbAffectCamera;
	};
}


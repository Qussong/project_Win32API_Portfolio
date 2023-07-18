#pragma once
#include "vanEntity.h"

namespace van
{
	class Resource : public Entity	// 순수가상함수에 의해 추상클래스가 된다.
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& _path) = 0;	// 순수가상함수

		__forceinline std::wstring& GetPath() { return mPath; }
		__forceinline void SetPath(const std::wstring& _path) { mPath = _path; }

	private:
		std::wstring mPath;	// 리소스의 경로
	};
}


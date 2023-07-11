#pragma once
#include "CommonInclude.h"

namespace van
{
	class Entity							
	{
	public:
		Entity();
		virtual ~Entity();	// 소멸자에 항상 virtual 키워드를 붙여주면 후에 상속되어도 문제 발생이 적어진다.

		__forceinline void SetName(const std::wstring& name) 
												{ mName = name; }	// setter
		__forceinline std::wstring& GetName() { return mName; }		// getter

	private:
		std::wstring mName;	// 이름 저장하는 용도 
	};
}
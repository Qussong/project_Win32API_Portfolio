#pragma once
#include "CommonInclude.h"

namespace van
{
	class Entity							// 상속해서 사용해줄 것 
											// -> Question) 어차피 상속할거면 추상 클래스로 만들어주면 안되나?
	{
	public:
		Entity();
		virtual ~Entity();					// 소멸자에 항상 virtual 키워드를 붙여주면 후에 상속되어도 문제 발생이 적어진다.

		void SetName(std::wstring& name);	// setter
		std::wstring& GetName();			// getter

	private:
		std::wstring mName;					// 이름 저장하는 용도 
	};
}
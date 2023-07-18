#pragma once
#include "vanResource.h"

namespace van
{
	class ResourceManager
	{
	public:
		// 리소스가 이미 로드 되어 있는지 확인
		template <typename T>
		static T* Find(const std::wstring& _name)	
		{
			auto iter = mResources.find(_name);		// map.find()는 해당 객체를 찾지 못하면 map.end()를 반환한다.
			if (iter == mResources.end())			// 해당 이름을 가진 리소스가 없으면 nullptr return 
				return nullptr;

			return dynamic_cast<T*>(iter->second);	// 해당 이름을 가진 리소스가 있으면 해당 리소스의 주소값 반환
		}

		// 리소스를 불러와 mResources에 저장한다.
		template <typename T>
		static T* Load(const std::wstring& _name
						, const std::wstring& _path)	
		{
			T* resource = ResourceManager::Find<T>(_name);	// 해당 리소스를 mResources에서 탐색

			if (resource != nullptr)
				return resource;
			
			resource = new T();
			if (FAILED(resource->Load(_path)))				// 해당 값이 0보다 작으면 false
			{
				MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);
				delete resource;
				return nullptr;
			}

			resource->SetName(_name);
			resource->SetPath(_path);
			mResources.insert(std::make_pair(_name, resource));

			return resource;
		}

		// 특정 Resource를 mResources에 저장한다.
		template <typename T>
		static void Insert(const::std::wstring& _name, T* _resource)
		{
			_resource->SetName(_name);
			mResources.insert(std::make_pair(_name, _resource));
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}


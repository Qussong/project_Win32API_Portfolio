#pragma once
#include "vanResource.h"

namespace van
{
	class ResourceManager
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& _name)
		{
			auto iter = mResources.find(_name);	// map.find()는 해당 객체를 찾지 못하면 map.end()를 반환한다.
			if (iter == mResources.end())
				return nullptr;

			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& _name, const std::wstring& _path)
		{
			T* resource = ResourceManager::Find<T>(_name);

			if (resource != nullptr)
				return resource;
			
			resource = new T();
			if (FAILED(resource->Load(_path)))
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

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}


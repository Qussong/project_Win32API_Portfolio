#pragma once
#include "vanScene.h"

namespace van
{
	class SceneManager
	{
	public:
		static void Init();
		static void Update();
		static void Render(HDC _hdc);
		static void Release();

		template <typename T>
		__forceinline static T* CreateScene(const std::wstring& name)
		{
			T* scene = new T();
			scene->SetName(name);
			mScenes.insert(std::make_pair(name, scene));	// mScenes 에 생성된 scene 넣기
			mActiveScene = scene;							// mActiveScene 설정
			scene->Init();									// GameObject 객체 생성

			return scene;
		}
		__forceinline static Scene* LoadScene(const std::wstring& name);
		__forceinline static Scene* GetActiveScene() { return mActiveScene; }

		static void Next(const std::wstring& name);
		static void Previous(const std::wstring& name);
		__forceinline static bool GetColliderVisibleFlag() { return mbColliderVisible; }

	private:
		/*
			트리 자료구조 사용할 예정
			-> 이유 : 최악의 경우를 가정했을 때 원하는 값 찾는 속도가 빠르다.

			[ map ]
			- key,value 구조로 이루어져있다.
			- key는 원하는 값을 검색하는 용도
			- value는 사용할 값(=찾는 값)
		 */
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;
		static bool mbColliderVisible;
	};
}


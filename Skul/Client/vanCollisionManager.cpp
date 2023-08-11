#include "vanCollisionManager.h"
#include "vanScene.h"
#include "vanSceneManager.h"

namespace van
{
    std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
    std::bitset<LAYER_MAX> CollisionManager::mLayerMasks[LAYER_MAX] = {};

    void CollisionManager::Init()
    {
        // nothing
    }

    void CollisionManager::Update()
    {
        Scene* activeScene = SceneManager::GetActiveScene();

        for (size_t row = 0; row < LAYER_MAX; ++row)
        {
            for (size_t col = 0; col < LAYER_MAX; ++col)
            {
                if (mLayerMasks[row][col] == true)
                {
                    LayerCollision(activeScene, (eLayerType)row, (eLayerType)col);
                }
            }
        }
    }

    void CollisionManager::Render(HDC hdc)
    {
        // nothing
    }

    void CollisionManager::Release()
    {
        // nothing
    }

    void CollisionManager::Clear()
    {
        //mLayerMasks->reset();   // 비트셋의 비트들을 전부 0으로 세팅 (정적)
        for (int i = 0; i < LAYER_MAX; i++)
        {
            mLayerMasks[i].reset();
        }
        mCollisionMap.clear();  // map의 모든 요소를 지운다. 즉, map을 비운다. (동적)
    }

    void CollisionManager::SetCollisionLayerCheck(eLayerType _left, eLayerType _right, bool _enable)
    {
        int row = -1;
        int col = -1;

        if (_left > _right)
        {
            row = (UINT)_left;
            col = (UINT)_right;
        }
        else
        {
            col = (UINT)_left;
            row = (UINT)_right;
        }

        mLayerMasks[row][col] = _enable;    // 레이어들 간의 충돌체크 여부 설정
    }

    bool CollisionManager::Intersect(Collider* _left, Collider* _right)
    {
        math::Vector2 leftPos = _left->GetPos();    // _left 인자의 위치 좌표 저장
        math::Vector2 rightPos = _right->GetPos();  // _right 인자의 위치 좌표 저장

        math::Vector2 leftSize = _left->GetSize();      // _left 인자의 크기 저장
        math::Vector2 rightSize = _right->GetSize();    // _right 인자의 크기 저장

        // 두 사각형의 중심사이의 거리가 각 사각형의 너비/높이 값의 절반의 합보다 작으면 충돌상태
        if (::fabs(leftPos.x - rightPos.x) < ::fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
            && ::fabs(leftPos.y - rightPos.y) < ::fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
        {
            return true;
        }

        return false;
    }

    void CollisionManager::ColliderCollision(Collider* _left, Collider* _right)
    {
        // 두 충돌체의 ID를 확인
        ColliderID ID;
        ID.left = (UINT)_left->GetCollisionNum();   // 파라미터로 들어온 첫번째 인자의 충돌체 ID 저장
        ID.right = (UINT)_right->GetCollisionNum(); // 파라미터로 들어온 두번째 인자의 충돌체 ID 저장


        // 이전 충돌체의 정보를 가져와서 확인한다.
        std::map<UINT64, bool>::iterator iter
            = mCollisionMap.find(ID.id);    // 정보가 없다면 map.end() 반환

        // 혹시 충돌정보가 없다면 생성해주면된다
        if (iter == mCollisionMap.end())
        {
            mCollisionMap.insert(std::make_pair(ID.id, false));
            iter = mCollisionMap.find(ID.id);
        }

        // 충돌함수 호출
        if (Intersect(_left, _right))   // 충돌상태
        {
            if (iter->second == false)  // 처음 충돌하는 상태
            {
                _left->OnCollisionEnter(_right);
                _right->OnCollisionEnter(_left);

                iter->second = true;
            }
            else  // 충돌 중인상태
            {
                _left->OnCollisionStay(_right);
                _right->OnCollisionStay(_left);
            }
        }
        else  // 비충돌상태
        {
            if (iter->second == true)   // 충돌을 빠져나간상태
            {
                _left->OnCollisionExit(_right);
                _right->OnCollisionExit(_left);

                iter->second = false;
            }
        }
    }

    void CollisionManager::LayerCollision(Scene* _scene, eLayerType _left, eLayerType _right)
    {
        // finds left layer objects
        Layer& leftLayer = _scene->GetLayer(_left); // 해당 Scene에서 _left에 해당하는 layer를 저장
        std::vector<GameObject*>& lefts = leftLayer.GetGameObjects();   // 해당 레이어(leftLayer)의 GameObject 객체들을 가리키는 변수 생성

        Layer& rightLayer = _scene->GetLayer(_right);   // 해당 Scene에서 _right에 해당하는 layer를 저장
        std::vector<GameObject*>& rights = rightLayer.GetGameObjects(); // 해당 레이어(rightLayer)의 GameObject 객체들을 가리키는 변수 생성

        // finds right layer Objects
        for (GameObject* leftObj : lefts)   // leftLayer 에 속하는 GameObject를 하나씩 호출
        {
            Collider* leftCol = leftObj->GetComponent<Collider>();  // leftLayer 에 속하는 GameObject의 Collider 속성 저장
            if (leftCol == nullptr) // 해당 GameObject 객체에 Collider 속성이 없다면 다음 GameObject 객체 호출
                continue;

            for (GameObject* rightObj : rights) // rightLayer 에 속하는 GameObject를 하나씩 호출
            {
                Collider* rightCol = rightObj->GetComponent<Collider>();    // 해당 GameObject 객체의 Collider 속성 저장
                if (rightCol == nullptr)    // 해당 GameObject 객체에 Collider 속성이 없다면 다음 객체 호출
                    continue;
                if (leftObj == rightObj)    // 비교대상이 본인이면 다음 객체 호출
                    continue;

                ColliderCollision(leftCol, rightCol);   // 두 객체의 충돌과정에(enter, stay, exit)따른 영향 계산
            }
        }
    }
}
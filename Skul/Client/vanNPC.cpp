#include "vanNPC.h"
#include "vanRigidBody.h"

namespace van
{
    NPC::NPC()
        : mState(NPCState::None)
        , mPastState(NPCState::None)
        , mDirection(NPCDirection::None)
        , mPastDirection(NPCDirection::None)
        , mTimer(0.0f)
        , mbPatrol(false)
        , mbPlayAnimation(false)
    {
        AddComponent<RigidBody>();
    }

    NPC::~NPC()
    {
        // nothing
    }

    void NPC::Init()
    {
        // nothing
    }

    void NPC::Update()
    {
        GameObject::Update();
    }

    void NPC::Render(HDC _hdc)
    {
        GameObject::Render(_hdc);
    }

    void NPC::MakeAnimation()
    {
        // nothing
    }

    void NPC::Idle()
    {
        // nothing
    }

    void NPC::Walk()
    {
        // nothing
    }

    void NPC::Patrol()
    {
        // nothing
    }
}
#include "vanNPC.h"
#include "vanRigidBody.h"

namespace van
{
    NPC::NPC()
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
}
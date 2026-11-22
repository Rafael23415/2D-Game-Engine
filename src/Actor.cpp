#include "Actor.h"

namespace Engineering2D
{
    Actor::Actor(Vector2D position, Vector2D scale, SpriteSheet* spriteSheet) : m_position(position), m_scale(scale), m_active(true), m_spriteSheet(spriteSheet)
    {
    }

    void Actor::Destroy()
    {
        m_waitingDestroy = true;
    }

    void Actor::SetActive(bool active)
    {
        m_active = active;
    }

    bool Actor::IsActive() const
    {
        return m_active;
    }

    bool Actor::IsWaitingDestroy() const
    {
        return m_waitingDestroy;
    }
}

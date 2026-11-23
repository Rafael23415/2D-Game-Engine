#include "Actor.h"

namespace Engineering2D
{
    Actor::Actor(Vector2D position, Vector2D scale, Texture* texture) : m_position(position), m_scale(scale), m_active(true), m_texture(texture)
    {
    }

    Actor::Actor(Actor&& actor) noexcept
    {
        m_position = actor.m_position;
        m_scale = actor.m_scale;
        m_texture = actor.m_texture;
        m_active = actor.m_active;
        m_waitingDestroy = actor.m_waitingDestroy;

        actor.m_texture = nullptr;
    }

    Actor& Actor::operator=(Actor&& actor) noexcept
    {
        m_position = actor.m_position;
        m_scale = actor.m_scale;
        m_texture = actor.m_texture;
        m_active = actor.m_active;
        m_waitingDestroy = actor.m_waitingDestroy;

        actor.m_texture = nullptr;
        
        return *this;
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

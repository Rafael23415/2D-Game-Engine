#include "Actor.h"
#include "Debug.h"

namespace Engineering2D
{
    using namespace Math;

    Actor::Actor(Vector2D position, Vector2D scale, std::weak_ptr<Texture> texture) : m_position(position), m_scale(scale), m_active(true), m_texture(texture)
    {
        Debug::Log("Created an Actor");
    }

    Actor::Actor(Actor&& actor) noexcept
    {
        m_position = actor.m_position;
        m_scale = actor.m_scale;
        m_texture = actor.m_texture;
        m_active = actor.m_active;
        m_waitingDestroy = actor.m_waitingDestroy;

        Debug::Log("Created an Actor from another actor");
    }

    Actor& Actor::operator=(Actor&& actor) noexcept
    {
        m_position = actor.m_position;
        m_scale = actor.m_scale;
        m_texture = actor.m_texture;
        m_active = actor.m_active;
        m_waitingDestroy = actor.m_waitingDestroy;
        
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

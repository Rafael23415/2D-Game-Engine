#pragma once

#include "Vector2D.h"
#include "TextureManager.h"

namespace Engineering2D
{
    using namespace Math;

    class Actor
    {
    public:
    
        Actor(Vector2D position, Vector2D scale, std::weak_ptr<Texture> texture);
        virtual ~Actor() = default;
    
        Actor(const Actor& actor) = delete;
        Actor& operator=(const Actor& actor) = delete;

        Actor(Actor&& actor) noexcept;
        Actor& operator=(Actor&& actor) noexcept;

        virtual void Update(double deltaTime) = 0;
        virtual void Destroy();
        
        virtual void SetActive(bool active);
        bool IsActive() const;
        bool IsWaitingDestroy() const;
    
    protected:
    
        Vector2D m_position;
        Vector2D m_scale;
        std::weak_ptr<Texture> m_texture;
        bool m_active = true;
        bool m_waitingDestroy = false;
    };
}

#pragma once

#include "Vector2D.h"
#include "TextureManager.h"

#include <memory>
#include <string>

namespace Engineering2D
{
    class Actor
    {
    public:
        Actor(std::string name, Math::Vector2D position, Math::Vector2D scale);
        virtual ~Actor() = default;
    
        Actor(const Actor& actor) = delete;
        Actor& operator=(const Actor& actor) = delete;

        Actor(Actor&& actor) noexcept;
        Actor& operator=(Actor&& actor) noexcept;

        void SetTexture(std::shared_ptr<Texture> texture);

        virtual void Update(double deltaTime) = 0;
        virtual void Destroy();
        
        virtual void SetActive(bool active);
        bool IsActive() const;
        bool IsWaitingDestroy() const;
    
    protected:
        std::string m_name;
        Math::Vector2D m_position;
        Math::Vector2D m_scale;
        std::weak_ptr<Texture> m_texture;
        bool m_active = true;
        bool m_waitingDestroy = false;
    };
}

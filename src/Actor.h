#pragma once

#include "SpriteSheet.h"
#include "Vector2D.h"

namespace Engineering2D
{
    class Actor
    {
    public:
    
        Actor(Vector2D position, Vector2D scale, SpriteSheet* spriteSheet);
        virtual ~Actor() = default;
    
        virtual void Update(double deltaTime) = 0;
        virtual void Destroy();
        
        virtual void SetActive(bool active);
        bool IsActive() const;
        bool IsWaitingDestroy() const;
    
    protected:
    
        Vector2D m_position;
        Vector2D m_scale;
        SpriteSheet* m_spriteSheet;
        bool m_active = true;
        bool m_waitingDestroy = false;
    };
}

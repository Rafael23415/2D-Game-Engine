#pragma once

#include <vector>
#include <memory>

#include "Graphics.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "Actor.h"
#include "Vector2DInt.h"

namespace Engineering2D
{
    /**
     * Scene where every entity in the game lives.
     */
    class Scene
    {
    public:
        Scene(const char* name, const Vector2DInt& windowSize, const Vector2DInt& worldSize);
        ~Scene() = default;
        
        void Start();
        void Update();
        void ShutDown();

        void CreateActor(Actor* actor);
        
        std::shared_ptr<Texture> CreateTexture(const char* filePath);

        bool IsRunning() const;
        
    private:
        const Vector2DInt m_worldSize;
        
        std::unique_ptr<Graphics> m_graphics;
        std::unique_ptr<InputManager> m_inputManager;
        std::unique_ptr<TextureManager> m_textureManager;
        
        std::vector<std::unique_ptr<Actor>> m_actors;
        
        bool m_isRunning;
    };
}

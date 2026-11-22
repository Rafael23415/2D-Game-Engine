#pragma once

#include <vector>
#include <memory>

#include "Program.h"
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
        
        ~Scene();
        
        void Start();
        void Update();
        void ShutDown();
        void CreateEntity(Actor& actor);
        
        Program& GetProgram() const;
        TextureManager& GetTextureManager() const;
        bool IsRunning() const;
        
    private:
        const Vector2DInt worldSize;
        
        std::unique_ptr<Program> program;
        std::unique_ptr<InputManager> inputManager;
        std::unique_ptr<TextureManager> textureManager;
        
        std::vector<std::unique_ptr<Actor>> actors;
        
        bool isRunning;
    };
}

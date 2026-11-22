#include "Scene.h"

#include <stdexcept>

namespace Engineering2D
{
    Scene::Scene(const char* name, const Vector2DInt& windowSize, const Vector2DInt& worldSize) : worldSize(worldSize)
    {
        if (windowSize.x <= 0 || windowSize.y <= 0)
        {
            throw std::invalid_argument{"The window size must be greater than zero."};
        }

        if (worldSize.x <= 0 || worldSize.y <= 0)
        {
            throw std::invalid_argument{"The world size must be greater than zero."};
        }
        
        isRunning = true;
        
        program = std::make_unique<Program>(name, windowSize);
        inputManager = std::make_unique<InputManager>();
        textureManager = std::make_unique<TextureManager>();
    }
    
    Scene::~Scene()
    {
        if (!actors.empty())
        {
            for (auto& actor : actors)
            {
                actor.reset();
            }
        }
    }
    
    void Scene::Start()
    {
        program->SetVSync(true);
        program->SetColor(255, 0, 255);
        
        Update();
    }

    void Scene::Update()
    {
        static Uint64 prevTime;
        static Uint64 currentTime;
        static float deltaTime;
        
        prevTime = currentTime;
        currentTime = SDL_GetTicksNS();
        deltaTime = (currentTime - prevTime) / 1e9f;
        
        while (isRunning)
        {
            inputManager->ProcessInput();
            
            if (inputManager->IsWaitingShutdown())
            {
                isRunning = false;
            }
            
            program->ClearRenderer();
            program->PresentRenderer();
            
            for (auto i = actors.begin(); i != actors.end(); ++i)
            {
                (*i)->Update(deltaTime);
                
                if ((*i)->IsWaitingDestroy())
                {
                    actors.erase(i);
                }
            }
        }
    }

    void Scene::ShutDown()
    {
        isRunning = false;
    }

    void Scene::CreateEntity(Actor& actor)
    {
        const auto a = std::make_unique<Actor>(actor);
        
        actors.push_back(std::move(a));
    }
    
    Program& Scene::GetProgram() const
    {
        return *program;
    }

    TextureManager& Scene::GetTextureManager() const
    {
        return *textureManager;
    }

    bool Scene::IsRunning() const
    {
        return isRunning;
    }
}

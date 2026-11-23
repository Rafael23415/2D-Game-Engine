#include "Scene.h"

#include <stdexcept>
#include <SDL3/SDL_timer.h>

namespace Engineering2D
{
    Scene::Scene(const char* name, const Vector2DInt& windowSize, const Vector2DInt& worldSize) : m_worldSize(worldSize)
    {
        if (windowSize.x <= 0 || windowSize.y <= 0)
        {
            throw std::invalid_argument{"The window size must be greater than zero."};
        }

        if (worldSize.x <= 0 || worldSize.y <= 0)
        {
            throw std::invalid_argument{"The world size must be greater than zero."};
        }
        
        m_isRunning = true;
        
        m_graphics = std::make_unique<Graphics>(name, windowSize);
        m_inputManager = std::make_unique<InputManager>();
        m_textureManager = std::make_unique<TextureManager>();
    }
    
    Scene::~Scene()
    {
        if (!m_actors.empty())
        {
            for (auto& actor : m_actors)
            {
                actor.reset();
            }
        }
    }
    
    void Scene::Start()
    {
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
        
        while (m_isRunning)
        {
            m_inputManager->ProcessInput();
            
            if (m_inputManager->IsWaitingShutdown())
            {
                m_isRunning = false;
            }
            
            m_graphics->ClearRenderer();
            
            for (auto i = m_actors.begin(); i != m_actors.end(); ++i)
            {
                (*i)->Update(deltaTime);
                
                if ((*i)->IsWaitingDestroy())
                {
                    m_actors.erase(i);
                }
            }

            m_graphics->SwapWindow();
        }
    }

    void Scene::ShutDown()
    {
        m_isRunning = false;
    }

    template<typename T, typename... Args>
    void Scene::CreateEntity(Args&&... args)
    {
        const auto a = std::make_unique<T>(std::forward<Args>(args)...);
        
        m_actors.push_back(std::move(a));
    }
    
    Graphics& Scene::GetProgram()
    {
        return *m_graphics;
    }

    TextureManager& Scene::GetTextureManager()
    {
        return *m_textureManager;
    }

    bool Scene::IsRunning() const
    {
        return m_isRunning;
    }
}

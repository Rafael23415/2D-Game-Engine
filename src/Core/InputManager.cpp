#include "InputManager.h"

namespace Engineering2D
{
    void InputManager::ProcessInput()
    {
        while (SDL_PollEvent(&m_ev)) {
            // Getting the events
            if (m_ev.type == SDL_EVENT_QUIT)
            {
                m_isWaitingShutdown = true;
            }
        }
    }
    void InputManager::BindAction(const std::string& actionName, Key keybind)
    {
        //keybinds[actionName] = keybind;
    }

    bool InputManager::IsPressed(const std::string& actionName)
    {
        return false;
    }

    bool InputManager::IsWaitingShutdown() const
    {
        return m_isWaitingShutdown;
    }
}

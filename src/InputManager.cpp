#include "InputManager.h"

namespace Engineering2D
{

    void InputManager::ProcessInput()
    {
        while (SDL_PollEvent(&ev)) {
            // Getting the events
            if (ev.type == SDL_EVENT_QUIT)
            {
                m_waitingShutdown = true;
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
        return IsWaitingShutdown;
    }
}

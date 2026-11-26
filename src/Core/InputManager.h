#pragma once

#include <SDL3/SDL_events.h>
#include <map>
#include <string>

namespace Engineering2D
{
    enum Key {

    };

    /**
     * 
     */
    class InputManager
    {
    public:
        InputManager() = default;
        ~InputManager() = default;
        
        void ProcessInput();
        void BindAction(const std::string& actionName, Key keybind);
        bool IsPressed(const std::string& actionName);
        
        bool IsWaitingShutdown() const;
    
    private:
        SDL_Event m_ev;

        //std::map<const std::string&, SDL_Keycode> keybinds;
        
        bool m_isWaitingShutdown = false;
    };
}

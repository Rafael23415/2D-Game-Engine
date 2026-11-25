#pragma once

#include <iostream>

namespace Debug {

	template<typename... Args>
	void Log(Args&&... args)
	{
		((std::cout << "[Log]: ") << ... << args) << std::endl;
	}
	
	template<typename... Args>
	void LogWarning(Args&&... args)
	{
		((std::cout << "\x1b[33m[Warning]: ") << ... << args) << "\x1b[0m" << std::endl;
	}
	
	template<typename... Args>
	void LogError(Args&&... args)
	{
		((std::cout << "\x1b[31m[Error]: ") << ... << args) << "\x1b[0m" << std::endl;
	}
}

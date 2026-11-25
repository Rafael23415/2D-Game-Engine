#pragma once

#include <iostream>
#include <string_view>

namespace Debug {

	template<typename... T>
	void Log(T&... message)
	{
		std::cout << "[Log]: " << std::forward(message)... << std::endl;
	}
	//void Log(std::string_view message);
	void LogWarning(std::string_view message);
	void LogError(std::string_view message);
};

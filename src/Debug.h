#pragma once

#include <iostream>
#include <string_view>
#include <string>

namespace Debug {

	//template<typename... Args>
	void Log(std::string_view message);
	void LogWarning(std::string_view message);
	void LogError(std::string_view message);
};

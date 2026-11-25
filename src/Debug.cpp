#include "Debug.h"

//void Debug::Log(std::string_view message)
//{
//	std::cout << "[Log]: " << message << std::endl;
//}

void Debug::LogWarning(std::string_view message)
{
	std::cout << "\x1b[33m[Warning]: " << message << "\x1b[0m" << std::endl;
}

void Debug::LogError(std::string_view message)
{
	std::cout << "\x1b[31m[Error]: " << message << "\x1b[0m" << std::endl;
}

#pragma once

#include <ctime>
#include <iostream>
#include <iomanip>

class Logger
{
public:
	enum class Level
	{
		Info
	};

public:
	template<class ... Args>
	static void Log(Level level, Args&& ... params)
	{
		switch (level)
		{
		case Level::Info:
			std::cout << "[Info]";
			break;
		}
		std::time_t crtTime = std::time(nullptr);
		std::cout << '[' << std::put_time(std::localtime(&crtTime), "%Y-%m-%d %H:%M:%S") << ']';
		((std::cout << ' ' << std::forward<Args>(params)), ...);
		std::cout << '\n';
	}
};

template<class ... Args>
void logi(Args&& ... params)
{
	Logger::Log(Logger::Level::Info, std::forward<Args>(params)...);
}

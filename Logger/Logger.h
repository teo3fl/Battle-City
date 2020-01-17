#pragma once

#ifdef LOGGING_EXPORTS
     #define LOGGER __declspec(dllexport)
#else
     #define LOGGER __declspec(dllexport)
#endif

#include <chrono>
#include <iomanip>
#include <fstream>

class LOGGER Logger
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
		std::ofstream outputFile;
		outputFile.open("../Logger/logger.txt", std::ios::out | std::ios::app);
		switch (level)
		{
		case Level::Info:
			outputFile<< "[Info]";
			break;
		}
		/*std::time_t crtTime = std::time(nullptr);
		outputFile << '[' << std::put_time(std::localtime(&crtTime), "%Y-%m-%d %H:%M:%S") << ']';*/
		((outputFile << ' ' << std::forward<Args>(params)), ...);
		outputFile << '\n';
		outputFile.close();
	}
};

template<class ... Args>
void logi(Args&& ... params)
{
	Logger::Log(Logger::Level::Info, std::forward<Args>(params)...);
}

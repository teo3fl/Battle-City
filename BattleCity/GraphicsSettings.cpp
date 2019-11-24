#include "GraphicsSettings.h"
#include <fstream>

GraphicsSettings::GraphicsSettings()
{
	m_title = "DEFAULT";
	m_resolution = sf::VideoMode::getDesktopMode();
	m_fullscreen = false;
	m_frameRateLimit = 120;
	m_contextSettings.antialiasingLevel = 0;
}

void GraphicsSettings::LoadFromFile(const std::string& path)
{
	std::ifstream in(path);

	if (in.is_open())
	{
		std::getline(in, m_title);
		in >> m_resolution.width >> m_resolution.height;
		in >> m_fullscreen;
		in >> m_frameRateLimit;
		in >> m_verticalSync;
		in >> m_contextSettings.antialiasingLevel;
	}

	in.close();
}

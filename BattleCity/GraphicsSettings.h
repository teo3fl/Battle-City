#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class GraphicsSettings
{
public:
	GraphicsSettings();
	void LoadFromFile(const std::string& path);

public:
	std::string m_title;
	sf::VideoMode m_resolution;
	bool m_fullscreen;
	bool m_verticalSync;
	uint16_t m_frameRateLimit;
	sf::ContextSettings m_contextSettings;
};
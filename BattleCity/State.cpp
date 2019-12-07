#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
	m_window = window;
	m_supportedKeys = supportedKeys;
	m_quit = false;
}

State::~State()
{
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Escape)))
	{
		m_quit = true;
	}
}

const bool& State::getQuit() const
{
	return m_quit;
}


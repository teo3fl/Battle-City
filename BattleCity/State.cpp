#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
	m_window = window;
	m_supportedKeys = supportedKeys;
	m_quit = false;
}

State::~State()
{
	for (auto it = this->m_buttons.begin(); it != m_buttons.end(); ++it)
		delete it->second;
}

void State::CheckForQuit()
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Escape)))
	{
		m_quit = true;
	}
}

const bool& State::GetQuit() const
{
	return m_quit;
}


#include "State.h"

State::State(sf::RenderWindow* window)
{
	m_window = window;
	m_quit = false;
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


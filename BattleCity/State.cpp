#include "stdafx.h"
#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
	m_window = window;
	m_supportedKeys = supportedKeys;
	m_quit = false;


	m_keytime = 0.f;
	m_keytimeMax = 10.f;
}

State::~State()
{

}

void State::CheckForQuit()
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Escape)) && GetKeytime())
	{
		m_quit = true;
	}
}

void State::UpdateKeytime(const float& dt)
{
	if (m_keytime < m_keytimeMax)
		m_keytime += 100.f * dt;
}

const bool& State::GetQuit() const
{
	return m_quit;
}

const bool State::GetKeytime()
{
	if (m_keytime >= m_keytimeMax)
	{
		m_keytime = 0.f;
		return true;
	}

	return false;
}


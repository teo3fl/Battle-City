#include "stdafx.h"
#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
	m_window = window;
	m_supportedKeys = supportedKeys;
	m_quit = false;

	m_keytime = 0.f;
	m_keytimeMax = 20.f;
}

State::~State()
{

}

void State::SetText(sf::Text& text, const sf::Font& font, const sf::Color& fillColor, uint16_t size, const sf::Vector2f& position, float thickness)
{
	text.setFillColor(fillColor);
	text.setFont(font);
	text.setCharacterSize(size);
	text.setPosition(position);
	text.setOutlineThickness(thickness);
	text.setOutlineColor(fillColor);
}

void State::SetText(sf::Text& text, const sf::Font& font, const sf::Color& fillColor, uint16_t size, float thickness)
{
	text.setFillColor(fillColor);
	text.setFont(font);
	text.setCharacterSize(size);
	text.setOutlineThickness(thickness);
	text.setOutlineColor(fillColor);
}

void State::CheckForQuit()
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Escape)) && GetKeytime())
	{
		m_quit = true;
	}
}

void State::LoadHighScore()
{
	std::ifstream score("../External/Resources/Config/high_score.ini");

	if (score.is_open())
		score >> m_highScore;
	else
		m_highScore = 0;

	m_highScoreText.setString(std::to_string(m_highScore));
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


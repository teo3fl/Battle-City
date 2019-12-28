#include "KeybindState.h"

KeybindState::KeybindState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, sf::Font* font, sf::Color color, uint8_t size)
	: State(window, supportedKeys), m_font(font)
{
	InitializeText(color, size);
}

void KeybindState::InitializeKeybinds()
{

}

void KeybindState::InitializeBackground()
{
	m_background.setSize(sf::Vector2f(1100.f, 1000.f));
	m_background.setFillColor(sf::Color::Black);
}

void KeybindState::InitializeText(sf::Color color, uint8_t size)
{
	std::stringstream ss;
	
	ss <<
		"Move up\n" <<
		"Move down\n" <<
		"Move left\n" <<
		"Move Right\n" <<
		"Shoot\n" <<
		"Back to Main Meniu\n";

	m_actions.setFont(*m_font);
	m_actions.setString(ss.str());
	m_actions.setFillColor(color);
	m_actions.setCharacterSize(size);
	m_actions.setPosition(20, 20);
		
	ss.str(std::string());

	ss <<
		"W\n" <<
		"S\n" <<
		"A\n" <<
		"D\n" <<
		"???\n" <<
		"Escape\n";

	m_keybinds.setFont(*m_font);
	m_keybinds.setString(ss.str());
	m_keybinds.setFillColor(color);
	m_keybinds.setCharacterSize(size);
	m_keybinds.setPosition(500, 20);
}

void KeybindState::UpdateInput(const float& dt)
{
	CheckForQuit();
}

void KeybindState::Update(const float& dt)
{
	UpdateInput(dt);
}

void KeybindState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	target->draw(m_background);
	target->draw(m_actions);
	target->draw(m_keybinds);
}

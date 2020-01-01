#include "stdafx.h"
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
	std::stringstream ss_keys;
	std::stringstream ss_actions;
	
	std::ifstream in("../External/Resources/Config/gamestate_keybinds.ini");

	if (in.is_open())
	{
		std::string action = "";
		std::string key = "";

		while (in >> action >> key)
		{
			ss_actions << action << std::endl;
			ss_keys << key << std::endl;
		}
	}
	else
		throw "ERROR::KEYBINDS_STATE::KEYBINDS_NOT_FOUND";

	in.close();


	//ss_actions <<
	//	"Move up\n" <<
	//	"Move down\n" <<
	//	"Move left\n" <<
	//	"Move Right\n" <<
	//	"Shoot\n" <<
	//	"Back to Main Meniu\n";

	m_actions.setFont(*m_font);
	m_actions.setString(ss_actions.str());
	m_actions.setFillColor(color);
	m_actions.setCharacterSize(size);
	m_actions.setPosition(20, 20);


	//ss_keys <<
	//	"W\n" <<
	//	"S\n" <<
	//	"A\n" <<
	//	"D\n" <<
	//	"???\n" <<
	//	"Escape\n";

	m_keybinds.setFont(*m_font);
	m_keybinds.setString(ss_keys.str());
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
	UpdateKeytime(dt);
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

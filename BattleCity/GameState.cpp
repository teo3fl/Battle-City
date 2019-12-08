#include "GameState.h"


GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	this->InitializeKeybinds();
}

GameState::~GameState()
{
}

void GameState::InitializeKeybinds()
{
	this->m_keybinds.emplace("MOVE_LEFT", this->m_supportedKeys->at("A"));
	this->m_keybinds.emplace("MOVE_RIGHT", this->m_supportedKeys->at("D"));
	this->m_keybinds.emplace("MOVE_UP", this->m_supportedKeys->at("W"));
	this->m_keybinds.emplace("MOVE_DOWN", this->m_supportedKeys->at("S"));
}


void GameState::EndState()
{
	std::cout << "Ending GameState!" << "\n";
}

void GameState::UpdateInput(const float& dt)
{
	CheckForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_LEFT"))))
		this->m_player.move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_RIGHT"))))
		this->m_player.move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_UP"))))
		this->m_player.move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_DOWN"))))
		this->m_player.move(dt, 0.f, 1.f);
	
}


void GameState::Update(const float& dt)
{
	UpdateInput(dt);

	m_player.update(dt);
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	this->m_player.render(target);
}

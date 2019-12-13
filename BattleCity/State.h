﻿#ifndef STATE_H
#define STATE_H

#include "Entity.h"

class State
{

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*> m_states);
	virtual ~State();
	virtual void InitializeKeybinds() = 0;

	const bool& GetQuit() const;

	virtual void CheckForQuit();

	virtual void EndState() = 0;
	virtual void UpdateInput(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;

protected:
	sf::RenderWindow* m_window;
	std::map<std::string, int>* m_supportedKeys;
	std::map<std::string, int> m_keybinds;
	bool m_quit;

	//Resources
	std::map<std::string, sf::Texture> m_textures;
	std::stack<State*> m_states;
	std::map<std::string, Button*> m_buttons;

};
#endif

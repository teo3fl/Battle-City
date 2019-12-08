﻿#ifndef STATE_H
#define STATE_H

#include "Entity.h"

class State
{
protected:
	sf::RenderWindow* m_window;
	std::map<std::string, int>* m_supportedKeys;
	std::map<std::string, int> m_keybinds;
	bool m_quit;

	//Resources
	std::vector<sf::Texture> m_textures;
	
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~State();
	virtual void ItitializeKeybinds() = 0;

	const bool& GetQuit() const;

	virtual void CheckForQuit();
	
	virtual void EndState() = 0;
	virtual void UpdateInput(const float& dt) =0;
	virtual void Update(const float& dt) =0;
	virtual void Render(sf::RenderTarget* target = nullptr) =0;
};
#endif

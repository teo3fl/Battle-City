#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <stack>
#include <vector>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class State
{
private:
	std::vector<sf::Texture> m_textures;
	sf::RenderWindow* m_window;
	bool m_quit;
	
public:
	State(sf::RenderWindow* window);

	virtual void checkForQuit();
	const bool& getQuit() const;

	virtual void updateKeybinds(const float &dt) = 0;
	virtual void update(const float& dt) =0;
	virtual void render(sf::RenderTarget* target = nullptr) =0;
};
#endif

#ifndef STATE_H
#define STATE_H

#include "Entity.h"

class State
{
private:
	sf::RenderWindow* m_window;
	std::map<std::string, int>* m_supportedKeys;
	std::map<std::string, int> m_keybinds;
	bool m_quit;

	//Resources
	std::vector<sf::Texture> m_textures;
	
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~State();
	virtual void ititializeKeybinds() = 0;

	const bool& getQuit() const;

	virtual void checkForQuit();
	
	virtual void endState() = 0;
	virtual void updateInput(const float& dt) =0;
	virtual void update(const float& dt) =0;
	virtual void render(sf::RenderTarget* target = nullptr) =0;
};
#endif

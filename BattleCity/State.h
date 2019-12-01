#ifndef STATE_H
#define STATE_H

#include "Entity.h"

class State
{
private:
	std::vector<sf::Texture> m_textures;
	sf::RenderWindow* m_window;
	bool m_quit;
	
public:
	State(sf::RenderWindow* window);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	
	virtual void endState() = 0;
	virtual void updateInput(const float& dt) =0;
	virtual void update(const float& dt) =0;
	virtual void render(sf::RenderTarget* target = nullptr) =0;
};
#endif

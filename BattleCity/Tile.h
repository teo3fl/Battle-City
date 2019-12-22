#pragma once
#include <string>

#include "Entity.h"

class Tile
{
public:
	Tile(int x, int y, const sf::Texture& texture);
	void SetTexture(const sf::Texture& texture);
	void SetPosition(int x, int y);
	//virtual void Update(const float& dt);
	void Render(sf::RenderTarget* target);

	virtual const std::string GetType() const = 0;
	virtual bool IsPassable() const = 0;
	virtual bool IsBreakable() const = 0;

protected:
	sf::Sprite m_sprite;
};

#pragma once
#include <string>

#include "Entity.h"

class Tile
{
public:
	Tile(const float x, const float y, const sf::Texture& texture);
	void SetTexture(const sf::Texture& texture);
	void SetPosition(const float x, const float y);
	virtual void Update(const float& dt);
	void Render(sf::RenderTarget* target);

	virtual const std::string GetType() const = 0;
	virtual bool IsPassable() const = 0;
	virtual bool IsBreakable() const = 0;

private:
	sf::Sprite m_sprite;
};

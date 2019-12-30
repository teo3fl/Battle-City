#pragma once

#include "Hitbox.h"

class Tile
{
public:
	Tile(int x, int y, const sf::Texture& texture);

	void SetTexture(const sf::Texture& texture);
	void SetPosition(int x, int y);
	void CreateHitbox(sf::Sprite& sprite);

	virtual const sf::FloatRect GetGlobalBounds() const;
	virtual const bool Intersects(const sf::FloatRect bounds) const;

	virtual void Update(const float& dt);
	void Render(sf::RenderTarget* target);

	virtual const std::string GetType() const = 0;
	virtual bool IsPassable() const = 0;
	virtual bool IsBreakable() const = 0;

protected:
	sf::Sprite m_sprite;
	Hitbox* m_hitbox;

	uint8_t m_width;
	uint8_t m_height;
};

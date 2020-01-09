#pragma once

#include "Hitbox.h"

class BasicTile
{
public:
	BasicTile(int x, int y, const sf::Texture& texture);

	virtual void SetTexture(const sf::Texture& texture);
	virtual void SetPosition(int x, int y);
	virtual void CreateHitbox(sf::Sprite& sprite);

	virtual const sf::FloatRect GetGlobalBounds() const;
	virtual const bool Intersects(const sf::FloatRect bounds) const;

	void Render(sf::RenderTarget* target);

protected:
	sf::Sprite m_sprite;
	Hitbox* m_hitbox;

	uint8_t m_width;
	uint8_t m_height;
};


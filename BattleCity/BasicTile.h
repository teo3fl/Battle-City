#pragma once

#include "Hitbox.h"

class BasicTile
{
public:
	BasicTile(int x, int y, const sf::Texture& texture);

	void SetTexture(const sf::Texture& texture);
	void SetPosition(int x, int y);
	void CreateHitbox(sf::Sprite& sprite);

	const sf::FloatRect GetGlobalBounds() const;
	const bool Intersects(const sf::FloatRect bounds) const;

	void Render(sf::RenderTarget* target);

protected:
	sf::Sprite m_sprite;
	Hitbox* m_hitbox;

	uint8_t m_width;
	uint8_t m_height;
};


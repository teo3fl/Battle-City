#include "Tile.h"

Tile::Tile(const float x, const float y, const sf::Texture& texture)
{
	SetTexture(texture);
}

void Tile::SetTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
}

void Tile::SetPosition(const float x, const float y)
{
	m_sprite.setPosition(x, y);
}

void Tile::Render(sf::RenderTarget* target)
{
	target->draw(m_sprite);
}

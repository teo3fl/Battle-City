#include "stdafx.h"
#include "Tile.h"

Tile::Tile(int x, int y, const sf::Texture& texture)
{
	SetTexture(texture);
	SetPosition(x, y);
}

void Tile::SetTexture(const sf::Texture& texture)
{
	m_sprite.scale(sf::Vector2f(0.5f, 0.5f));
	m_sprite.setTexture(texture);
}

void Tile::SetPosition(int x, int y)
{
	m_sprite.setPosition(x, y);
}

void Tile::Render(sf::RenderTarget* target)
{
	target->draw(m_sprite);
}

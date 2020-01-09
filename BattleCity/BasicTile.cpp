#include "stdafx.h"
#include "BasicTile.h"

BasicTile::BasicTile(int x, int y, const sf::Texture& texture)
{
	SetTexture(texture);
	SetPosition(x, y);
}

void BasicTile::SetTexture(const sf::Texture& texture)
{
	m_sprite.scale(sf::Vector2f(0.5f, 0.5f));
	m_sprite.setTexture(texture);
}

void BasicTile::SetPosition(int x, int y)
{
	m_sprite.setPosition(x, y);
}

void BasicTile::CreateHitbox(sf::Sprite& sprite)
{
	m_hitbox = new Hitbox(m_sprite, m_width, m_height);
}

const sf::FloatRect BasicTile::GetGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

const bool BasicTile::Intersects(const sf::FloatRect bounds) const
{
	return m_sprite.getGlobalBounds().intersects(bounds);
}

void BasicTile::Render(sf::RenderTarget* target)
{
	target->draw(m_sprite);
	if (m_hitbox)
		m_hitbox->Render(target);
}

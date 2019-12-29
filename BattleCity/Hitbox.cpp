#include "stdafx.h"
#include "Hitbox.h"

Hitbox::Hitbox(sf::Sprite& sprite, float x, float y, float width, float height) : 
	m_sprite(sprite), m_x(x), m_y(y)
{
	m_hitbox.setPosition(m_sprite.getPosition().x , m_sprite.getPosition().y);
	m_hitbox.setSize(sf::Vector2f(width, height));
	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOutlineThickness(1.f);
	m_hitbox.setOutlineColor(sf::Color::Green);
}

Hitbox::~Hitbox()
{
}

bool Hitbox::Intersects(const sf::FloatRect& frect)
{
	return m_hitbox.getGlobalBounds().intersects(frect);
}

const sf::Vector2f& Hitbox::GetPosition() const
{
	return m_hitbox.getPosition();
}

const sf::FloatRect Hitbox::GetGlobalBounds() const
{
	return m_hitbox.getGlobalBounds();
}

void Hitbox::Update()
{
	m_hitbox.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);
}

void Hitbox::Render(sf::RenderTarget& target)
{
	target.draw(m_hitbox);
}

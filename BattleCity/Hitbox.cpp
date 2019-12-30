#include "stdafx.h"
#include "Hitbox.h"

Hitbox::Hitbox(sf::Sprite& sprite, float width, float height) : 
	m_sprite(sprite)
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

const sf::FloatRect& Hitbox::GetNextPosition(const sf::Vector2f& velocity)
{
	m_nextPosition.left = m_hitbox.getPosition().x + velocity.x;
	m_nextPosition.top = m_hitbox.getPosition().y + velocity.y;

	return m_nextPosition;
}

void Hitbox::Update()
{
	m_hitbox.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);
}

void Hitbox::Render(sf::RenderTarget* target)
{
	target->draw(m_hitbox);
}

#include "Entity.h"

Entity::Entity()
{
	this->m_movementSpeed = 100.f;
}

Entity::~Entity()
{
}

void Entity::SetTexture(sf::Texture& texture)
{
	m_sprite.setTexture(texture);
}

void Entity::SetPosition(const float x, const float y)
{
	m_sprite.setPosition(x, y);
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	this->m_sprite.move(dir_x * this->m_movementSpeed * dt, dir_y * this->m_movementSpeed * dt);
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(m_sprite);
}



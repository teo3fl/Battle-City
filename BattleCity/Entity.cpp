#include "Entity.h"

Entity::Entity()
{
	this->m_shape.setSize(sf::Vector2f(50.f, 50.f));
	this->m_shape.setFillColor(sf::Color::White);
	this->m_movementSpeed = 100.f;

}

Entity::~Entity()
{
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	this->m_shape.move(dir_x * this->m_movementSpeed * dt, dir_y * this->m_movementSpeed * dt);
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->m_shape);
}



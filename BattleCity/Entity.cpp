#include "Entity.h"

Entity::Entity()
{
	m_movementSpeed = 100.f;
	m_sprite.scale(sf::Vector2f(0.5f, 0.5f));
}

Entity::~Entity()
{
}

void Entity::AddTexture(const sf::Texture& texture, const std::string& textureName)
{
	m_textures[textureName] = texture;
}

void Entity::SetTexture(const std::string& texture)
{
	m_sprite.setTexture(m_textures[texture]);
}

void Entity::SetPosition(const float x, const float y)
{
	m_sprite.setPosition(x, y);
}

void Entity::Move(const float& dt, const float dir_x, const float dir_y)
{
	this->m_sprite.move(dir_x * this->m_movementSpeed * dt, dir_y * this->m_movementSpeed * dt);
}

void Entity::Update(const float& dt)
{
	
}

void Entity::Render(sf::RenderTarget* target)
{
	target->draw(m_sprite);
}



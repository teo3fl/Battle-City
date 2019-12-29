#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	delete m_hitbox;
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

void Entity::CreateHitbox(sf::Sprite& sprite, float width, float height)
{
	m_hitbox = new Hitbox(m_sprite, width, height);
}

void Entity::Move(const float& dt, const float dir_x, const float dir_y)
{
	this->m_sprite.move(dir_x * this->m_movementSpeed * dt, dir_y * this->m_movementSpeed * dt);
}



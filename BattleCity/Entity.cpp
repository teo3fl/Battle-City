#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
	InitializeVariables();
}

Entity::~Entity()
{
	delete m_hitbox;
	delete m_movementComponent;
}

void Entity::InitializeVariables()
{
	m_hitbox = NULL;
	m_movementComponent = NULL;
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

void Entity::CreateMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	m_movementComponent = new MovementComponent(m_sprite, maxVelocity, acceleration, deceleration);
}

const sf::Vector2f& Entity::GetPosition() const
{
	if (m_hitbox)
		return m_hitbox->GetPosition();

	return m_sprite.getPosition();
}

const sf::FloatRect Entity::GetGlobalBounds() const
{
	if (m_hitbox)
		return m_hitbox->GetGlobalBounds();

	return m_sprite.getGlobalBounds();
}

const sf::FloatRect Entity::GetNextPositionBounds(const float& dt) const
{
	if (m_hitbox && m_movementComponent)
		return m_hitbox->GetNextPosition(m_movementComponent->GetVelocity() * dt);

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

void Entity::Move(const float& dt, const float dir_x, const float dir_y)
{
	if (m_movementComponent)
		m_movementComponent->Move(dir_x, dir_y, dt); //Sets velocity

}

void Entity::StopVelocityX()
{
	if (m_movementComponent)
		m_movementComponent->StopVelocityX();
}

void Entity::StopVelocityY()
{
	if (m_movementComponent)
		m_movementComponent->StopVelocityY();
}



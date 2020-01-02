#pragma once

#include "Entity.h"

enum class BulletType
{
	Slow = 0,
	Normal,
	Fast
};

enum class BulletSource
{
	Player = 0,
	Enemy
};

class Bullet :
	public Entity
{
public:
	Bullet(float x, float y, sf::Vector2f direction, const sf::Texture& texture, BulletType type, BulletSource source);

	void SetSpeed();

	BulletSource GetSource();
	uint8_t GetHealth();

	void Update(const float& dt) override;

	virtual void Render(sf::RenderTarget* target = nullptr) override;

private:
	BulletType m_type : 2;
	uint8_t m_health : 2;
	BulletSource m_source : 1;
	sf::Vector2f m_direction;
};


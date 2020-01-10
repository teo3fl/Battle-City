#pragma once 

#include "BasicTile.h"

enum class PowerUpType
{
	Grenade,
	Helmet,
	Shovel,
	Star,
	Tank,
	Timer
};

class PowerUp : public BasicTile
{

public:
	PowerUp(sf::Vector2f coordinates, const sf::Texture& texture, PowerUpType type);
	PowerUpType GetType();

private:
	PowerUpType m_type : 3;
};
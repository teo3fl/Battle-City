#pragma once

#include "BasicTile.h"

class Tile : public BasicTile
{
public:
	Tile(int x, int y, const sf::Texture& texture);

	virtual const uint8_t GetHealth();
	virtual std::string& GetType();

	virtual bool GetTankCollision();
	virtual bool GetBulletCollision();

protected:
	std::string m_type;

	bool m_tankCollision:1;
	bool m_bulletCollision:1;
};

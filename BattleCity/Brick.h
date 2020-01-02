#pragma once
#include "Tile.h"
class Brick : public Tile
{
public:
	Brick(int x, int y, const sf::Texture& texture);

	const uint8_t GetHealth() override;
};


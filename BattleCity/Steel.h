#pragma once
#include "Tile.h"
class Steel : public Tile
{
public:
	Steel(int x, int y, const sf::Texture& texture);

	const uint8_t GetHealth() override;
};


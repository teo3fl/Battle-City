#pragma once
#include "Tile.h"
class Brick : public Tile
{
public:
	Brick(int x, int y, const sf::Texture& texture);

	const std::string GetType() const override;
	bool IsPassable() const override ;
	bool IsBreakable()const override;
private:
	const std::string m_type = "Brick";
	const bool m_isPassable = false;
	const bool m_isBreakable = true;

};


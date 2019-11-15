#pragma once
#include "Tile.h"
class Water : public Tile
{
public:
	const std::string GetType() const override;
	bool IsPassable() const override;
	bool IsBreakable()const override;

private:
	const std::string m_type = "Water";
	const bool m_isPassable = false;
	const bool m_isBreakable = false;
};

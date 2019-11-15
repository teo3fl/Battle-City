#pragma once
#include "Tile.h"
class Ice : public Tile
{
public:
	const std::string GetType() const override;
	bool IsPassable() const override;
	bool IsBreakable()const override;

private:
	const std::string m_type = "Ice";
	const bool m_isPassable = true;
	const bool m_isBreakable = false;
};

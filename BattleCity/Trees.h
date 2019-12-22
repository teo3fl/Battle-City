#pragma once
#include "Tile.h"
class Trees : public Tile
{
public:
	Trees(const float x, const float y, const sf::Texture& texture);

	const std::string GetType() const override;
	bool IsPassable() const override;
	bool IsBreakable()const override;

private:
	const std::string m_type = "Trees";
	const bool m_isPassable = true;
	const bool m_isBreakable = false;
};


#pragma once
#include <cstdint>

class Tile
{
private:
	enum class TileType : uint8_t
	{
		BrWall,
		StWall,
		Trees,
		Water,
		Ice
	};

public:
	Tile(TileType type);

	TileType GetType() const;
	bool IsPassable() const;
	bool IsBreakable() const;
	uint8_t GetHealth() const;

	void SetHealth(uint8_t health);

private:
	TileType m_type : 2;
	bool m_isPassable : 1;
	bool m_isBreakable : 1;
	uint8_t m_health : 2;
};


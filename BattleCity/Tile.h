#pragma once
#include <string>

class Tile
{
public:
	virtual const std::string GetType() const = 0;
	virtual bool IsPassable() const = 0;
	virtual bool IsBreakable() const = 0;
};

#pragma once

#include "Brick.h"
#include "Ice.h"
#include "Steel.h"
#include "Trees.h"
#include "Water.h"

#include "Tile.h"

#include <vector>

class TileMap
{
public:


private:

	std::vector<std::vector<std::vector<Tile*>>> map;
};


#include "stdafx.h"
#include "AiMap.h"

AiMap::AiMap(uint16_t width, uint16_t height)
	: m_width(width), m_height(height)
{
	m_map.resize(m_height);
	for (int x = 0; x < m_height; x++)
		m_map[x].resize(m_width);
}

void AiMap::LoadFromFile(const std::string& fileName)
{
	std::ifstream in(fileName);


	if (in.is_open())
		for (uint16_t y = 0; y < m_height; y++)
			for (uint16_t x = 0; x < m_width; x++)
				in >> m_map[x][y];
	else
		throw "ERROR::AI_MAP::COULD NOT LOAD FROM FILE::FILENAME: " + fileName;
	in.close();
}

void AiMap::Clear(uint16_t x, uint16_t y)
{
	if (x >= m_width)
		throw "ERROR::AI_MAP::X_OUT_OF_BOUNDS";
	if (y >= m_height)
		throw "ERROR::AI_MAP::X_OUT_OF_BOUNDS";

	m_map[x][y] = 0;
}

#pragma once
#include "stdafx.h"

class AiMap
{
public:
	AiMap(uint16_t width, uint16_t height);

	void LoadFromFile(const std::string& fileName);

	void Clear(uint16_t x, uint16_t y);

private:
	size_t m_width;
	uint16_t m_height;
	std::vector<std::vector<uint8_t>> m_map;

};


#pragma once

#include "AiMap.h"

typedef std::pair<int, int> Pair;
typedef std::pair<double, std::pair<int, int>> pPair;
// A structure to hold the necessary parameters 
struct cell
{
	int parent_i, parent_j;
	double f, g, h;
};

class AiComponent
{
public:
	static const uint16_t m_row = 52;
	static const uint16_t m_col = 52;

public:
	AiComponent(const uint16_t& currentRow, const uint16_t& currentCol);

	static bool IsValid(const uint16_t& m_currentRow, const uint16_t& m_currentCol);
	static bool IsUnBlocked(const uint16_t& m_currentRow, const uint16_t& m_currentCol);
	static bool IsDestination(const uint16_t& m_currentRow, const uint16_t& m_currentCol, Pair dest);
	double CalculateHValue(uint16_t m_currentRow, int16_t m_currentCol, Pair dest) const;
	void TracePath(cell cellDetails[][m_row], Pair dest);
	
	uint16_t m_currentRow{};
	uint16_t m_currentCol{};
	
	static std::shared_ptr<AiMap> m_aiMap;

};

#pragma once

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
	AiComponent(const uint16_t& currentRow, const uint16_t& currentCol);

	static bool isValid(const uint16_t& m_currentRow, const uint16_t& m_currentCol);
	//static bool isUnBlocked(grid[][]?, const uint16_t& m_currentRow, const uint16_t& m_currentCol); discutie :D
	static bool isDestination(const uint16_t& m_currentRow, const uint16_t& m_currentCol, Pair dest);
	double calculateHValue(uint16_t m_currentRow, int16_t m_currentCol, Pair dest) const;
	//void tracePath(cell cellDetails[][m_row], Pair dest)
	
private:

	static const uint16_t m_row = 52;
	static const uint16_t m_col = 52;
	
	uint16_t m_currentRow{};
	uint16_t m_currentCol{};
	


};

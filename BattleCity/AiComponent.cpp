#include "stdafx.h"
#include "AiComponent.h"
#include <utility>

AiComponent::AiComponent(const uint16_t& currentRow, const uint16_t& currentCol) :
	m_currentRow(currentRow),
	m_currentCol(currentCol)
{
}

bool AiComponent::IsValid(const uint16_t& m_currentRow, const uint16_t& m_currentCol)
{
	// Returns true if row number and column number 
	// is in range 
	return (m_currentRow >= 0) && (m_currentRow < m_row) &&
		(m_currentCol >= 0) && (m_currentCol < m_col);
}

bool AiComponent::IsDestination(const uint16_t& m_currentRow, const uint16_t& m_currentCol, Pair dest)
{
	if (m_currentRow == dest.first && m_currentCol == dest.second)
		return true;
	else
		return false;
}

bool AiComponent::IsUnBlocked(const uint16_t& m_currentRow, const uint16_t& m_currentCol)
{
	if (m_aiMap->m_map[m_currentRow][m_currentCol] == 0)
		return true;
	else
		return false;

	// GOTTA DO SHIT HERE, THIS AIN'T OK
}


double AiComponent::CalculateHValue(uint16_t m_currentRow, int16_t m_currentCol, Pair dest)
{
	return static_cast<double>(sqrt((m_currentRow - dest.first) * (m_currentRow - dest.first)
		+ (m_currentCol - dest.second) * (m_currentCol - dest.second)));
}

// A Utility Function to trace the path from the source 
// to destination

void AiComponent::tracePath(cell cellDetails[][AiComponent::m_row], Pair dest)
{
	printf("\nThe Path is ");
	auto row = dest.first;
	auto col = dest.second;

	std::stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row
		&& cellDetails[row][col].parent_j == col))
	{
		Path.push(std::make_pair(row, col));
		const auto temp_row = cellDetails[row][col].parent_i;
		const auto temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(std::make_pair(row, col));
	while (!Path.empty())
	{
		std::pair<int, int> p = Path.top();
		Path.pop();
		printf("-> (%d,%d) ", p.first, p.second);
	}

	return;
}

// A Function to find the shortest path between 
// a given source cell to a destination cell according 
// to A* Search Algorithm

void aStarSearch(int grid[][AiComponent::m_col], Pair src, Pair dest)
{
	// If the source is out of range 
	if (AiComponent::IsValid(src.first, src.second) == false)
	{
		printf("Source is invalid\n");
		return;
	}

	// If the destination is out of range 
	if (AiComponent::IsValid(dest.first, dest.second) == false)
	{
		printf("Destination is invalid\n");
		return;
	}

	// Either the source or the destination is blocked 
	if (AiComponent::IsUnBlocked(src.first, src.second) == false ||
		AiComponent::IsUnBlocked(dest.first, dest.second) == false)
	{
		printf("Source or the destination is blocked\n");
		return;
	}

	// If the destination cell is the same as source cell 
	if (AiComponent::IsDestination(src.first, src.second, dest) == true)
	{
		printf("We are already at the destination\n");
		return;
	}

	// Create a closed list and initialise it to false which means 
	// that no cell has been included yet 
	// This closed list is implemented as a boolean 2D array 
	bool closedList[AiComponent::m_row][AiComponent::m_col];
	memset(closedList, false, sizeof(closedList));

	// Declare a 2D array of structure to hold the details 
	//of that cell 
	const int row = AiComponent::m_row;
	const int col = AiComponent::m_col;
	cell cellDetails[row][col];

	int i, j;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node 
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	/*
	 Create an open list having information as-
	 <f, <i, j>>
	 where f = g + h,
	 and i, j are the row and column index of that cell
	 Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	 This open list is implenented as a set of pair of pair.*/
	std::set<pPair> openList;

	// Put the starting cell on the open list and set its 
	// 'f' as 0 
	openList.insert(std::make_pair(0.0, std::make_pair(i, j)));

	// We set this boolean value as false as initially 
	// the destination is not reached. 
	bool foundDest = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		// Remove this vertex from the open list 
		openList.erase(openList.begin());

		// Add this vertex to the closed list 
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		/*
		 Generating all the 8 successor of this cell

			 N.W   N   N.E
			   \   |   /
				\  |  /
			 W----Cell----E
				  / | \
				/   |  \
			 S.W    S   S.E

		 Cell-->Popped Cell (i, j)
		 N -->  North       (i-1, j)
		 S -->  South       (i+1, j)
		 E -->  East        (i, j+1)
		 W -->  West           (i, j-1)
		 N.E--> North-East  (i-1, j+1)
		 N.W--> North-West  (i-1, j-1)
		 S.E--> South-East  (i+1, j+1)
		 S.W--> South-West  (i+1, j-1)*/

		 // To store the 'g', 'h' and 'f' of the 8 successors 
		double gNew, hNew, fNew;

		//----------- 1st Successor (North) ------------ 

		// Only process this cell if this is a valid one 
		if (AiComponent::IsValid(i - 1, j) == true)
		{
			// If the destination cell is the same as the 
			// current successor 
			if (AiComponent::IsDestination(i - 1, j, dest) == true)
			{
				// Set the Parent of the destination cell 
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				printf("The destination cell is found\n");
				AiComponent::tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}
			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i - 1][j] == false &&
				AiComponent::IsUnBlocked(i - 1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = AiComponent::CalculateHValue(i - 1, j, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//                OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i - 1][j].f == FLT_MAX ||
					cellDetails[i - 1][j].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i - 1, j)));

					// Update the details of this cell 
					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parent_i = i;
					cellDetails[i - 1][j].parent_j = j;
				}
			}
		}

		//----------- 2nd Successor (South) ------------ 

		// Only process this cell if this is a valid one 
		if (AiComponent::IsValid(i + 1, j) == true)
		{
			// If the destination cell is the same as the 
			// current successor 
			if (AiComponent::IsDestination(i + 1, j, dest) == true)
			{
				// Set the Parent of the destination cell 
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
				printf("The destination cell is found\n");
				AiComponent::tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}
			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i + 1][j] == false &&
				AiComponent::IsUnBlocked(i + 1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = AiComponent::CalculateHValue(i + 1, j, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//                OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i + 1][j].f == FLT_MAX ||
					cellDetails[i + 1][j].f > fNew)
				{
					openList.insert(std::make_pair(fNew, std::make_pair(i + 1, j)));
					// Update the details of this cell 
					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parent_i = i;
					cellDetails[i + 1][j].parent_j = j;
				}
			}
		}

		//----------- 3rd Successor (East) ------------ 

		// Only process this cell if this is a valid one 
		if (AiComponent::IsValid(i, j + 1) == true)
		{
			// If the destination cell is the same as the 
			// current successor 
			if (AiComponent::IsDestination(i, j + 1, dest) == true)
			{
				// Set the Parent of the destination cell 
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				printf("The destination cell is found\n");
				AiComponent::tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i][j + 1] == false &&
				AiComponent::IsUnBlocked(i, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = AiComponent::CalculateHValue(i, j + 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//                OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i][j + 1].f == FLT_MAX ||
					cellDetails[i][j + 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i, j + 1)));

					// Update the details of this cell 
					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parent_i = i;
					cellDetails[i][j + 1].parent_j = j;
				}
			}
		}

		//----------- 4th Successor (West) ------------ 

		// Only process this cell if this is a valid one 
		if (AiComponent::IsValid(i, j - 1) == true)
		{
			// If the destination cell is the same as the 
			// current successor 
			if (AiComponent::IsDestination(i, j - 1, dest) == true)
			{
				// Set the Parent of the destination cell 
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
				printf("The destination cell is found\n");
				AiComponent::tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i][j - 1] == false &&
				AiComponent::IsUnBlocked(i, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = AiComponent::CalculateHValue(i, j - 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//                OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i][j - 1].f == FLT_MAX ||
					cellDetails[i][j - 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i, j - 1)));

					// Update the details of this cell 
					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}

		//----------- 5th Successor (North-East) ------------ 

		// Only process this cell if this is a valid one 
		if (AiComponent::IsValid(i - 1, j + 1) == true)
		{
			// If the destination cell is the same as the 
			// current successor 
			if (AiComponent::IsDestination(i - 1, j + 1, dest) == true)
			{
				// Set the Parent of the destination cell 
				cellDetails[i - 1][j + 1].parent_i = i;
				cellDetails[i - 1][j + 1].parent_j = j;
				printf("The destination cell is found\n");
				AiComponent::tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i - 1][j + 1] == false &&
				AiComponent::IsUnBlocked(i - 1, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = AiComponent::CalculateHValue(i - 1, j + 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//                OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i - 1][j + 1].f == FLT_MAX ||
					cellDetails[i - 1][j + 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i - 1, j + 1)));

					// Update the details of this cell 
					cellDetails[i - 1][j + 1].f = fNew;
					cellDetails[i - 1][j + 1].g = gNew;
					cellDetails[i - 1][j + 1].h = hNew;
					cellDetails[i - 1][j + 1].parent_i = i;
					cellDetails[i - 1][j + 1].parent_j = j;
				}
			}
		}

		//----------- 6th Successor (North-West) ------------ 

		// Only process this cell if this is a valid one 
		if (AiComponent::IsValid(i - 1, j - 1) == true)
		{
			// If the destination cell is the same as the 
			// current successor 
			if (AiComponent::IsDestination(i - 1, j - 1, dest) == true)
			{
				// Set the Parent of the destination cell 
				cellDetails[i - 1][j - 1].parent_i = i;
				cellDetails[i - 1][j - 1].parent_j = j;
				printf("The destination cell is found\n");
				AiComponent::tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i - 1][j - 1] == false &&
				AiComponent::IsUnBlocked(i - 1, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = AiComponent::CalculateHValue(i - 1, j - 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//                OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i - 1][j - 1].f == FLT_MAX ||
					cellDetails[i - 1][j - 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew, std::make_pair(i - 1, j - 1)));
					// Update the details of this cell 
					cellDetails[i - 1][j - 1].f = fNew;
					cellDetails[i - 1][j - 1].g = gNew;
					cellDetails[i - 1][j - 1].h = hNew;
					cellDetails[i - 1][j - 1].parent_i = i;
					cellDetails[i - 1][j - 1].parent_j = j;
				}
			}
		}

		//----------- 7th Successor (South-East) ------------ 

		// Only process this cell if this is a valid one 
		if (AiComponent::IsValid(i + 1, j + 1) == true)
		{
			// If the destination cell is the same as the 
			// current successor 
			if (AiComponent::IsDestination(i + 1, j + 1, dest) == true)
			{
				// Set the Parent of the destination cell 
				cellDetails[i + 1][j + 1].parent_i = i;
				cellDetails[i + 1][j + 1].parent_j = j;
				printf("The destination cell is found\n");
				AiComponent::tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i + 1][j + 1] == false &&
				AiComponent::IsUnBlocked(i + 1, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = AiComponent::CalculateHValue(i + 1, j + 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//                OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i + 1][j + 1].f == FLT_MAX ||
					cellDetails[i + 1][j + 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i + 1, j + 1)));

					// Update the details of this cell 
					cellDetails[i + 1][j + 1].f = fNew;
					cellDetails[i + 1][j + 1].g = gNew;
					cellDetails[i + 1][j + 1].h = hNew;
					cellDetails[i + 1][j + 1].parent_i = i;
					cellDetails[i + 1][j + 1].parent_j = j;
				}
			}
		}

		//----------- 8th Successor (South-West) ------------ 

		// Only process this cell if this is a valid one 
		if (AiComponent::IsValid(i + 1, j - 1) == true)
		{
			// If the destination cell is the same as the 
			// current successor 
			if (AiComponent::IsDestination(i + 1, j - 1, dest) == true)
			{
				// Set the Parent of the destination cell 
				cellDetails[i + 1][j - 1].parent_i = i;
				cellDetails[i + 1][j - 1].parent_j = j;
				printf("The destination cell is found\n");
				AiComponent::tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i + 1][j - 1] == false &&
				AiComponent::IsUnBlocked(i + 1, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = AiComponent::CalculateHValue(i + 1, j - 1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//                OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i + 1][j - 1].f == FLT_MAX ||
					cellDetails[i + 1][j - 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i + 1, j - 1)));

					// Update the details of this cell 
					cellDetails[i + 1][j - 1].f = fNew;
					cellDetails[i + 1][j - 1].g = gNew;
					cellDetails[i + 1][j - 1].h = hNew;
					cellDetails[i + 1][j - 1].parent_i = i;
					cellDetails[i + 1][j - 1].parent_j = j;
				}
			}
		}
	}

	// When the destination cell is not found and the open 
	// list is empty, then we conclude that we failed to 
	// reach the destiantion cell. This may happen when the 
	// there is no way to destination cell (due to blockages) 
	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");

	return;
}
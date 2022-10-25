#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <unordered_set>
#define printGrid printVec2(grid)
#define NEWLINE cout << endl;
#define RANDINT  rand() % colourPool.size()
#define CELL_KEY(x,y) to_string(x) + to_string(y)
#define COLOURCELL(row,col) grid[row][col] = gridColour
using namespace std;

void MakeGrid(vector<vector<string>> &grid)
{
	srand(time(0));
	// Create colour pool to populate the grid
	vector<string> colours = { "red", "green", "yellow", "blue", "purple", "black" };
	vector<string> colourPool;
	for (auto item : colours)
		colourPool.push_back(item.substr(0, 3));

	// Select Current Cell colour
	int cell_Index1 = RANDINT, cell_Index2;
	string cellColour1 = colourPool[cell_Index1], cellColour2;
	
	// Populate the grid
	for (int rowIndex = 0; rowIndex < 7; rowIndex++)
	{
		// Fill grid row by row
		vector<string> row = {};
		for (int colIndex = 0; colIndex < 8; colIndex++)
		{
			if (rowIndex > 0)
			{
				string neighbourColour = grid[rowIndex - 1][colIndex].substr(0, 3);
				while (neighbourColour == cellColour1)
				{ // If the colour's are same, change cellColour
					if (colIndex > 0)
					{
						string leftNeighbourColour = row[colIndex - 1].substr(0, 3);
						while (leftNeighbourColour == cellColour1 || neighbourColour == cellColour1)
						{ // Ensuring it's different from all neighbours
							cell_Index1 = RANDINT;
							cellColour1 = colourPool[cell_Index1];
						}
						break;
					}
					cell_Index1 = RANDINT;
					cellColour1 = colourPool[cell_Index1];
				}
			}
			// Select next cell colour
			cell_Index2 = RANDINT;
			while (cell_Index2 == cell_Index1)
				cell_Index2 = RANDINT;
			cellColour2 = colourPool[cell_Index2];

			// Assign cellColour1
			row.push_back(cellColour1+="  ");

			// Transfer variables
			cell_Index1 = cell_Index2;
			cellColour1 = cellColour2;
		}
		grid.push_back(row); // append finished row in grid
	}
	// Assign P1 and P2 starting positions
	grid[0][7] = "P-2  ";
	grid[6][0] = "P-1  ";
}

void printVec2(vector<vector<string>> Array)
{
	for (auto row : Array)
	{
		for (auto element : row)
			cout << element << "  ";
		NEWLINE
	}
}

void heading(int p1, int p2, int player)
{
	cout << "\n\t\t======  P1: "<< p1 << "\tP2: " << p2 << "  ======" << endl; // Display tiles filled
	cout << "OPTIONS: red, green, yellow, blue, purple, black" << endl; // Display options
	if (player == 1)
		cout << "Pick a colour (P1)   "; // Prompt player 1 to play
	else if (player == 2)
		cout << "Pick a colour (P2)   "; // Prompt player 2 to play
}
string playGame()
{
	vector<vector<string>> grid;
	int turn = 1;	
	MakeGrid(grid);
	printGrid;

	// Register starting positions in sets
	unordered_set <string> P1_Cells = {"60"};
	unordered_set <string> P2_Cells = {"07"};
	unordered_set<string> combinedCells = { "60","07" };

	// Main Loop
	while (P1_Cells.size() + P2_Cells.size() < 56)
	{
		if (turn == 1) // Player 1
		{
			string pickedColour, gridColour;
			heading(P1_Cells.size(), P2_Cells.size(), 1); // Display info

			// Receive Player Input
			cin >> pickedColour;
			while (!cin)
			{ // Ensure it's correct before proceeding
				cin.clear();
				cin.ignore(256, '\n');
				cin >> pickedColour;
			}

			// Clipping first 3 letters and changing to uppercase
			for (int i = 0; i < 3; i++)
				gridColour += toupper(pickedColour[i]);
			gridColour += "-1"; // P1 tag

			// Colouring Grid
			int row, col;
			for (auto pair : P1_Cells)
			{
				row = stoi(pair)/10;
				col = stoi(pair)%10;
				if (grid[row][col] == gridColour) // If we've checked this cell, skip
					continue;
				COLOURCELL(row, col);

				// Check Neighbours
				if (row - 1 >= 0) // Up
				{ // if (Top neighbour is same as picked colour)  && (isn't in P1Cells or P2Cells)
					if (grid[row-1][col].substr(0, 3) == pickedColour.substr(0,3) && combinedCells.find(CELL_KEY(row - 1, col)) == combinedCells.end())
					{
						P1_Cells.insert(CELL_KEY(row - 1, col));
						combinedCells.insert(CELL_KEY(row - 1, col));
						COLOURCELL(row - 1, col);
					}
				}
				if (row + 1 <= 6) // Down
				{ // if (Down neighbour is same as picked colour)  && (isn't in P1Cells or P2Cells)
					if (grid[row+1][col].substr(0, 3) == pickedColour.substr(0,3) && combinedCells.find(CELL_KEY(row + 1, col)) == combinedCells.end())
					{
						P1_Cells.insert(CELL_KEY(row + 1, col));
						combinedCells.insert(CELL_KEY(row + 1, col));
						COLOURCELL(row + 1, col);
					}
				}
				if (col - 1 >= 0) // Left
				{ // if (Left neighbour is same as picked colour)  && (isn't in P1Cells or P2Cells)
					if (grid[row][col-1].substr(0, 3) == pickedColour.substr(0,3) && combinedCells.find(CELL_KEY(row, col - 1)) == combinedCells.end())
					{
						P1_Cells.insert(CELL_KEY(row, col-1));
						combinedCells.insert(CELL_KEY(row, col - 1));
						COLOURCELL(row, col - 1);
					}
				}
				if (col + 1 <= 7) // Right
				{ // if (Right neighbour is same as picked colour)  && (isn't in P1Cells or P2Cells)
					if (grid[row][col+1].substr(0, 3) == pickedColour.substr(0,3) && combinedCells.find(CELL_KEY(row, col + 1)) == combinedCells.end())
					{
						P1_Cells.insert(CELL_KEY(row, col + 1));
						combinedCells.insert(CELL_KEY(row, col + 1));
						COLOURCELL(row, col + 1);
					}
				}

			}
			// Rotating Board for Player 2
			vector<vector<string>> rotatedGrid;
			for (int row = grid.size() - 1; row >= 0; row--)
			{
				vector<string> tempRow;
				for (int col = grid[0].size() - 1; col >= 0; col--)
				{
					tempRow.push_back(grid[row][col]);
				}
				rotatedGrid.push_back(tempRow);
			}
			printVec2(rotatedGrid); // Printing rotated board
			turn = 0;
		}
		else  // Player 2
		{
			string pickedColour, gridColour;
			heading(P1_Cells.size(), P2_Cells.size(), 2); // Display info

			// Receive Player Input
			cin >> pickedColour;
			while (!cin)
			{ // Ensure it's correct before proceeding
				cin.clear();
				cin.ignore(256, '\n');
				cin >> pickedColour;
			}

			// Clipping first 3 letters and changing to uppercase
			for (int i = 0; i < 3; i++)
				gridColour += toupper(pickedColour[i]);
			gridColour += "-2"; // P2 tag

			// Colouring Grid
			int row, col;
			for (auto pair : P2_Cells)
			{
				row = stoi(pair) / 10;
				col = stoi(pair) % 10;
				if (grid[row][col] == gridColour) // If we've checked this cell, skip
					continue;
				COLOURCELL(row, col);

				// Check Neighbours
				if (row - 1 >= 0) // Up
				{ // if (Top neighbour is same as picked colour)  && (isn't in P1Cells or P2Cells)
					if (grid[row - 1][col].substr(0, 3) == pickedColour.substr(0,3) && combinedCells.find(CELL_KEY(row - 1, col)) == combinedCells.end())
					{
						P2_Cells.insert(CELL_KEY(row - 1, col));
						combinedCells.insert(CELL_KEY(row - 1, col));
						COLOURCELL(row - 1, col);
					}
				}
				if (row + 1 <= 6) // Down
				{ // if (Down neighbour is same as picked colour)  && (isn't in P1Cells or P2Cells)
					if (grid[row + 1][col].substr(0, 3) == pickedColour.substr(0,3) && combinedCells.find(CELL_KEY(row + 1, col)) == combinedCells.end())
					{
						P2_Cells.insert(CELL_KEY(row + 1, col));
						combinedCells.insert(CELL_KEY(row + 1, col));
						COLOURCELL(row + 1, col);
					}
				}
				if (col - 1 >= 0) // Left
				{ // if (Left neighbour is same as picked colour)  && (isn't in P1Cells or P2Cells)
					if (grid[row][col - 1].substr(0, 3) == pickedColour.substr(0,3) && combinedCells.find(CELL_KEY(row, col - 1)) == combinedCells.end())
					{
						P2_Cells.insert(CELL_KEY(row, col - 1));
						combinedCells.insert(CELL_KEY(row, col - 1));
						COLOURCELL(row, col - 1);
					}
				}
				if (col + 1 <= 7) // Right
				{ // if (Right neighbour is same as picked colour)  && (isn't in P1Cells or P2Cells)
					if (grid[row][col + 1].substr(0, 3) == pickedColour.substr(0,3) && combinedCells.find(CELL_KEY(row, col + 1)) == combinedCells.end())
					{
						P2_Cells.insert(CELL_KEY(row, col + 1));
						combinedCells.insert(CELL_KEY(row, col + 1));
						COLOURCELL(row, col + 1);
					}
				}

			}			
			printGrid;
			turn = 1;
		}
	}
	if (P1_Cells.size() > P2_Cells.size())
		return "P1";
	else if (P1_Cells.size() < P2_Cells.size())
		return "P2";
	return "Draw";
}

int main()
{
	string winner = playGame();
	if (winner == "P1")
		cout << "\n\nPlayer 1 won" << endl;
	else if (winner == "P2")
		cout << "\n\nPlayer 2 won" << endl;
	else
		cout << "\n\nThis match was a Draw. Well Done to both players" << endl;
}	
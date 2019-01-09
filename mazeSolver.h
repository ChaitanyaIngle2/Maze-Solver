// Chaitanya Ingle
// Sec. 1002
// Ast. 08

// FILE: mazeSolver.h
// DESCRIPTION: Header file for mazeSolver class


// -------------------------------------- CLASS OVERVIEW -------------------------------------- 
//
// --------------------------------------------------------
// ----------------- PRIVATE DATA MEMBERS -----------------
//
//
//	int height;
//		- stores height of maze
//
//	int width;
//		- stores width of maze
//
//	string mazeTitle;
//		- stores title of maze
//
//	int startR;
//		- stores row of maze start
//
//	int startC;
//		- stores column of maze start
//
//	int endR;
//		- stores row of maze end
//
//	int endC;
//		- stores column of maze end
//
//	int steps;
//		- stores number of steps taken to complete maze
//
//	struct mazeCell
//	{
//		char value;
//		int r, c;
//		int g;
//		bool visited;
//		int prevR, prevC;
//	};
//		- mazeCell struct for each position in **maze. Value holds value of cell, r holds 
//		  row, c holds column, g holds steps taken to get to that cell, visited is true
//		  if cell has been visited in current path and false otherwise, prevR holds row
//		  of previous cell in current path, and prevC holds column of previous cell in
//		  current path.
//
//	mazeCell **maze;
//		- points to maze, which is a 2-d array of mazeCells.
//
//	static constexpr int MIN_SIZE = 5;
//		- used to error check height and width of maze.
//
//	static constexpr int MAX_SIZE = 1000;
//		- used to error check height and width of maze.
//
// --------------------------------------------------------
// ----------------- PUBLIC FUNCTIONS -----------------
//
//
//	bool readMaze(const string mName);
//		- reads maze title, dimensions, and actual maze from file mName, and stores 
//		  maze in **maze.
//
//	string getTitle() const;
//		- returns maze title
//
//	void printMaze() const;
//		- prints current maze using unicode characters.
//
//	bool findPath(mazeStrategyOptions);
//		- finds path by either calling findPathDFS() or findPathASTAR(), depending
//		  on mazeStrategyOptions.
//
//	int getSteps() const;
//		- returns number of steps in current path.
//
// --------------------------------------------------------
// ----------------- PRIVATE FUNCTIONS -----------------
//
//
//	bool findPathDFS();
//		- Finds path using depth first search algorithm. Calls recursive dfs() 
//		  helper function at start cell. Returns true if path is found and false
//		  otherwise.
//
//	bool dfs(mazeCell* );
//		- [Recursive] Used to conduct depth first search. Searches for all valid
//		  paths in the order of up, down, left, right. dfs() is called again for
//		  each consequent valid cell until end is found. Returns true if end is 
//		  found and false otherwise.
//
//	bool findPathASTAR();
//		- Uses A Star algorithm to find path through maze. Uses priorityQueue class
//		  to search highest priority path in maze at any given position, so a 
//		  near-optimal path is chosen every time. Returns true if path is found
//		  and false otherwise.
//


#include <string>

using namespace std;

enum  mazeStrategyOptions {DFS, ASTAR, NONE};

class mazeSolver
{

	public:

	// CONSTRUCTOR AND DESTRUCTOR

	mazeSolver();
	~mazeSolver();

	// PUBLIC FUNCTIONS

	bool readMaze(const string mName);
	string getTitle() const;
	void printMaze() const;
	bool findPath(mazeStrategyOptions);
	int getSteps() const;

	private:
	
	// PRIVATE VARIABLES

	int height;
	int width;
	string mazeTitle;
	int startR;
	int startC;
	int endR;
	int endC;
	int steps;
	struct mazeCell
	{
		char value;
		int r, c;
		int g;
		bool visited;
		int prevR, prevC;
	};
	mazeCell **maze;
	static constexpr int MIN_SIZE = 5;
	static constexpr int MAX_SIZE = 1000;

	// PRIVATE FUNCTIONS

	bool findPathDFS();
	bool dfs(mazeCell* );
	bool findPathASTAR();	

};

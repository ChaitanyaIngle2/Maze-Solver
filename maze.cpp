//  CS 302
//  Provided Main Program

//  Maze solving algorithms assignment.

// ***********************************************************************
//  Includes and prototypes.
  
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

#include "mazeSolver.h"

// *******************************************************************

int main(int argc, char *argv[])
{
// ------------------------------
//  Declarations and headers.

	string	stars;
	string	fName;
	stars.append(60,'*');
	stringstream ss;
	mazeStrategyOptions	userChoice=NONE;

	const char* bold   = "\033[1m";
	const char* unbold   = "\033[0m";
	const char* red   = "\033[31m";
	const char* green   = "\033[32m";

// ------------------------------
//  Verify command line arguments.

	if (argc == 1) {
		cout << "Usage: ./maze <-dfs|-astar> -f <fileName>" << endl;
		return	0;
	}

	if (argc != 4) {
		cout << "Error, invalid command line arguments." << endl;
		return 0;
	}

	if (string(argv[1]) == "-dfs")
		userChoice = DFS;

	if (string(argv[1]) == "-astar")
		userChoice = ASTAR;

	if (userChoice == NONE) {
		cout << "Error, invalid maze strategy." << endl;
		return	0;
	}

	if (string(argv[2]) != "-f") {
		cout << "Error, invalid file name specifier." << endl;
		return 0;
	}

	if (string(argv[3]) == "") {
		cout << "Error, file does not exist." << endl;
		return 0;
	}

	fName = string(argv[3]);

// ------------------------------
//  Command line args ok, display initial headers.

	cout << stars << endl;
	cout << "CS 302 - Assignment #8" << endl;
	cout << bold << green << "Maze Solver Algorithms." << unbold << endl;
	cout << endl << endl;

// ------------------------------
//  Generate random values.

	mazeSolver	myMaze;

// ------------------------------

	if (myMaze.readMaze(string(argv[3]))) {
		cout << bold << "Title: " << myMaze.getTitle() << unbold << endl;
		myMaze.printMaze();

		if (myMaze.findPath(userChoice)) {
			cout << endl << "Solved Maze ";
			if (userChoice == DFS)
				cout << "- Recursive DFS ";
			if (userChoice == ASTAR)
				cout << "- A* ";
			cout << "Strategy." << endl;
			cout << "Solution Steps: " << myMaze.getSteps() << endl;
			myMaze.printMaze();
		} else {
			cout << endl << bold << red << "There is ";
			cout << "no path through this maze.";
			cout << unbold << endl;
		}
	} else {
		cout << "Error reading maze file." << endl;
	}

// ------------------------------
//  Done, terminate program.

	cout << endl;
	cout << "Game over, thanks for playing." << endl;

	return 0;
}


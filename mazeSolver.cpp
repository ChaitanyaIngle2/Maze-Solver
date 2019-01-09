// Chaitanya Ingle
// Sec. 1002
// Ast. 08

// FILE: mazeSolver.cpp
// DESCRIPTION: Implementation file for mazeSolver class.

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "mazeSolver.h"
#include "priorityQueue.h"

using namespace std;

// **************************************************************
// **************************************************************
// DATA DECLARATIONS

static const string LTC = "\u2554";    // l, left top corner 
static const string RTC = "\u2557";    // r, right top corner 
static const string LBC = "\u255A";    // k, left bottom corner
static const string RBC = "\u255D";    // z, right bottom corner
static const string HLN = "\u2550";    // ­, horizontal line 
static const string VLN = "\u2551";    // i, vertical line 
static const string CTR = "\u256C";    // x, center 4­way 
static const string VLT = "\u2563";    // f, vertical left 
static const string VRT = "\u2560";    // 7, vertical right 
static const string HUP = "\u2569";    // ^, horizontal up 
static const string HDW = "\u2566";    // t, horizontal down 
static const string BLT = "\u2022";    // bullet 

static const string SPC = " ";         // space
static const string STR = "S";         // start 
static const string END = "E";         // end 

const char* bold   = "\033[1m";        // start bolding
const char* red    = "\033[31m";       // start red
const char* green  = "\033[32m";       // start green
const char* unbold = "\033[0m";        // end bolding/reset

// **************************************************************
// **************************************************************
// FUNCTIONS
//
// DESCRIPTIONS IN HEADER FILE


// ********************************************

mazeSolver::mazeSolver()
{

	height = 0;
	width = 0;
	mazeTitle = "";
	startR = 0;
	startC = 0;
	endR = 0;
	endC = 0;
	steps = 0;
	maze = NULL;

}

// ********************************************

mazeSolver::~mazeSolver()
{

	for (int i = 0; i < height; i++)
		delete [] maze[i];
	delete [] maze;
	maze = NULL;

}

// ********************************************

bool mazeSolver::readMaze(const string mName)
{

	ifstream infile;                     // Make sure file exists
	infile.open(mName.c_str());
	if (!infile)
		return false;

	getline(infile, mazeTitle);   // Read file header and ensure valid arguments
	infile >> height >> width;
	if (height < MIN_SIZE || height > MAX_SIZE || width < MIN_SIZE || width > MAX_SIZE)
		return false;	
	
	maze = new mazeCell*[height];        // Allocate 2-d array
	for (int i = 0; i < height; i++)
		maze[i] = new mazeCell[width];


	char mazeChar;
	infile.get(mazeChar);             // get linefeed character
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			infile.get(mazeChar);
			if (mazeChar == 'S') {
				startR = i;
				startC = j;
			}
			if (mazeChar == 'E') {
				endR = i;
				endC = j;
			}
			
			maze[i][j].value = mazeChar;
			maze[i][j].r = i;
			maze[i][j].c = j;
		}
		infile.get(mazeChar);             // get linefeed character
	}	
	return true;
}

// ********************************************

string mazeSolver::getTitle() const
{

	return mazeTitle;

}

// ********************************************

int mazeSolver::getSteps() const
{

	return steps;

}

// ********************************************

void mazeSolver::printMaze() const
{

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) 
			switch (maze[i][j].value) {
			
				case '.':
					cout<< bold<< red<< BLT<< unbold;
					break;
				case 'l':
					cout<< LTC;	
					break;
				case 'r':
					cout<< RTC;
					break;
				case 'k':
					cout<< LBC;
					break;
				case 'z':
					cout<< RBC;
					break;
				case '-':
					cout<< HLN;
					break;
				case 'i':
					cout<< VLN;
					break;
				case 'x':
					cout<< CTR;
					break;
				case '7':
					cout<< VLT;
					break;
				case 'f':
					cout<< VRT;
					break;
				case '^':
					cout<< HUP;
					break;
				case 't':
					cout<< HDW;
					break;
				case ' ':
					cout<< SPC;
					break;
				case 'S':
					cout<< bold<< green<< STR<< unbold;
					break;
				case 'E':
					cout<< bold<< green<< END<< unbold;
					break;
			}
			
			cout<< endl;
	}
}

// ********************************************

bool mazeSolver::findPath(mazeStrategyOptions strat)
{

	switch (strat) {	
		case DFS:
			return findPathDFS();
		case ASTAR:
			return findPathASTAR();
		case NONE:
			return false;
	}
	return false;
}

bool mazeSolver::findPathDFS()
{
	mazeCell* mStart = new mazeCell;
	*mStart = maze[startR][startC];
	return dfs(mStart);

}

// ********************************************

bool mazeSolver::dfs(mazeCell * cell)
{
	
	if (cell->value == 'E')
		return true;

	if (cell->value == '.' || (cell-> value != ' ' && cell-> value != 'S'))
		return false;

	steps++;

	if (cell-> value != 'S') 
		maze[cell-> r][cell-> c].value = '.';

	mazeCell* nextCell = new mazeCell;

	if (cell-> r - 1 >= 0) {
		*nextCell = maze[cell->r-1][cell->c];
		if (dfs(nextCell))
			return true;
	}
	if (cell-> r + 1 < height) {
		*nextCell = maze[cell->r+1][cell->c];
		if (dfs(nextCell))
			return true;
	}
	if (cell-> c - 1 >= 0) {
		*nextCell = maze[cell->r][cell->c-1];
		if (dfs(nextCell))
			return true;
	}
	if (cell-> c + 1 < width) {
		*nextCell = maze[cell->r][cell->c+1];
		if (dfs(nextCell))
			return true;
	}

	steps--;
	if (cell-> value != 'S') 
		maze[cell-> r][cell-> c].value = ' ';
	return false;
}

// ********************************************

bool mazeSolver::findPathASTAR()
{
	
	priorityQueue<mazeCell> mazeLocs;
	
	maze[startR][startC].g = 0;
	mazeCell currCell;
	currCell = maze[startR][startC];
	mazeLocs.insert(currCell, 1);

	mazeCell nextCell;
	int priorDump;   // variable to store priority when cell is grabbed 
	int heuter;

	while (!mazeLocs.isEmpty()) {
		if (mazeLocs.deleteMin(currCell, priorDump)) {
			maze[currCell.r][currCell.c].visited = true;
			if (currCell.value == 'E') {
				steps = currCell.g;
				while (currCell.c > 0) {
					currCell = maze[currCell.prevR][currCell.prevC]; 
					if(maze[currCell.r][currCell.c].value != 'S')
						maze[currCell.r][currCell.c].value = '.';
		
				}
				return true;
			}

			if (currCell.r - 1 >= 0) {
				nextCell = maze[currCell.r-1][currCell.c];
				if ((nextCell.value == ' ' || nextCell.value == 'E') && (nextCell.visited != true)) {
					maze[nextCell.r][nextCell.c].prevR = currCell.r;
					maze[nextCell.r][nextCell.c].prevC = currCell.c;
					maze[nextCell.r][nextCell.c].g = currCell.g + 1;
					nextCell = maze[currCell.r-1][currCell.c];	
					heuter = abs(currCell.r - endR) + abs(currCell.c - endC) + currCell.g;			
					mazeLocs.insert(nextCell, heuter);
				}
			}
			if (currCell.r + 1 < height) {
				nextCell = maze[currCell.r+1][currCell.c];
				if ((nextCell.value == ' ' || nextCell.value == 'E') && (nextCell.visited != true)) {
					maze[nextCell.r][nextCell.c].prevR = currCell.r;
					maze[nextCell.r][nextCell.c].prevC = currCell.c;
					maze[nextCell.r][nextCell.c].g = currCell.g + 1;
					nextCell = maze[currCell.r+1][currCell.c];	
					heuter = abs(currCell.r - endR) + abs(currCell.c - endC) + currCell.g;			
					mazeLocs.insert(nextCell, heuter);
				}
			}
			if (currCell.c - 1 >= 0) {
				nextCell = maze[currCell.r][currCell.c-1];
				if ((nextCell.value == ' ' || nextCell.value == 'E') && (nextCell.visited != true)) {
					maze[nextCell.r][nextCell.c].prevR = currCell.r;
					maze[nextCell.r][nextCell.c].prevC = currCell.c;
					maze[nextCell.r][nextCell.c].g = currCell.g + 1;
					nextCell = maze[currCell.r][currCell.c-1];
					heuter = abs(currCell.r - endR) + abs(currCell.c - endC) + currCell.g;			
					mazeLocs.insert(nextCell, heuter);
				}
			}
			if (currCell.c + 1 < width) {
				nextCell = maze[currCell.r][currCell.c+1];
				if ((nextCell.value == ' ' || nextCell.value == 'E') && (nextCell.visited != true)) {
					maze[nextCell.r][nextCell.c].prevR = currCell.r;
					maze[nextCell.r][nextCell.c].prevC = currCell.c;
					maze[nextCell.r][nextCell.c].g = currCell.g + 1;
					nextCell = maze[currCell.r][currCell.c+1];	
					heuter = abs(currCell.r - endR) + abs(currCell.c - endC) + currCell.g;		
					mazeLocs.insert(nextCell, heuter);
				}
			}
		}
	}
	return false;
					

}














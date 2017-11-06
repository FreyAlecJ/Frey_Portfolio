/*
Author: Alec Frey
Installation: MTSU
Profesor: Dr. Phillips
Class: CSCI4350
Purpse: This lab implements A* to solve the 8-puzzle problem with various heuristics
*/

#include <string>
#include <array>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unordered_map>
#include <cmath>
#include <set>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Node
{
	int parent;
	int depth;
	int nodeID;
	int pathCost;
	int estimatedCost;
	int zeroLocation;
	string boardState;

	bool operator<(const Node& rhs) const
	{
		if (estimatedCost < rhs.estimatedCost)
			return true;
		else if (estimatedCost > rhs.estimatedCost)
			return false;
		if (nodeID > rhs.nodeID)
			return true;
		else
			return false;
	}
};

struct compareNode
{
	bool operator()(const Node& first, const Node& second) const
	{
		return (first < second);
	}
};


//Function Prototypes
Node 						BuildInitial();
void 						DisplayState(string& state);
string						BuildGoalState();
int 						FindManhattan(string& currState, string& goal,
										unordered_map<int,int>& xValue, unordered_map<int,int>& yValue);
int 						CountMisplaced(string& currState, string& goalState);
void						Swap(string& curr, int& x, int& y);
int						MisplacedNeighbors(string& currState, string& goal, vector<int>& neighbors,
							unordered_map<int, int>& xValue, unordered_map<int, int>& yValue);
void 						GenerateChildren(Node& curr, string& goal, unordered_map<int, vector<int>>&  possibleMoves, int& id, set<string>& closed, int& nodesVisited,
							int& function, set<Node, compareNode>& frontier, unordered_map<int, int>& xValue, unordered_map<int, int>& yValue);
unordered_map<int,int>				BuildxValue();
unordered_map<int,int> 				BuildyValue();
unordered_map<int, vector<int>> 		BuildPossibleMoves();
void						DisplayFinalPath(Node currNode, unordered_map<int, Node> nodes);



int main(int argc, char *argv[])
{
	//variables to hold the statistics
	int nodesVisited = 0;

	//initialze x lookup table for manhattan distance
	unordered_map<int, int> xValue = BuildxValue();

	//initialize y lookup table for manhattan distance
	unordered_map<int, int> yValue = BuildyValue();

	//initialize the children lookup table
	unordered_map<int, vector<int>> possibleMoves = BuildPossibleMoves();

	//initialize the frontier
	set<Node, compareNode> frontier;

	//initialize the closed list
	set<string> closed;

	//create the goal state references
	string goal = BuildGoalState();


	//perform the AStar search. Done in main to reduce excessive passing of hash tables
	Node currNode = BuildInitial(); // builds the initial state
	int id = currNode.nodeID;

	//initialize the list of all nodes for tracing back the path
	unordered_map<int, Node> nodes;
	int function = atoi(argv[1]);
	
	while (true)
	{
		//Step 1: Check Goal
		if (currNode.boardState == goal) // GOLLLLIIIIIIEEELGOAALLLLLIEEEEGOAL!
		{	
			break;
		}

		//Step 2: Expand Children (Closed list comparison handled in expansion) and add to frontier
		GenerateChildren(currNode, goal, possibleMoves, id, closed, nodesVisited, function, frontier, xValue, yValue);
		
		//Step 3: Add Node to closed list
		closed.emplace(currNode.boardState);

		//Step 4: Add node to the cumulative list Key: ID Value: Node
		nodes.emplace(currNode.nodeID, currNode);


		//Step 5: Set the currNode to the top of the frontier
		currNode = *(frontier.begin());
		frontier.erase(frontier.begin());

	}


	cout << "V = " << nodesVisited << endl;
	cout << "N = " << frontier.size() + closed.size() << endl;
	cout << "D = " << currNode.depth << endl;
	cout << "B = " << pow(nodesVisited, (1.0 / currNode.depth)) << endl << endl;
	DisplayFinalPath(currNode, nodes);

	
	
	return 0;


}







/*
	Function: DisplayFinalPath()
	Purpose: Displays the path to the goal
*/
void DisplayFinalPath(Node currNode, unordered_map<int, Node> nodes)
{
	stack<Node> path;

	while (currNode.nodeID != 0)
	{
		//push the current node onto the stack
		path.push(currNode);

		//find the parent node using the hash table
		currNode = nodes.find(currNode.parent)->second;
	}

	path.push(currNode);

	while (!path.empty())
	{
		DisplayState(path.top().boardState);
		path.pop();
	}

}


/*
	Function: 	BuildIntial
	Purpose: 	Creates the intitial node based on the input of the random_board file
*/
Node BuildInitial()
{
	//recieve the initial input from random board
	string a, b, c, d, e, f, g, h, i;
	cin >> a >> b >> c >> d >> e >>f >> g >> h >> i;


	//insert the information into the root node;
	Node initialState;
	string state;

	state = a + b + c + d + e + f + g + h + i;
	

	//initialize other data members
	initialState.zeroLocation = state.find('0'); // delete for actual build
	initialState.parent = 0;
	initialState.depth = 0;
	initialState.nodeID = 0;
	initialState.pathCost = 0;
	initialState.boardState = state;

	return initialState;
}






/*
	Function: 	BuildGoalState
	Purpose: 	Creates the pre defined goal state. SHOULD BE IMPLMENTED FROM FILE BUT FOR THE SAKE
				OF SIMPLICITY IT IS NOT AT THIS TIME
*/
string BuildGoalState()
{
	string goal = "012345678";

	return goal;
}




/*
	Function: 	DisplayState
	Purpose: 	Displays the passed board state
*/
void DisplayState(string& state)
{
	cout << state[0] << " " << state[1] << " " << state[2] << endl;
	cout << state[3] << " " << state[4] << " " << state[5] << endl;
	cout << state[6] << " " << state[7] << " " << state[8] << endl << endl;

	return;
}


/*
	Function	MisplacedNeighbor
	Purpose: This is a hueristic value that involves counting how many of zero's neighbors are out of place
*/
int MisplacedNeighbors(string& currState, string& goal, vector<int>& neighbors,
		unordered_map<int, int>& xValue, unordered_map<int, int>& yValue)
{
	int total = 0;

	for (int i = 0; i < neighbors.size(); i++)
	{
		int neighbor = neighbors[i];
		if (currState[neighbor] != goal[neighbor])
		{
			total += 1;
		}
	}

	return total;
}




/*
	Function: 	FindManhattan
	Purpose: 	Finds the manhattan distance of the passed tile
*/
int FindManhattan(string& currState, string& goal,
		unordered_map<int,int>& xValue, unordered_map<int,int>& yValue)
{	
	//holds the coordinates for the tile and its goal state
	int curTile;
	int curX; // these coordinates map the current and desired locations in the array
	int curY;
	int goalTile;
	int goalX;
	int goalY;
	int distance = 0; 	// holds the manhattan distance for the tile to the goal
	int totalDistance = 0;  //holds the total manhattan distance for all 8 tiles

	//skips zero for the calcualtion
	for (int i = 0; i < 9; i++)
	{

		//find the digit at goal location i
		char digit = goal[i];

		if (digit == '0')
			continue;

		//find where the char is in current state
		curTile = currState.find(digit);

		
		//find the current x and y values of location i
		curX = xValue.find(curTile)->second;
		curY = yValue.find(curTile)->second;

		//finds the x and y location of the desired state
		goalX = xValue.find(i)->second;
		goalY = yValue.find(i)->second;

		//calculates the distance away
		distance = abs(goalX - curX); //calc x distance
		distance += abs(goalY - curY); //calc y distance
	

		totalDistance += distance;
		
	}
	return totalDistance;
}








/*
	Function: 	CountMisplaced
	Purpose: 	Returns the amount of misplaced tiles
*/
int CountMisplaced(string& currState, string& goalState)
{
	int total = 0;

	for(int i = 1; i < 9; i++)
	{
		if (currState[i] != goalState[i])
		{
			total += 1;
		}
	}

	return total;
}



/*

	Fuction Swap
	Purpose: Swaps the two tiles
*/
void Swap(string& curr, int& x, int& y)
{
	int temp = curr[x];
	curr[x] = curr[y];
	curr[y] = temp;

	return;

}



/*
	Function: 	GenerateChildren
	Purpose: 	Generates the four children of the node 
*/
void GenerateChildren(Node& curr, string& goal, unordered_map<int, vector<int>>&  possibleMoves, int& id, set<string>& closed, int& nodesVisited,
		int& function, set<Node, compareNode>& frontier, unordered_map<int, int>& xValue, unordered_map<int, int>& yValue)
{

	vector<int> possible = possibleMoves.find(curr.zeroLocation)->second;
	//iterate through the set<int> and create children for each iteration
	for(int i = 0; i != possible.size(); i++)
	{
		

		//create the new child node
		Node newNode;
		string copy = curr.boardState;

		//find the two numbers to switch based off the flippedState
		int move = possible[i];
		Swap(copy, curr.zeroLocation, move);
		
		//assign the node its member data
		id += 1; //increment id then push into the node
		newNode.nodeID = id;
		newNode.parent = curr.nodeID;
		newNode.depth = curr.depth + 1;
		newNode.zeroLocation = move;
		newNode.boardState = copy;
		newNode.pathCost = curr.pathCost + 1;

		//check if the child is in the closed list. This is done after the member data is calculated so the node count is updated
		set<string>::iterator setIt = closed.find(copy);
		if (setIt != closed.end()) //object found -> do skip adding this to the vector
		{
			continue;
		}

		//increment V
		nodesVisited++;

		//calculate the hueristic cost
		int hueristic;
		switch (function)
		{
		case 0:
		{
			hueristic = 0;
			break;
		}
		case 1:
		{
			hueristic = CountMisplaced(newNode.boardState, goal);
			break;
		}
		case 2:
		{
			hueristic = FindManhattan(newNode.boardState, goal, xValue, yValue);
			break;
		}
		case 3:
		{
			vector<int> neighbors = possibleMoves.find(newNode.zeroLocation)->second;
			hueristic = MisplacedNeighbors(newNode.boardState, goal, neighbors, xValue, yValue);
			break;
		}
		}


		//add hueristic to the path cost and store into node.estimatedcost
		newNode.estimatedCost = newNode.pathCost + hueristic;

		//push the node into the frontier
		frontier.insert(newNode);


	}

	return;
}


/*
	Function: 	BuildxValue()
	Purpose: 	Generates the xValue lookup table for manhattan heuristic
*/
unordered_map<int,int> BuildxValue()
{
	unordered_map<int,int> xValue;
	xValue.emplace(0, 0);
	xValue.emplace(1, 0);
	xValue.emplace(2, 0);
	xValue.emplace(3, 1);
	xValue.emplace(4, 1);
	xValue.emplace(5, 1);
	xValue.emplace(6, 2);
	xValue.emplace(7, 2);
	xValue.emplace(8, 2);

	return xValue;
}







/*
	Function: 	BuildyValue()
	Purpose: 	Generates the yValue lookup table for manhattan heuristic
*/
unordered_map<int,int> BuildyValue()
{
	unordered_map<int,int> yValue;
	yValue.emplace(0, 0);
	yValue.emplace(3, 0);
	yValue.emplace(6, 0);
	yValue.emplace(1, 1);
	yValue.emplace(4, 1);
	yValue.emplace(7, 1);
	yValue.emplace(2, 2);
	yValue.emplace(5, 2);
	yValue.emplace(8, 2);

	return yValue;
}



/*
	Function: BuildPossibleMoves()
	Purpose: Builds the lookup table for possible moves when generating children nodes
*/
unordered_map<int, vector<int>> BuildPossibleMoves()
{

	//initialize the children lookup table
	unordered_map<int, vector<int>> possibleMoves;

	int zeroMoves[] {1,3};
	vector<int> zero (zeroMoves, zeroMoves+2);
	possibleMoves.emplace(0, zero);
	
	int oneMoves[] {0,2,4};
	vector<int> one (oneMoves, oneMoves+3);
	possibleMoves.emplace(1, one);
	
	int twoMoves[] {1,5};
	vector<int> two (twoMoves, twoMoves+2);
	possibleMoves.emplace(2, two);
	
	int threeMoves[] {0,4,6};
	vector<int> three (threeMoves, threeMoves+3);
	possibleMoves.emplace(3, three);
	
	int fourMoves[] {1,3,5,7};
	vector<int> four (fourMoves, fourMoves+4);
	possibleMoves.emplace(4, four);
	
	int fiveMoves[] {2,4,8};
	vector<int> five (fiveMoves, fiveMoves+3);
	possibleMoves.emplace(5, five);
	
	int sixMoves[] {3,7};
	vector<int> six (sixMoves, sixMoves+2);
	possibleMoves.emplace(6, six);
	
	int sevenMoves[] {4,6,8};
	vector<int> seven (sevenMoves, sevenMoves+3);
	possibleMoves.emplace(7, seven);

	int eightMoves[] {5,7};
	vector<int> eight (eightMoves, eightMoves+2);
	possibleMoves.emplace(8, eight);

	return possibleMoves;

}




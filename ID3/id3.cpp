/*
	Author: Alec Frey
	Professor: Dr. Phillips
	Assignment: OLA 3
	Class: 	CSCI 4350
	Purpose: Implment an id3 tree to learn to classify data
*/
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <set>
#include <iomanip>

using namespace std;

struct 	node;
double 			CalculateI(double probability);
double 			CalculateH(double probability);
double 			CalculateIClasses(vector<vector<double>> record, set<double> classes);
void			QuickSort(vector<vector<double>>& records, int col, int first, int last);
int 			partition(vector<vector<double>>& records, int col, int first, int last);
void 			Swap(vector<vector<double>>& records, int i, int j);
double 			CalculatePAgivenB(vector<vector<double>> record, double label, int col, 				double split, int gt);
void 			DisplayData(vector<vector<double>> data);
double	 		CalculateE(vector<vector<double>>& record, int col, double split, 					set<double> classes);
double			CalculateGain(vector<vector<double>>& record, int col, double split, 					set<double> classes);
double			CalculatePclass(vector<vector<double>> record, int label);
set<double>		CalculateClass(vector<vector<double>> record, int attributes);
node* 			Split(vector<vector<double>>& record, int attributes, 
				set<double> classes);
double 			CalculatePx(vector<vector<double>>& record, int col, double value);
vector<vector<double>> 	ReadData(string filename, int attributes);
vector<vector<double>>	CutRecord(vector<vector<double>> record, int direction, int col, 
				double	val);
node*			Train(vector<vector<double>>& records, int attributes);
int			FindMostClasses(vector<vector<double>> records, int attributes);
int			Classify(vector<double> record, node* root);
bool			CheckSplits(vector<vector<double>> record, int attributes);
void 			DFS(node* root);

struct node
{
	int 	splitCol; 
	double 	splitVal;
	int	label;
	node* 	left;
	node* 	right;
	node(int col, double val, int lab, node* l, node* r)
		: splitCol(col), splitVal(val), label(lab), left(l), right(r)
	{}
};

int main(int argc, char *argv[])
{
	//grab command line args
	int attributes = atoi(argv[1]);
	string training = argv[2];
	string testing = argv[3];

	//declarations
	vector<vector<double>> trainingData = ReadData(training, attributes);
	vector<vector<double>> testData = ReadData(testing, attributes);

	//Train the data
	node* root = Train(trainingData, attributes);

	double totalCorrect = 0;
	double totalWrong = 0;
	
	for (int j = 0; j < testData.size(); j++)
	{
		//loop through the testing data and classify
		vector<double> line = testData[j];

		int label = Classify(line, root);
		if (label == line[attributes])
		{
			totalCorrect++;	
		}
		else
		{
			totalWrong++;		
		}
			
	}

	cout << totalCorrect << endl;
	

	return 0;
}




/*
	Function: Train
	Purpose: Recursively build a tree for use in training data
*/
node* Train(vector<vector<double>>& records, int attributes)
{
	//calculate classes in data
	set<double> classes = CalculateClass(records, attributes);

	//Base Cases -> 1: No split occurred
	//Base cases -> 2: Only one classification remains
	if (!CheckSplits(records,attributes) || classes.size() == 1)
	{
		int label = FindMostClasses(records,attributes);

		node* finalNode = new node(-1, -1, label, NULL, NULL);
		return finalNode;	
	}

	//find the next best splitpoint
	node* split = Split(records, attributes, classes);

	//build left tree -> x < split
	vector<vector<double>> leftRecord;
	leftRecord =  CutRecord(records, 0, split->splitCol, split->splitVal);

	//build right tree -> x > split
	vector<vector<double>> rightRecord;
	rightRecord = CutRecord(records, 1, split->splitCol, split->splitVal);

	//make recursive calls on new trees
	split->left =  Train(leftRecord, attributes);
	split->right = Train(rightRecord, attributes);
	return split;

}

bool	CheckSplits(vector<vector<double>> record, int attributes)
{
	//holdsp previous value for comparison
	double previousValue;
	for(int i = 0; i < attributes; i++)
	{
		//sort by column for use in spliting
		QuickSort(record, i, 0, record.size());

		//first entry in the sorted column
		previousValue = record[0][i];

		//loop through the records. Split and calculate gain
		for (int j = 0; j < record.size(); j++)
		{
			//grab line
			vector<double> line = record[j];

			//get value from sorted column
			double value = line[i];

			if (value > previousValue)
			{
				return true;
			}
			previousValue = value;
		}
	}

	return false;
}

/*
	Function: Classify
	Purpose: Classifies the vector passed to the function
*/

int Classify(vector<double> record, node* root)
{
	//initialize search node
	node* curNode = root;

	while (curNode->label == -1)
	{
		int nodeCol = curNode->splitCol;
		int nodeVal = curNode->splitVal;
		if (record[nodeCol] < nodeVal)
		{
			curNode = curNode->left;
		}
		else
			curNode = curNode->right;

	}

	return curNode->label;
}



/*
	Function: FindMostClasses
	Purpose: Searches through the record and find the class with the most occurence
	for use in classification
*/
int FindMostClasses(vector<vector<double>> records, int attributes)
{
	//sort by classes
	QuickSort(records, attributes, 0, records.size());

	//holders for curCount, Maxcount and label
	int maxCount = 0;
	int curCount = 0;

	//set both labels to the first occurence
	int curLabel = records[0][attributes];
	int label = records[0][attributes];
	curCount++;

	for(int i = 1; i < records.size(); i++)
	{
		if (records[i][attributes] == curLabel)
		{
			curCount++;
		}
		else
		{	//track old label data
			if (curCount > maxCount)
			{
				maxCount = curCount;
				label = curLabel;
			}
			else if (curCount == maxCount)
			{
				if (curLabel < label) //break tie with smallest
				{
					maxCount = curCount;
					label = curLabel;
				}
			}

			//update the new label 
			curLabel = records[i][attributes];
			curCount = 1;	
		}
	}

	return label;
}

/*
	Function: CalculateClass
	Pupose: Counts how many classes are present in the data
*/
set<double> CalculateClass(vector<vector<double>> record, int attributes)
{
	set<double> classes;
	for(int i = 0; i < record.size(); i++)
	{
		vector<double> line = record[i];
		set<double>::iterator it;

		it = classes.find(line[attributes]);
		if (it == classes.end())
		{
			classes.insert(line[attributes]);
		}
	}

	return classes;
}



/* 
	Function: Read Data
	Purpose: Read data from a file and store in a vector of vector double
*/
vector<vector<double>> ReadData(string filename, int attributes)
{
	//open the test data
	ifstream trainFile;
	trainFile.open(filename);

	vector<vector<double>> trainingData;

	//read data into trainingData vector
	string line;
	int numberOfEntries = 0;
	while (getline(trainFile, line))
	{
		//create vector for pushing into data
		vector<double> newData;

		//hold the index uses in parsing
		int start= 0;
		int stop = 0;

		//parse string
		for(int i = 0; i < attributes+1; i++)
		{
			stop = line.find(" ");
			if (stop != string::npos)
			{
				int length = stop - start;
				string number = line.substr(start, length);
				newData.push_back(atof(number.c_str()));
				line = line.substr(stop+1);
			}
			else //final value in the string
			{
				string number = line;
				newData.push_back(atof(number.c_str()));
			}
		}

		newData.resize(attributes+1);

		//push vector into trainingData
		trainingData.push_back(newData);
		numberOfEntries++;
	}
	
	trainingData.resize(numberOfEntries);
		
	//close the file
	trainFile.close();

	return trainingData;
}





/*
	Function: Display Data
	Purpose: DIsplay the data in the vector of vectors
*/
void DisplayData(vector<vector<double>> data)
{
	
	for(int i = 0; i < data.size(); i++)
	{
		vector<double> line = data[i];

		for (int j = 0; j < line.size()-1; j++)
		{
			cout << setprecision(1) << fixed <<  line[j] << " ";
		}
		cout << setprecision(0) << fixed << line[line.size()-1] << " ";
		cout << endl;
	}
	cout << endl;

	return;
}


/* 
	Function QuickSort
	Purpose: Quick sort records by attriute

*/
void QuickSort(vector<vector<double>>& records, int col, int first, int last)
{
	int middle;
	if (first < last)
	{
		middle = partition(records, col, first, last);
		QuickSort(records, col, first, middle);
		QuickSort(records, col, middle+1, last); 
	}
	return;
}





/*
	Function Partiion
	Purpose: Make a partion and sort the search. 
*/
int partition(vector<vector<double>>& records, int col, int first, int last)
{
	//set the pivot value
	double 	pivot = records[first][col];
	int	middle = first-1;
	
	//move the pivot
	for (int index = first; index < last; index++)
	{	
		//grab new value
		double value = records[index][col];

		//compare and swap
		if (value <= pivot)
		{
			middle++;
			Swap(records, middle, index);
		}
	}
	Swap(records, middle, first);

	return middle;
	 
}

/*
	Function: CalculatePx
	Purpose: Calculate the proabilty of x < passed value
*/
double CalculatePx(vector<vector<double>>& record, int col, double value)
{
	//sort the record by the col
	QuickSort(record, col, 0, record.size());

	//count how many value are less than the passed value
	double count = 0;
	for(int i = 0; i < record.size(); i++)
	{
		vector<double> line = record[i];
		double curVal = line[col];
		if (curVal < value)
			count++;
	}
	return count/record.size();	
}


/*
	Function: Swap
	Purpose: Swap two records and provided indexes
*/
void Swap(vector<vector<double>>& records, int i, int j)
{
	vector<double> temp;
	temp = records[j];
	records[j] = records[i];
	records[i] = temp;

	return;
}




/*
	Function: CalculateI
	Purpose: Recieves the probability and calculates #of bits using the equation
		Bits = -log2(p)
*/
double CalculateI(double probability)
{

	return -log2(probability);
}





/*
	Function: CalculateH
	Purpose: Calcualtes P(x) * I(x)
*/
double CalculateH(double probability)
{
	double bits = CalculateI(probability);
	return bits*probability;
}




/* 
	Function CalculateI2
	Purpose: Calculates I with 2 classes
*/
double CalculateIClasses(vector<vector<double>> record, set<double> classes)
{
	set<double>::iterator it;
	double I = 0;
	for(it = classes.begin(); it != classes.end(); it++)
	{
		double prob = CalculatePclass(record, (*it));
		double H = CalculateH(prob);
		I += H;
	}

	return I;
}


/*
	Function: CalculatePClass()
	Purpose: Claculates the probability of a classification
*/
double CalculatePclass(vector<vector<double>> record, int label)
{
	double count = 0;
	for(int i = 0; i < record.size(); i++)
	{
		vector<double> line = record[i];
		int size = line.size();
		if (line[size-1] == label)
			count++;
	}

	return count/record.size();
}


/*
	Function: Calculate Gain
	Purpose: Calculate the gain of the passed column
*/
double	CalculateGain(vector<vector<double>>& record, int col, double split, 
	set<double> classes)
{
	double eCol = CalculateE(record, col, split, classes);
	double iClasses = CalculateIClasses(record, classes);
	return iClasses-eCol;
}


/*
	Function: CalculatePAgivenB
	Pupose: calculates the probabiliyt of A given B
*/
double CalculatePAgivenB(vector<vector<double>> record, double label, int col, double split, 
		int gt)
{
	QuickSort(record, col, 0, record.size());

	double pOfB;
	double count = 0.0;

	if (gt == 0)
	{
		//find all cases where that label holds
		for(int i = 0; i < record.size(); i++)
		{
			vector<double> line = record[i];
			int attributes = line.size();
			if ((line[attributes-1] == label) && (line[col] < split))
			{
				count++;
			}
		}
		pOfB = CalculatePx(record, col, split);
	}
	else
	{
		//find all cases where that label holds
		for(int i = 0; i < record.size(); i++)
		{
			vector<double> line = record[i];
			int attributes = line.size();
			if ((line[attributes-1] == label) && (line[col] > split))
			{
				count++;
			}	
		}
		pOfB = 1 - CalculatePx(record,col,split);
	}
	
	double pofAandB = count/record.size();
	
	return pofAandB/pOfB;
}



/*
	Function: CalculateE(double a)
	Purpose: Calcualtes the Expectation value of a value
*/
double	CalculateE(vector<vector<double>>& record, int col, double split, set<double> classes)
{
	//claculate x < split
	double xLess = 0;
	set<double>::iterator it;
	for(it = classes.begin(); it != classes.end(); it++)
	{
			double pClassGivenA = CalculatePAgivenB(record, (*it), col, split, 0);
			if (pClassGivenA == 0)
				continue;
			double logPClassGivenA = log2(pClassGivenA);
			xLess += (pClassGivenA)*(logPClassGivenA);	
	}
	xLess *= -CalculatePx(record, col, split);

	//claculate x > split
	double xGreater = 0;
	for(it = classes.begin(); it != classes.end(); it++)
	{
			double pClassGivenA = CalculatePAgivenB(record, (*it), col, split, 1);
			if (pClassGivenA == 0)
				continue;
			double logPClassGivenA = log2(pClassGivenA);
			xGreater += (pClassGivenA)*(logPClassGivenA);	
	}
	xGreater *= -(1 - CalculatePx(record, col, split));

	return xLess + xGreater;
}




/*
	Function: Split
	Purpose: Runs through record list and pulls the record with the maximum gain
*/
node* Split(vector<vector<double>>& record, int attributes, set<double> classes)
{
	//holds the info for the item that gave the max gain
	double maxGain = 0;
	double maxGainVal = 0;
	double maxGainCol = -1;

	//holdsp previous value for comparison
	double previousValue;

	for(int i = 0; i < attributes; i++)
	{
		//sort by column for use in spliting
		QuickSort(record, i, 0, record.size());

		//first entry in the sorted column
		previousValue = record[0][i];

		//loop through the records. Split and calculate gain
		for (int j = 0; j < record.size(); j++)
		{
			//grab line
			vector<double> line = record[j];

			//get value from sorted column
			double value = line[i];

			if (value > previousValue)
			{
				//split the record				
				double split = (value + previousValue)/2;
				
				//caclulate the gain
				double gain = CalculateGain(record, i, split, classes);
				if (gain > maxGain)
				{
					maxGain = gain;
					maxGainVal = split;
					maxGainCol = i;
				}
				else if (gain == maxGain && i < maxGainCol)
				{
					maxGain = gain;
					maxGainVal = split;
					maxGainCol = i;
				}
				else if (gain == maxGain && i == maxGainCol && value < maxGainVal)
				{
					maxGain = gain;
					maxGainVal = split;
					maxGainCol = i;

				}
			}
			previousValue = value;
		}
	}

	node* newPtr = new node(maxGainCol, maxGainVal, -1, NULL, NULL);
	return newPtr;
}




/* 
		Function: CutRecord
		purpose: Cuts the record based on your passed parameter with it
*/
vector<vector<double>> CutRecord(vector<vector<double>> record, int direction, int col, double value)
{
	//sort the record by the desired col
	QuickSort(record, col, 0, record.size());

	//create the new vector to hold the cut data
	vector<vector<double>> newData;

	//check which direction to cut and loop through
	if (direction == 1)
	{
		for(int i = 0; i < record.size(); i++)
		{
			vector<double> line = record[i];
			double newValue = line[col];
			if (newValue > value)
				newData.push_back(line);
		}
	}
	else
	{
		for(int i = 0; i < record.size(); i++)
		{
			vector<double> line = record[i];
			double newValue = line[col];
			if (newValue < value)
				newData.push_back(line);
		}
	}

	return newData;
}



void DFS(node* n)
{
	if (n == NULL)
		return;
	cout << "Label:  " << setprecision(2) << fixed << n->label << " Value: " << 
		n->splitVal << " Col: " << n->splitCol << endl;
	DFS(n->left);
	DFS(n->right);

}













/*
	Author: Alec Frey
	Installation: MTSU
	Class: Intro to AI
	Prof: Dr. Phillips
	Assignment: OLA4
	purpose: To implement the kmeans algorithm.
*/

#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <set>
#include <unordered_map>

using namespace std;

void 			DisplayCenters(vector<vector<double>> data);
void 			DisplayPoints(vector<vector<double>> data, vector<int> states);
vector<vector<double>> 	ReadData(string filename, int attributes);
vector<vector<double>> 	InitClusters(vector<vector<double>> data, int seed, int clusters);
double 			Distance(vector<double> v1, vector<double> v2);
bool			UpdateStates(vector<vector<double>>& data, 
				vector<vector<double>>& centers, vector<int>& states);
void 			SetStates(vector<vector<double>>& data, vector<vector<double>>& centers, 
				vector<int>& states);
void			UpdateCenters(vector<vector<double>>& centers, 
				const vector<vector<double>>& data, const vector<int>& states,
				int clusters);
void			AssignLabels(vector<vector<double>>& centers,
				vector<vector<double>>& data, const vector<int>& states,
				int clusters, int numFeatures);
int			Classify(vector<double> point, const vector<vector<double>>& centers,
				int numFeatures);

int main(int argc, char* argv[])
{
	//grab command line args
	int randomSeed 	= atoi(argv[1]);
	int numClusters = atoi(argv[2]);
	int numFeatures = atoi(argv[3]);
	string training = argv[4];
	string testing 	= argv[5];

	//build the data sets
	vector<vector<double>> trainingData = ReadData(training, numFeatures);
	vector<vector<double>> testData = ReadData(testing, numFeatures);
	vector<vector<double>> centers = InitClusters(trainingData, randomSeed, numClusters);
	vector<int> curStates (trainingData.size(), 0);

	//initalize the points to their closes vector
	SetStates(trainingData, centers, curStates);

	//continuously move centers until no more movement.
	bool keepGoing = true;
	while (keepGoing)
	{
		//set the new centers
		UpdateCenters(centers, trainingData, curStates, numClusters);

		//update the states
		keepGoing = UpdateStates(trainingData, centers, curStates);

		//if keepgoing as false, verify it
		if (!keepGoing)
		{
			UpdateCenters(centers,trainingData, curStates, numClusters);
			keepGoing = UpdateStates(trainingData, centers, curStates);
		}
	}

	//assign labels to the centers based on majority 
	AssignLabels(centers, trainingData, curStates, numClusters, numFeatures);

	double correct = 0;
	int wrong = 0;
	for(int i = 0; i < testData.size(); i++)
	{
		vector<double> point = testData[i];
		int label = Classify(point, centers, numFeatures);
		if (label == point[numFeatures])
			correct++;
		else
			wrong++;	
	}

	double percent = correct/(correct+wrong);
	percent *= 100;

	//cout << "Total: " << correct+wrong << endl;
	//cout << "Correct: " << correct << endl;
	//cout << "Accuracy: " << setprecision(1) << fixed << percent << endl;
	cout << correct << endl;
	
}



/*
	Function: ReadData
	Purpose: Reads the data and feeds it into a vector of vectors
	****** TAKEN FROM MY OWN CODE IN ID3 *****
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
	Function: InitClusters
	Purpose: Randomly initialize the specified number of clusters
*/
vector<vector<double>> 	InitClusters(vector<vector<double>> data, int seed, int clusters)
{
	vector<vector<double>> centers;
	set<int> usedNums;
	for(int i=0; i < clusters; i++)
	{
		int random = rand() % data.size();
		auto ret = usedNums.emplace(random);
		while (!ret.second)
		{
			random = rand() % clusters;
			ret = usedNums.emplace(random);
		}
		
		centers.push_back(data[random]);
	}

	return centers;
}






/*
	Function: DisplayCenters
	Purpose: Ouputs the center data within the vector<vector<double>>
	***** TAKEN FROM MY OWN CODE FROM ID3 *****
*/
void DisplayCenters(vector<vector<double>> data)
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
	Function: DisplayPoints
	Purpose: Displays the data with the current state appended to the end of the line
*/
void DisplayPoints(vector<vector<double>> data, vector<int> states)
{
	
	for(int i = 0; i < data.size(); i++)
	{
		vector<double> line = data[i];

		for (int j = 0; j < line.size()-1; j++)
		{
			cout << setprecision(1) << fixed <<  line[j] << " ";
		}
		cout << setprecision(0) << fixed << line[line.size()-1] << " ";

		cout << "    Current State: " << states[i];
		cout << endl;
	}
	cout << endl;

	return;
}

/*
	Function: Distance
	Pupose: Returns the distance between the two vectors
*/
double Distance(vector<double> v1, vector<double> v2)
{
	//skipping the final square root as it is uncessary when simply comparing who is farther
	//if a square is greater than another its root will also be greater
	double distance = 0;
	for (int i = 0; i < v1.size()-1; i++)
	{
		double att1 = v1[i];
		double att2 = v2[i];
		distance += pow(att2-att1, 2);
	}

	return distance;
}


/*
	Fucntion: ReClassify
	Purpose: loops through and reclassifies the points to their nearest cluster
*/
bool UpdateStates(vector<vector<double>>& data, vector<vector<double>>& centers, 
		vector<int>& states)
{
	bool changesMade = false;

	//loop through each point and reassign it to the a center
	for (int i = 0; i < data.size(); i++)
	{
		//calculate the distance to each vector and select the closest
		//initalize initial points to the first data
		int closest = 0;
		double closestDist = Distance(data[i], centers[0]);
		for(int j = 1; j < centers.size(); j++)
		{
			double newDist = Distance(data[i], centers[j]);
			if (newDist < closestDist)
			{
				closest = j;
				closestDist = newDist;
			}		
		}

		if (closest != states[i])
		{
			states[i] = closest;
			changesMade = true;
		}
	}

	return changesMade;

}

/*
	Function: SetState
	Purpose: Sets the original state bsed on what center is closest
*/
void SetStates(vector<vector<double>>& data, vector<vector<double>>& centers, 
		vector<int>& states)
{
	//loop through each point and reassign it to the a center
	for (int i = 0; i < data.size(); i++)
	{
		//calculate the distance to each vector and select the closest
		//initalize initial points to the first data
		int closest = 0;
		double closestDist = Distance(data[i], centers[0]);
		for(int j = 1; j < centers.size(); j++)
		{
			double newDist = Distance(data[i], centers[j]);
			if (newDist < closestDist)
			{
				closest = j;
				closestDist = newDist;
			}		
		}
		//set the state of the vector to the closest cluster
		states[i] = closest;
	}

	return;
}




/*
	Function: UpdateCenters
	Purpose: Update the centers based on the new points in their range
*/
void	UpdateCenters(vector<vector<double>>& centers, const vector<vector<double>>& data, 
		const vector<int>& states, int clusters)
{

	for(int k = 0; k < clusters; k++)
	{
		vector<vector<double>> separatedPoints;

		//get all of the vectors with proper state
		for(int i = 0; i < data.size(); i++)
		{
			if (states[i] == k)
				separatedPoints.push_back(data[i]);
		}

		//loop through separated data and add them up
		vector<double> newCenter (data[0].size(), 0);
		for(int i = 0; i < separatedPoints.size(); i++)
		{
			vector<double> line = separatedPoints[i];
			for(int j = 0; j < data[0].size()-1; j++)
			{
				newCenter[j] += line[j];
			}
		}

		//loop through and divided by the total amount of vectors
		for (int i = 0; i < data[0].size()-1; i++)
		{
			newCenter[i] /= separatedPoints.size();
		}
		newCenter[newCenter.size()-1] = centers[k][centers.size()-1];
	
		//set centers equal to the newVector
		centers[k] = newCenter;
	}

}

/*
	Function: AssignLabels
	Purpose: Count the majority label for the clusters and assign them
*/
void AssignLabels(vector<vector<double>>& centers, vector<vector<double>>& data, 
		const vector<int>& states, int clusters, int numFeatures)
{
	// looop through all the clusters
	for(int k = 0; k < clusters; k++)
	{
		vector<vector<double>> seperatedPoints;

		//get all of the vectors with proper cluster state
		for(int i = 0; i < data.size(); i++)
		{
			if (states[i] == k)
				seperatedPoints.push_back(data[i]);
		}

		unordered_map<int, int> count;
		vector<int> keys;

		//count how many of each label
		for(int i = 0; i < seperatedPoints.size(); i++)
		{
			vector<double> line = seperatedPoints[i];
			auto it = count.find(line[numFeatures]);
			if ( it == count.end())
			{
				count.emplace(line[numFeatures], 1);
				keys.push_back(line[numFeatures]);
			}
			else
			{
				it->second += 1;
			}
		}

		//find the one with the highest count
		int maxCount = 0;
		int label = -1;
		for (int i = 0; i < keys.size(); i++)
		{
			auto it = count.find(keys[i]);
			int curCount = it->second;
			if (curCount > maxCount)
			{
				maxCount = curCount;
				label = keys[i];
			}			
			else if (curCount == maxCount)
			{
				if (keys[i] < label)
				{
					maxCount = curCount;
					label = keys[i];
				}
			}
		}


		//asign label to cluster
		centers[k][numFeatures] = label;
	}
}


/*
	Function: Classify
	Purpose: Recieve an input vector, determine closest cluster and return its label
*/
int Classify(vector<double> point, const vector<vector<double>>& centers, int numFeatures)
{
	//loop through clustesr and find the closest one
	int closest = 0;
	double closestDist = Distance(point, centers[0]);
	for(int j = 1; j < centers.size(); j++)
	{
		double newDist = Distance(point, centers[j]);
		if (newDist < closestDist)
		{
			closest = j;
			closestDist = newDist;
		}		
	}

	return centers[closest][numFeatures];
	
}

















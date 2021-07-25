#include <iostream>
#include<fstream>
#include <vector>
#include <queue>
#include<time.h>
#define NO_GRAPH 500
#define NO_PROB 10
#define NO_VERTICIES 1000
using namespace std; 

vector<vector<int>> build_random_graph(int v, double p)
{//Generate random Graph
	vector<vector<int>> graph(v);//create vector of vertices and another vector of adjacent for each vector
	for (int i = 0; i < v; i++){
		for (int j = i+1; j < v; j++)
		{//i use i+1=j to dont double check
			if ((double) rand() / RAND_MAX <= p)
			{//set the edges of the graph and push the neighbor to the adjacent vector
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}
	}
	return graph;
}

int is_isolated(vector<vector<int>>& graph) 
{// checking if there is a isolated vertex
	for (int i = 0; i < graph.size(); i++)
		if (graph[i].empty())//checking if the adjacent vector is empty
			return 1;
	return 0;
}

int BFSconnectivity(vector<vector<int>>& graph, int startingVertex) 
{//BFS algorithm retrun if the graph is connected
	vector<bool> visited;// vector of vetecies were true if visited
	int front;
	visited.assign(graph.size(), false);//assign false for all vertecies
	queue<int> q;//queue for current vertex
	q.push(startingVertex);
	visited[startingVertex] = true;
	while (!q.empty()) 
	{// loop at the queue until we passed at the all vertecies in the same component with the starting vertex
		front = q.front();
		q.pop();
		for (auto v = graph[front].begin(); v != graph[front].end(); v++) 
		{//run of the all vertecies and their neighbors
			if (!visited[*v]) 
			{
				q.push(*v);
				visited[*v] = true;
			}
		}
	}
	for (int i = 0; i < visited.size(); i++)//run on the vector of visited check if we visit at every vertecies
		if (visited[i] == false)
			return 0;
	return 1;
	
}

int connectivity(vector<vector<int>>& graph)
{//function check if the graph is connected
	if (graph.size() == 1)//check if the graph is a single vertex
		return 1;
	if(!is_isolated(graph))//if there is not a isolated vertex
		return BFSconnectivity(graph, 0);//call BFS return if the graph connected
	return 0;
}

int BFSdiameter(vector<vector<int>>& graph, int startingVertex) 
{//BFS algorithm return the diameter
	vector<int> distance;//vector of distance from the starting vertex
	vector<bool> visited;// vector of vetecies were true if visited
	int front, maxDiameter = 0;;
	visited.assign(graph.size(), false);//assign false for all vertecies
	distance.assign(graph.size(), 0);//assing 0 for all the distance
	queue<int> q;
	q.push(startingVertex);
	visited[startingVertex] = true;
	while (!q.empty())
	{// loop at the queue until we passed at the all vertecies in the same component with the starting vertex
		front = q.front();
		q.pop();
		for (auto v = graph[front].begin(); v != graph[front].end(); v++)
		{//run of the all vertecies and their neighbors
			if (!visited[*v])
			{
				q.push(*v);
				distance[*v] = distance[front] + 1;//set the distance of the current vertex
				visited[*v] = true;		
			}
		}
	}
	for (int i = 0; i < distance.size(); i++)//search for the heigher distance
		if (maxDiameter < distance[i]) 
			maxDiameter = distance[i];
	return maxDiameter;
}

int diameter(vector<vector <int>>& graph) 
{//return the diameter
	int maxDiameter = -1,diameter=0;
	if (connectivity(graph))//check if the graph is connected
	{
		for (int i = 0; i < graph.size(); i++)//call BFS on every vertecies of the graph that return the diameter 
		{
			diameter = BFSdiameter(graph, i);
			if (maxDiameter < diameter) //set the heigher diameter
				maxDiameter = diameter;
		}
	}
	return maxDiameter;
}

void writeToFile(double* threshold1, double* threshold2, double* threshold3,int* countConnectivity, int* countDiameter, int* countIsolated)
{//function that make file and write the result of the arrtibute
	ofstream algoFileConnectivity;
	ofstream algoFileDiameter;
	ofstream algoFileIsolated;
	algoFileConnectivity.open("algoConnectivity.csv");//open CSV File for connectivity
	algoFileDiameter.open("algoDiameter.csv");//open CSV File for diameter
	algoFileIsolated.open("algoIsolated.csv");//open CSV File for Isolated vertex
	algoFileConnectivity << "Connectivity" << endl;
	algoFileDiameter << "Diameter" << endl;
	algoFileIsolated << "Isolate" << endl;
	for (int i = 0; i < NO_PROB; i++) {
		//Write to CSV file the requested array probability
		algoFileConnectivity << "p=" << threshold1[i] << ",";
		algoFileDiameter << "p=" << threshold2[i] << ",";
		algoFileIsolated << "p=" << threshold2[i] << ",";
	}
	algoFileConnectivity << endl;
	algoFileDiameter << endl;
	algoFileIsolated << endl;
	for (int i = 0; i < NO_PROB; i++)
	{   //Write to CSV file probability of Connected graph after calculation  
		algoFileConnectivity << (double)countConnectivity[i] / NO_GRAPH << ",";
		//Write to CSV file probability of Diameter graph <= 2 after calculation 
		algoFileDiameter << (double)countDiameter[i] / NO_GRAPH << ",";
		//Write to CSV file probability of isolate graph after calculation    
		algoFileIsolated << (double)countIsolated[i] / NO_GRAPH << ",";
	}
}

void main()
{
	srand((unsigned)time(NULL));
	double threshold1[NO_PROB] = { 0.003,0.0052,0.0055,0.0062,0.0065, 0.0072,0.0075,0.008,0.01,0.012 };//0.00690775527
	double threshold2[NO_PROB] = { 0.05,0.11,0.112,0.113,0.115,0.12,0.125,0.13,0.135,0.2 };//0.11753940002
	double threshold3[NO_PROB] = { 0.004,0.0053,0.0055,0.006,0.0065,0.007,0.0075,0.008,0.01,0.012 }; //0.00690775527
	int count_is_isolated[NO_PROB] = { 0 };//the number of graph that have the requested the attribute
	int count_connectivity[NO_PROB] = { 0 };//the number of graph that have the requested the attribute
	int countDiameterequal2[NO_PROB] = { 0 };//the number of graph that have the requested the attribute
	int diam = 0;
	for (int i = 0; i < NO_PROB; i++)
	{//loop for the attribute 1
		for (int j = 0; j < NO_GRAPH; j++)
		{
			vector<vector<int>> graph = build_random_graph(NO_VERTICIES, threshold1[i]);
			if (connectivity(graph))
				count_connectivity[i]++;
		}
	}
	for (int i = 0; i < NO_PROB; i++)
	{//loop for the attribute 2
		for (int j = 0; j < NO_GRAPH; j++)
		{
			vector<vector<int>> graph = build_random_graph(NO_VERTICIES, threshold2[i]);
			diam = diameter(graph);
			if (diam <= 2 && diam != -1)
				countDiameterequal2[i]++;
		}
	}
	for (int i = 0; i < NO_PROB; i++)
	{//loop for the attribute 3
		for (int j = 0; j < NO_GRAPH; j++)
		{
			vector<vector<int>> graph = build_random_graph(NO_VERTICIES, threshold3[i]);
			if (is_isolated(graph))
				count_is_isolated[i]++;
		}
	}
	writeToFile(threshold1, threshold2, threshold3, count_connectivity, countDiameterequal2, count_is_isolated);
}
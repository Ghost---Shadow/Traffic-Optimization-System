#pragma once

#include"TrafficMap.h"

#include<list>

using namespace std;

class Dijkstra
{
private: 
	TrafficMap &map_;
	static const int infinity_;

	int findVertexWithMinDistance(vector<int> &distance,list<int> &unvisited);
	list<int> findNeighbours(int index);
	int manhattanDistance(int u, int v);
public:
	Dijkstra(TrafficMap &map);
	~Dijkstra(void);

	list<int> findShortestPath(int start,int end);
};


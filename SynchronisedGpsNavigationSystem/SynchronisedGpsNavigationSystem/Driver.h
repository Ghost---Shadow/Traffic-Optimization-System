#pragma once

#include"Dijkstra.h"
#include<chrono>

class Driver
{
private: 
	Dijkstra dijkstra_;
	TrafficMap &map_;
	int findPathWeight(list<int> &path);
	int id_;
	int start_,end_;
public:
	Driver(int id,TrafficMap &map);
	~Driver(void);
	int run(ofstream &file);
	int run();
	void setStartAndEnd(int start,int end);
};


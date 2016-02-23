#include "Driver.h"
#include<fstream>

Driver::Driver(int id,TrafficMap &map):dijkstra_(map),map_(map),id_(id)
{	
	long seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	//cout<<seed;
	default_random_engine dre; dre.seed(seed-id);
	uniform_int_distribution<int> uid(0,map_.getMapSize()-1);
	start_ = uid(dre);
	end_ = uid(dre);

	while(start_ == end_)
		end_ = uid(dre);
}
Driver::~Driver(void)
{}

void Driver::setStartAndEnd(int start,int end){
	start_ = start;
	end_ = end;
}

int Driver::run(ofstream &file){	
	file<<endl<<start_<<" "<<end_<<endl;
	list<int> path = dijkstra_.findShortestPath(start_,end_);
	int path_weight = findPathWeight(path);
	file<<"Driver: "<<id_<<"\nTime: "<<path_weight;
	map_.print(path,file);
	map_.reservePath(path);
	return path_weight;
}
int Driver::run(){	
	list<int> path = dijkstra_.findShortestPath(start_,end_);
	int path_weight = findPathWeight(path);
	map_.reservePath(path);
	return path_weight;
}

int Driver::findPathWeight(list<int> &path){
	int total = 0;
	for(int node: path){
		total += map_.getWeight(node); 
		total += map_.checkReservations(SpaceTime(node,total));
	}
	return total;
}

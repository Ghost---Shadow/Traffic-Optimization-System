#include "Dijkstra.h"

const int Dijkstra::infinity_ =  (unsigned int)-1>>1;

Dijkstra::Dijkstra(TrafficMap &map):
	map_(map){}
Dijkstra::~Dijkstra(void){}

list<int> Dijkstra::findShortestPath(int source,int target){
	list<int> path;
	list<int> unvisited;
	int map_size = map_.getMapSize();
	vector<int> distance; distance.resize(map_size);
	vector<int> previous; previous.resize(map_size);	

	distance[source] = 0;
	previous[source] = -1;

	for(int v = 0; v < map_size; v++){
		if(v != source){
			distance[v] = infinity_;
			previous[v] = -1;
		}
		unvisited.push_back(v);
	}

	while(!unvisited.empty()){
		int u = findVertexWithMinDistance(distance,unvisited);

		if(u == target){
			while(u != source){
				path.push_front(u);
				u = previous[u];
			}
			path.push_front(source);
			return path;
		}

		unvisited.remove(u);
		list<int> neighbours = findNeighbours(u);
		for(int v : neighbours){
			int alt = distance[u] + map_.getWeight(v);			
			if(map_.areReservationsEnabled()){
				SpaceTime temp(v,alt);
				alt += map_.checkReservations(temp); 
			}
			if(alt < distance[v]){
				distance[v] = alt;
				previous[v] = u;
			}
		}
	}

	return path;
}

int Dijkstra::findVertexWithMinDistance(vector<int> &distance,list<int> &unvisited){
	int smallest_index = unvisited.front();

	for(int index: unvisited){
		if(map_.areReservationsEnabled()){
			SpaceTime temp(index,distance[index]);
			if(distance[index]+ map_.checkReservations(temp)
				< distance[smallest_index]) 
				smallest_index = index;
		} else {
			if(distance[index] < distance[smallest_index] ) 
				smallest_index = index;
		}

	}

	return smallest_index;
}

list<int> Dijkstra::findNeighbours(int index){
	list<int> neighbours;
	int i,j;
	int x = index / map_.getWidth();
	int y = index % map_.getWidth();

	i = x-1; j = y; // West
	if(i >= 0 && j >= 0 && i < map_.getWidth() && j < map_.getHeight())
		neighbours.push_back(i * map_.getWidth() + j);

	i = x+1; j = y; // East
	if(i >= 0 && j >= 0 && i < map_.getWidth() && j < map_.getHeight())
		neighbours.push_back(i * map_.getWidth() + j);

	i = x; j = y-1; // North
	if(i >= 0 && j >= 0 && i < map_.getWidth() && j < map_.getHeight())
		neighbours.push_back(i * map_.getWidth() + j);

	i = x; j = y+1; // South
	if(i >= 0 && j >= 0 && i < map_.getWidth() && j < map_.getHeight())
		neighbours.push_back(i * map_.getWidth() + j);		

	return neighbours;
}

int Dijkstra::manhattanDistance(int u, int v){
	int u_x = u / map_.getWidth();
	int u_y = u % map_.getWidth();

	int v_x = v / map_.getWidth();
	int v_y = v % map_.getWidth();

	return abs(u_x - v_x) + abs(u_y - v_y);
}
#pragma once
#include<vector>
#include<list>
#include<iostream>
#include<random>
#include<map>
#include<fstream>

using namespace std;

struct SpaceTime{
	int space,time; 
	SpaceTime(int s,int t): space(s), time(t) {}
	friend bool operator<(const SpaceTime &s1, const SpaceTime &s2){
		return (s1.space + s1.time) < (s2.space + s2.time);
	}
};
class TrafficMap
{
private:
	map<SpaceTime,int> reservations_;
	vector<int> weight_map_;
	bool enable_reservations_;
	int width_,height_;
	bool onPath(list<int>&path,int index);
	void populateMap();
public:
	TrafficMap(int width,int height);
	~TrafficMap(void);

	void print();
	void print(list<int> &path);
	void print(list<int> &path,ofstream &file);
	int getWeight(int index);
	int getWidth();
	int getHeight();
	int getMapSize();
	void reserveSpacetime(SpaceTime s);
	int checkReservations(SpaceTime s);
	void setEnableReservations(bool b);
	bool areReservationsEnabled();
	void reservePath(list<int> &path);
	void clearReservations();
};


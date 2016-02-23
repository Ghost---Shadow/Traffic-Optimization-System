#include "TrafficMap.h"

TrafficMap::TrafficMap(int width,int height):
	width_(width),
	height_(height),
	enable_reservations_(true){
		weight_map_.resize(width_ * height_);
		populateMap();
}
TrafficMap::~TrafficMap(void){}

void TrafficMap::print(){
	for(int i = 0; i < weight_map_.size(); i++){
		if(i % width_ == 0) cout<<"\n";
		cout<<" "<<weight_map_[i]<<" ";
	}
	cout<<endl;
}
void TrafficMap::print(list<int> &path){
	for(int i = 0; i < weight_map_.size(); i++){
		if(i % width_ == 0) cout<<"\n";
		if(onPath(path,i))
			cout<<"["<<weight_map_[i]<<"]";
		else
			cout<<" "<<weight_map_[i]<<" ";
	}
	cout<<endl;
}

void TrafficMap::print(list<int> &path,ofstream &file){
	for(int i = 0; i < weight_map_.size(); i++){
		if(i % width_ == 0) file<<"\n";
		if(onPath(path,i))
			file<<"["<<weight_map_[i]<<"]";
		else
			file<<" "<<weight_map_[i]<<" ";
	}
	file<<endl;
}

void TrafficMap::clearReservations(){
	reservations_.clear();
}
bool TrafficMap::onPath(list<int>&path,int index){
	for(int i:path)
		if(i == index) return true;
	return false;
}

void TrafficMap::populateMap(){
	int range = 0;
	default_random_engine dre;
	uniform_int_distribution<int> uid(range,2*range);
	for(int i = 0; i < weight_map_.size(); i++)
		weight_map_[i] = uid(dre);
}

int TrafficMap::getMapSize(){
	return width_ * height_;
}

int TrafficMap::getWeight(int index){
	return weight_map_[index];
}

int TrafficMap::getWidth(){
	return width_;
}
int TrafficMap::getHeight(){
	return height_;
}
void TrafficMap::setEnableReservations(bool b){
	enable_reservations_ = b;
}
bool TrafficMap::areReservationsEnabled(){
	return enable_reservations_;
}

void TrafficMap::reservePath(list<int> &path){
	SpaceTime temp(0,0);
	int time = 0;
	for(int node:path){
		temp.space = node;
		time += weight_map_[node];
		temp.time = time;
		reserveSpacetime(temp);
	}
}

void TrafficMap::reserveSpacetime(SpaceTime s){
	reservations_[s]++;
}
int TrafficMap::checkReservations(SpaceTime s){
	auto found = reservations_.find(s);
    if(found != reservations_.end())
        return found->second;
    return 0; 
}
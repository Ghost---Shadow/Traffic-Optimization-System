#include"Driver.h"

using namespace std;

void testFunction1(int map_size,int max_drivers){
	TrafficMap map(map_size,map_size);
	vector<Driver> drivers;
	vector<int> deltas;
	deltas.resize(max_drivers);
	for(int i = 2; i < max_drivers; i++){		
		map.clearReservations();
		map.setEnableReservations(true);
		vector<int> with,without; 
		with.reserve(i); without.reserve(i);
		drivers.clear(); drivers.reserve(i);
		for(int j = 0; j < i; j++){
			drivers.emplace_back(j,map);
			with.push_back(drivers[j].run());			
		}
		map.clearReservations();

		map.setEnableReservations(false);
		for(int j = 0; j < i; j++){
			without.push_back(drivers[j].run());
			//cout<<with[j]<<" "<<without[j]<<endl;
			deltas[i] += without[j] - with[j];
		}
		cout<<i<<" ";
	}		
	ofstream database("Drivers.csv");
	for(int delta:deltas)
		database<<delta<<"\n";
	database.close();
}

void userInterface(){
	ofstream database("data.csv");
	ofstream paths("paths.txt");
	vector<int> with,without;	
	int driver_count;
	int map_size;
	cout<<"Enter map size: "; cin>>map_size;
	cout<<"Enter driver count: "; cin>>driver_count;
	TrafficMap map(map_size,map_size);

	if(database.is_open()) cout<<"data.csv opened\n";
	if(paths.is_open()) cout<<"path.txt opened\n";

	vector<Driver> drivers;
	drivers.reserve(driver_count);
	with.reserve(driver_count);
	without.reserve(driver_count);

	// Initialize drivers
	for(int i = 0; i < driver_count; i++)
		drivers.emplace_back(i,map);

	// Calculate paths using optimized algorithm
	map.setEnableReservations(true);
	cout<<"Calculate paths using optimized algorithm.\n";
	for(int i = 0; i < driver_count; i++){
		with.push_back(drivers[i].run(paths));
		if(driver_count % (i+1) == 0)
			cout<<"|";
	}
	cout<<endl;

	map.clearReservations();

	map.setEnableReservations(false);
	// Calculate paths without using optimized algorithm
	cout<<"Calculate paths without using optimized algorithm.\n";
	for(int i = 0; i < driver_count; i++){
		without.push_back(drivers[i].run(paths));
		if(driver_count % (i+1) == 0)
			cout<<"|";
	}
	cout<<endl;
	for(int i = 0; i < driver_count; i++)
		database<<with[i]<<","<<without[i]<<"\n";

	database.close();
	paths.close();
	cout<<"done\n";
}
int main(){

	userInterface();
	//testFunction1(4,256);
	system("pause");
	return 0;
}


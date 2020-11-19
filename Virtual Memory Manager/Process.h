
#include <iostream>
#include <string>
using namespace std;

class Process {
private:
	string data;
	int bytes;
	int id;
	int PA_LOW;
	int PA_HIGH;
	int VA_LOW;
	int VA_HIGH;
	bool inmemory;

public:

	void getData(string sd) {
		data = sd;
	}

	void showData() {
		cout << data << endl;
	}

};




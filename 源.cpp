#include<iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;



int main() {
	cout << "please input the number of suffix";
	int x;
	cin >> x;
	
	string filename = "C:\\Users\\My\\Documents\\Visual Studio 2015\\Projects\\week12\\Debug\\dictionary.txt";
	ifstream order1;
	string line;
	order1.open(filename);
	while (getline(order1, line)) {

	}

}
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include <sstream>
#include<map>

using namespace std;


void solvemaze(vector<vector<int>>a, int i, int j,int m, int n, map<int,vector<vector<int>>>&mazemap) {
	if (a[i][j] == 1) {
		//return false;
	}
	else if (a[i][j] == 2) {
		//return false;
	}
	else if (a[i][j] == 3) {
		//return false;
	}
	else if (a[i][j] == 5) {
		a[i][j] = 2;
		int path = 0;
		for (int i = 0; i != m; i++)
		{
			for (int j = 0; j != n; j++) {
				if (a[i][j] == 2) path++;
			}
		}
		mazemap[path] = a;
	}
	else {
		a[i][j] = 2;
		if (i > 0) {
			solvemaze(a, i - 1, j, m, n,mazemap);
				//return true;
		}
		if (i < m - 1) {
			solvemaze(a, i + 1, j, m, n,mazemap);
				//return true;
				
		}
		if (j > 0) {
			solvemaze(a, i, j - 1, m, n,mazemap);
				//return true;
			
		}
		if (j < n - 1) {
			solvemaze(a, i, j + 1, m, n,mazemap);
				//return true
		}

		a[i][j] = 3;
		//return false;
	}
}



int main() {

	ifstream maze;
	maze.open("C:\\Users\\My\\Documents\\Visual Studio 2015\\Projects\\week13习题课\\maze.txt");
	string mazedata;

	if (!maze.is_open()) {
		cerr << "打开文件失败！" << endl;
		return 1;
	}

	getline(maze, mazedata);
	stringstream stream;
	int m, n;
	stream << mazedata;
	stream >> m;
	stream >> n;

	vector<vector<int>>mazepath(m, vector<int>(n));
	map<int,vector<vector<int>>>mazemap;



	int i = 0;
	int data;
	while (getline(maze, mazedata)) {
		stringstream stream;
		stream << mazedata;
		for (int j = 0; j < n; j++) {
			stream >> data;
			mazepath[i][j] = data;
		}
		i++;
	}
	
	mazepath[m-1][n-1] = 5;

	solvemaze(mazepath, 0, 0, m, n,mazemap);

	map<int, vector<vector<int>>>::iterator iter;
	iter = mazemap.begin();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << iter->second[i][j]<<" ";
		}
		cout << endl;
	}
	cout << endl << iter->first;

	cin.get();
	cin.get();
	return 0;
}
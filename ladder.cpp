#include<iostream>

using namespace std;

int ladder(int n) {
	if (n == 1) {
		return 1;
	}
	else if (n == 0) {
		return 1;
	}
	else
		return ladder(n-2)+ladder(n-1);
}

int main() {
	int n;
	while (true) {
		cin >> n;
		cout << ladder(n) << endl;
	}
	cin.get();
	cin.get();
}
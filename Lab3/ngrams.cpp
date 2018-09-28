#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
#include<sstream>

/*
map<vector<string>,vector<string>>
前一个是key，后一个是value，key是前缀，value是跟在前缀后面的单词的全部，相同的单词可以出现多次。
先随机找到一个key，然后在value里面随机找一个单词，记为next，
然后再把key复制一份vector，删掉第一个元素，把next放到vector的最后一个，形成新的key，
如此循环，第一个key打印全部，后面的都只打印next，直到全部打印出来。
*/


using namespace std;
bool validN(string ssN1);//检查输入的N是否合理，合理返回true，否则返回false
int getN();	//得到并返回N；
bool validwords(string ssN1,int N1);//输入的word的数量是否合理


int main() {

	cout << "Input file name? ";		//读入文件
	string filename;
	cin >> filename;
	ifstream dic;
	dic.open("C:\\Users\\My\\Desktop\\serafini\\Ngrams\\res\\" + filename);

	while (!dic.is_open()) {
		cerr << "Unable to open that file.  Try again." << endl;
		cout << "Input file name?";
		cin >> filename;
		dic.open("C:\\Users\\My\\Desktop\\serafini\\Ngrams\\res\\" + filename);
	}

	cout << "Value of N? ";
	int N = getN();

	string word;
	vector<string>wordvec;
	map<vector<string>, vector<string>>wordmap;
	while (dic >> word) {
		wordvec.push_back(word);
	}

	for (int i = 0; i < wordvec.size(); i++) {
		vector<string>vector1;
		int j = 0;
		while (j < N - 1) {
			vector1.push_back(wordvec[(i + j) % wordvec.size()]);
			j++;
		}

		if (wordmap.count(vector1)) {
			wordmap[vector1].push_back(wordvec[(i + N - 1) % wordvec.size()]);
		}
		else {
			vector<string>vector2;
			vector2.push_back(wordvec[(i + N - 1) % wordvec.size()]);
			wordmap[vector1] = vector2;
		}
	}

	while (true) {
		cout << "# of random words to generate (0 to quit)? ";
		string ssN1;
		cin >> ssN1;
		while (!validwords(ssN1,N)) {	//直到得到符合规定的输入值
			cout << "# of random words to generate (0 to quit)? ";
			cin >> ssN1;
		}
		stringstream stream;
		stream << ssN1;
		int generate;
		stream >> generate;
		if (generate == 0) {
			cout << "Exiting.";
			return 0;
		}

		map<vector<string>, vector<string>>::iterator iter;

		int random_start = rand() % (wordmap.size());
		iter = wordmap.begin();
		for (int i = 0; i < random_start; i++) { iter++; };//随机起点

		cout << "... ";

		for (int i = 0; i < iter->first.size(); i++) {//打印第一次，打印N-1个单词
			cout << iter->first[i] << " ";
		}

		int rand2 = rand() % (iter->second.size());
		vector<string>vector3 = iter->first;
		string next = iter->second[rand2];

		for (int k = 0; k < generate - N + 1; k++) {	//继续打印，还需要打印generate-N+1次，每次打印一个单词。
			vector3.push_back(next);		//将后缀加到vector，
			vector3.erase(vector3.begin());	//去掉第一个单词，形成新的前缀
			cout << next << " ";
			int rand2 = rand() % wordmap[vector3].size();
			next = wordmap[vector3][rand2];		//更新next
		}

		cout << "..." << endl << endl;
	
	}
	
	return 1;
}


bool validN(string ssN1) {
	stringstream stream;
	stream << ssN1;
	int N;
	stream >> N;
	stream.clear();
	stream << N;
	string ssN2;
	stream >> ssN2;
	stream.clear();
	if (ssN1.length() != ssN2.length()) {
		cout << "Illegal integer format. Try again." << endl;
		return false;
	}
	else if (N < 2) {
		cout << "N must be 2 or greater." << endl;
		return false;
	}
	cout << endl;
	return true;
}

int getN() {
	string ssN1;
	cin >> ssN1;
	while (!validN(ssN1)) {
		cout << "Value of N? ";
		cin >> ssN1;
	}
	stringstream stream;
	stream << ssN1;
	int N;
	stream >> N;
	return N;
}

bool validwords(string ssN1,int N1) {
	stringstream stream;
	stream << ssN1;
	int N;
	stream >> N;
	stream.clear();
	stream << N;
	string ssN2;
	stream >> ssN2;
	stream.clear();
	if (ssN1.length() != ssN2.length()) {
		cout << "Illegal integer format. Try again." << endl;
		return false;
	}
	else if (N != 0 && N < N1) {
		cout << "Must be at least "<< N1<<" words." << endl;
		return false;
	}
	return true;
}

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
#include<sstream>

/*
map<vector<string>,vector<string>>
ǰһ����key����һ����value��key��ǰ׺��value�Ǹ���ǰ׺����ĵ��ʵ�ȫ������ͬ�ĵ��ʿ��Գ��ֶ�Ρ�
������ҵ�һ��key��Ȼ����value���������һ�����ʣ���Ϊnext��
Ȼ���ٰ�key����һ��vector��ɾ����һ��Ԫ�أ���next�ŵ�vector�����һ�����γ��µ�key��
���ѭ������һ��key��ӡȫ��������Ķ�ֻ��ӡnext��ֱ��ȫ����ӡ������
*/


using namespace std;
bool validN(string ssN1);//��������N�Ƿ����������true�����򷵻�false
int getN();	//�õ�������N��
bool validwords(string ssN1,int N1);//�����word�������Ƿ����


int main() {

	cout << "Input file name? ";		//�����ļ�
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
		while (!validwords(ssN1,N)) {	//ֱ���õ����Ϲ涨������ֵ
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
		for (int i = 0; i < random_start; i++) { iter++; };//������

		cout << "... ";

		for (int i = 0; i < iter->first.size(); i++) {//��ӡ��һ�Σ���ӡN-1������
			cout << iter->first[i] << " ";
		}

		int rand2 = rand() % (iter->second.size());
		vector<string>vector3 = iter->first;
		string next = iter->second[rand2];

		for (int k = 0; k < generate - N + 1; k++) {	//������ӡ������Ҫ��ӡgenerate-N+1�Σ�ÿ�δ�ӡһ�����ʡ�
			vector3.push_back(next);		//����׺�ӵ�vector��
			vector3.erase(vector3.begin());	//ȥ����һ�����ʣ��γ��µ�ǰ׺
			cout << next << " ";
			int rand2 = rand() % wordmap[vector3].size();
			next = wordmap[vector3][rand2];		//����next
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

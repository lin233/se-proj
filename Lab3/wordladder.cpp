#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<stack>
#include<set>
#include<queue>
#include<algorithm>
#include<sstream>

using namespace std;

string neighbor(string word1, string word2, set<string>&wordset, vector<char>change) {		//查找存在的neighbor并返回
	int length1 = word1.length();
	for (int i = 0; i < length1; i++) {
		string wordword = word1;
		for (int j = 0; j < 26; j++) {
			wordword[i] = change[j];
			if (wordword == word2)
				return word2;
			if (wordset.count(wordword) == 1) {
				wordset.erase(wordword);
				return wordword;
			}
		}
	}
	return "none_";		//这个单词没有neighbor，返回none_ ，加一个下划线以免和none混淆。
}

bool valid(string word1, string word2) {			//检查是否合理的word1和word2
	if (word1.length() != word2.length()) {
		cout << "The two words must be the same length." << endl << endl;
		return false;
	};
	if (word1 == word2) {
		cout << "The two words must be different." << endl << endl;
		return false;
	}

	return true;
}

string upper_to_lower(string word) {			//大写单词转化成小写
	for (int i = 0; i < word.length(); i++) {
		if (word[i] >= 'A' && word[i] <= 'Z')  //如果是大写单词就转化
			word[i] = word[i] - ('A' - 'a');
	}
	return word;		
}

int main() {

	vector<char>change;
	for (char ch = 'a'; ch <= 'z'; ch++) {
		change.push_back(ch);
	}

	cout << "Dictionary file name?";		//读入文件
	string filename;
	cin >> filename;
	ifstream dic;
	dic.open("C:\\Users\\My\\Documents\\Visual Studio 2015\\Projects\\lab3\\lab3\\Debug\\" + filename);

	while (!dic.is_open()) {
		cerr << "Unable to open that file.  Try again." << endl;
		cout << "Dictionary file name?";	
		cin >> filename;
		dic.open("C:\\Users\\My\\Documents\\Visual Studio 2015\\Projects\\lab3\\lab3\\Debug\\" + filename);
	}

	string line;
	set<string>bigset;
	while (getline(dic, line)) { 
		bigset.insert(line);			//将所有的单词都读入到bigset
	}
	cout << endl;

	set<string>wordset;
	string word1, word2;
	string tom;

	while (true) {
		getline(cin, tom);			//读入word1 和 word2
		cout << "Word #1 (or Enter to quit): ";
		char ch;
		ch = cin.get();
		if (ch == '\n') {
			cout << "Have a nice day";
			break;
		}
		cin.putback(ch);
		cin >> word1;

		getline(cin, tom);
		cout << "Word #2 (or Enter to quit): ";
		ch = cin.get();
		if (ch == '\n') {
			cout << "Have a nice day";
			cin.get();
			break;
		}
		cin.putback(ch);
		cin >> word2;

		while (!valid(word1, word2)) {
			getline(cin, tom);
			cout << "Word #1 (or Enter to quit): ";
			char ch;
			ch = cin.get();
			if (ch == '\n') {
				cout << "Have a nice day";
				return 0;
			}
			cin.putback(ch);
			cin >> word1;

			getline(cin, tom);
			cout << "Word #2 (or Enter to quit): ";
			ch = cin.get();
			if (ch == '\n') {
				cout << "Have a nice day";
				cin.get();
				return 0;
			}
			cin.putback(ch);
			cin >> word2;
		}


		word1 = upper_to_lower(word1);		//	将word1和word2都变成小写
		word2 = upper_to_lower(word2);
		int length1 = word1.size();

		set<string>::iterator it;		
		for (it = bigset.begin(); it != bigset.end(); it++) {	//把和word1，word2一样长度的单词找出来放进wordset，缩小查找范围
			if (it->length() == length1)
				wordset.insert(*it);
		}

		if (!(wordset.count(word1)&wordset.count(word2))) {
			cout << "The two words must be found in the dictionary." << endl << endl; 
		}
		else {
			wordset.erase(word1);
			wordset.erase(word2);	//已经发现过一次的单词就不用再留在wordset里面了
			
			stack<string>wordstack;
			wordstack.push(word1);

			queue<stack<string>>wordqueue;
			wordqueue.push(wordstack);

			stack<string>output;
			output.push("No word ladder found from " + word1 + " back to " + word2 + ".");		

			while (!wordqueue.empty()) {
				wordstack = wordqueue.front();
				string neibor = neighbor(wordstack.top(), word2, wordset, change);
				while (neibor != "none_") {
					if (neibor == word2) {
						cout << "A ladder from " + word1 + " to " + word2 + ": " << endl;
						output = wordqueue.front();
						output.push(word2);
						break;
					}
					else if (neibor != "none_") {
						stack<string>wordstack1;
						wordstack1 = wordstack;
						wordstack1.push(neibor);
						wordqueue.push(wordstack1);
						neibor = neighbor(wordstack.top(), word2, wordset, change);
					}
				}
				if (neibor == word2) {
					break;
				}
				wordqueue.pop();
			}

			int x = output.size();
			for (int i = 0; i < x; i++) {
				cout << output.top() << " ";
				output.pop();
			}
			cout << endl << endl;
		}
	}

	return 0;

}

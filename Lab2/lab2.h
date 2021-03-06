#pragma once
#include<iostream>
#include<vector>
#include<string>
#include <sstream>
using namespace std;

const char quit = 'q';
const char print = ';';
const string prompt = ">";
const string result = "=";
const char number = '8';
const char memory = 'M';
const char read = 'R';
stringstream scin;
stringstream change;

//void error(string s) {
	//throw runtime_error(s);
//}


class Token {	//tokenize
public:
	char kind;
	double value;
	Token(char ch)		// character
		:kind(ch), value(int(0)) {}
	Token(char ch, double val)		//number
		:kind(ch), value(val) {}
};


class Token_stream {  //read characters and compose tokens
public:
	Token_stream();
	Token get();
	void putback(Token t);
	void ignore(char c);
private:
	bool full;
	Token buffer;
};

Token_stream::Token_stream()//构造函数初始化
	:full(false), buffer(0) {
}

void Token_stream::ignore(char c)// c represents the kind of Token
{
	if (full&&c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin >> ch)
		if (ch == c)return;
}

void Token_stream::putback(Token t) {
	if (full)error("error");
	else {
		buffer = t;
		full = true;
	}
}

Token Token_stream::get()//read character from cin and compose a Token
{
	if (full) {			//check if we already have a Token ready
		full = false;
		return buffer;
	}

	char ch;
	scin >> ch;
	switch (ch)
	{
	case print:
	case quit:
	case memory:
	case read:
	case'!':
	case'(':
	case')':
	case'+':
	case'-':
	case'*':
	case'/':			//character
	case'%':
		return Token(ch);
	case'.':
	case'0':case'1':case'2':case'3':case'4':	//number
	case'5':case'6':case'7':case'8':case'9':
	{
		change << ch;//put digit back into the input stream
		string putback1, putback2, putput;
		change >> putback1;
		scin >> putback2;
		putput = putback1 + putback2;
		scin.clear();
		scin << putput;
		double val;
		scin >> val;		//read a floating-point number
		val;
		change.clear();
		return Token(number, val);
	}
	default:// invalid input
		error("error");
	}
}

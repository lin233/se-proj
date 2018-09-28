#include"lab.h"
using namespace std;

/*
	Simple calculate
	
	The grammar for input is:
	
	Statement:
		Memorize
		Print
		Quit

	Print:
		;

	Quit:
		q

	Memorize:
		Expression
	
	Expression:
		Term
		Expression + Term 
		Expression - Term

	Term:
		Second
		Term * Second
		Term / Second
		Term % Second

	Second:
		First
		+Second
		-Second

	First:
		Primary
		Primary!

	Primary:
		Number
		(Expression)
		Read

	Read:
		Memorize



*/

double expression();//declaration so that primary() can call expression()
Token_stream ts;
double storage;//for memorize and read 


void clean_up_mess()//clean error so that program can be continue
{
	ts.ignore(print);
}


int keep_window_open() {	//keep window open
	cout << "Please enter the character ~ to close the window\n";
	char ch;
	while (cin >> ch)
		if (ch == '~')return 1;
}

int	factorial(double n) {	// calculate factorial
	if (n != int(n) || n < 0)error("error");	//only positive integer is valid 
	if (n == 0)return 1;
	else return n*factorial(n - 1);
}

double primary() {			//deal with numbers£¬read storage and parentheses
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')error("error");
		return d; }
	case read:		//read storage
		return storage;
	case number:
		return t.value;
	default:
		error("error");
	}
}
double first() {		//deal with factorial
	double left = primary();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case'!': {
			return factorial(left); 
		}
		default: {
			ts.putback(t);
			return left; }
		}
	}
}
double second() {		//deal with positive number and negative number
	double left;
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+': {
			left = second();
			return left; }
		case'-': {
			left = -second();
			return left; }
		default: {
			ts.putback(t);
			return first(); }
		}
	}
}
double term() {		//	deal with * / and %
	double left = second();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left *= second();
			t = ts.get();
			break;
		case'/': {
			double d = second();
			if (d == 0)error("error");
			left /= d;
			t = ts.get();
			break; }
		case'%': {
			double d = second();
			int i1 = int(left);
			if (i1 != left)error("error");
			int i2 = int(d);
			if (i2 != d || i2 == 0)error("error");
			left = i1%i2;
			t = ts.get();
			break;
		}
		default: {
			ts.putback(t);
			return left; }
		}
	}
}

double expression() {  //deal with + and - 
	double left = term();
	Token t = ts.get();
	while (true) {
		switch (t.kind)
		{
		case '+':
			left += term();
			t = ts.get();
			break;

		case'-':
			left -= term();
			t = ts.get();
			break;

		default:
			ts.putback(t);
			return left;
			break;
		}
	}
}

double Memorize() { // deal with memory 
	double left = expression();
	Token t = ts.get();
	while (true) {
		switch (t.kind)
		{
		case memory: {
			storage = left;
			return storage;
			break; }
		default: {
			ts.putback(t);
			return left;
			break; }
		}
	}
}

void calculate() { //calculate 
	while (cin) {
		try {
			cout << prompt;
			Token t = ts.get();
			while (t.kind == print)t = ts.get();//eat ';'
			if (t.kind == quit) { keep_window_open(); }
			ts.putback(t);
			cout << result << Memorize() << endl;
		}
		catch (exception&e) {
			cerr << e.what() << endl;
			clean_up_mess();
		}
	}
}


int main() {
	try {
		calculate();
		keep_window_open();
		return 0;
	}
	catch (exception&e) {
		cerr << e.what() << endl;
		keep_window_open();
		return 1;
	}
}
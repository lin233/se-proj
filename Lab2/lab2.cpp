#include "Simple_window.h"
#include "Graph.h"
#include"calculate.h"
#include<iostream>
#include<vector>
#include<string>
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
/*文法基本沿用lab1，没有什么改动。只是把输入形式从cin改成了GUI的button输入，button输入字符串，然后用字符串的形式处理。支持lab1的所有计算。
有0 1 2 3 4 5 6 7 8 9 . + - * / % ! ( ) M R ,delete用于错误输入的时候退回一位，C用于清零。*/  

double expression();//declaration so that primary() can call expression()
Token_stream ts;
double storage;//for memorize and read 
string input_s;
string output_s;

void clean_up_mess()//clean error so that program can be continue
{
	//ts.ignore(print);
	output_s = "error";
	input_s = "";

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

double primary() {			//deal with numbers，read storage and parentheses
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
				  // while (true) {
	scin << input_s;
	try {
		Token t = ts.get();
		while (t.kind == print)t = ts.get();//eat ';'
		if (t.kind == quit) { keep_window_open(); }
		ts.putback(t);
		double M= Memorize();
		stringstream out;
		string s = "";
		out << M;
		out >> s;
		output_s = s;
		out.clear();
		
	}
	catch (exception&e) {
		//cerr << e.what() << endl;
		output_s = "error";
		clean_up_mess();
	}
	catch (...) {
		cerr << "excapetion\n" << endl;
		keep_window_open();
		clean_up_mess();
	}
}


struct Lines_window:Window
{
	Lines_window(Point xy, int w, int h, const string& title);
	void wait_for_button();

private:
	bool button_pushed = false;
	void next();

	Out_box input;	//输入显示框
	Out_box result;	//输出显示框


	Button cin_one;		//1
	void input_one();
	static void cb_one(Address, Address);
	
	Button cin_two;		//2
	void input_two();
	static void cb_two(Address, Address);

	Button cin_three;	//3
	void input_three();
	static void cb_three(Address, Address);

	Button cin_four;	//4
	void input_four();
	static void cb_four(Address, Address);

	Button cin_five;	//5
	void input_five();
	static void cb_five(Address, Address);
	
	Button cin_six;		//6
	void input_six();
	static void cb_six(Address, Address);

	Button cin_seven;	//7
	void input_seven();
	static void cb_seven(Address, Address);

	Button cin_eight;	//8
	void input_eight();
	static void cb_eight(Address, Address);

	Button cin_nine;	//9
	void input_nine();
	static void cb_nine(Address, Address);

	Button cin_zero;	//0
	void input_zero();
	static void cb_zero(Address, Address);

	Button cin_dot;		//.
	void input_dot();
	static void cb_dot(Address, Address);

	Button out_put;		// = 
	void put_result();
	static void cb_result(Address, Address);

	Button cin_add;		// +
	void add();
	static void cb_add(Address, Address);

	Button cin_minus;	// -
	void minus();
	static void cb_minus(Address, Address);


	Button cin_multiply;	//*
	void multiply();
	static void cb_multiply(Address, Address);

	Button cin_division;	//÷
	void division();
	static void cb_division(Address, Address);

	Button cin_left_bracket;	//(
	void left_bracket();
	static void cb_left_bracket(Address, Address);

	Button cin_right_bracket;	//)
	void right_bracket();
	static void cb_right_bracket(Address, Address);

	Button cin_exclamation;	//!
	void exclamation();
	static void cb_exclamation(Address, Address);

	Button cin_remainder;	//%
	void remainder();
	static void cb_remainder(Address, Address);

	Button cin_cin_delete;	//delete
	void cin_delete();
	static void cb_cin_delete(Address, Address);

	Button cin_cin_C;	//清零
	void cin_C();
	static void cb_cin_C(Address, Address);

	Button cin_cin_M;	//memory
	void cin_M();
	static void cb_cin_M(Address, Address);

	Button cin_cin_R;	//read
	void cin_R();
	static void cb_cin_R(Address, Address);
};

void Lines_window::cb_cin_R(Address, Address pw) {	//R
	reference_to<Lines_window>(pw).cin_R();
}
void Lines_window::cin_R() {
	input_s += "R"; input.put(input_s);
}

void Lines_window::cb_cin_M(Address, Address pw) {	//M
	reference_to<Lines_window>(pw).cin_M();
}
void Lines_window::cin_M() {
	input_s += "M"; input.put(input_s);
}

void Lines_window::cb_cin_C(Address, Address pw) {		//C
	reference_to<Lines_window>(pw).cin_C();
}
void Lines_window::cin_C() {
	input_s = ""; input.put(input_s); output_s = ""; result.put(output_s);
}

void Lines_window::cb_cin_delete(Address, Address pw) {	//delete
	reference_to<Lines_window>(pw).cin_delete();
}
void Lines_window::cin_delete() {
	int leng = input_s.size();
	input_s = input_s.substr(0, leng - 1); //字符串截取，去掉最后一位
	input.put(input_s);
}

void Lines_window::cb_remainder(Address, Address pw) {//%
	reference_to<Lines_window>(pw).remainder();
}
void Lines_window::remainder() { input_s += "%"; input.put(input_s); }

void Lines_window::cb_exclamation(Address, Address pw) {
	reference_to<Lines_window>(pw).exclamation();
}
void Lines_window::exclamation() { input_s += "!"; input.put(input_s); }//!

void Lines_window::cb_right_bracket(Address, Address pw) {
	reference_to<Lines_window>(pw).right_bracket();
}
void Lines_window::right_bracket() { input_s += ")"; input.put(input_s); }//(

void Lines_window::cb_left_bracket(Address, Address pw) {
	reference_to<Lines_window>(pw).left_bracket();
}
void Lines_window::left_bracket() { input_s += "("; input.put(input_s); }//)


void Lines_window::cb_division(Address, Address pw) {//  "/"
	reference_to<Lines_window>(pw).division();
}
void Lines_window::division() { input_s += "/"; input.put(input_s); }


void Lines_window::cb_multiply(Address, Address pw) {//*
	reference_to<Lines_window>(pw).multiply();
}
void Lines_window::multiply() { input_s += "*"; input.put(input_s); }


void Lines_window::cb_minus(Address, Address pw) {//-
	reference_to<Lines_window>(pw).minus();
}
void Lines_window::minus() { input_s += "-"; input.put(input_s); }

void Lines_window::cb_add(Address, Address pw) {//+
	reference_to<Lines_window>(pw).add();
}
void Lines_window::add() { input_s += "+"; input.put(input_s);}

void Lines_window::cb_result(Address, Address pw) {// = 
	reference_to<Lines_window>(pw).put_result();
}
void Lines_window::put_result() { input_s += ";"; calculate(); input_s = ""; result.put(output_s);  }


void Lines_window::cb_dot(Address, Address pw) {// .
	reference_to<Lines_window>(pw).input_dot();
}
void Lines_window::input_dot() { input_s += "."; input.put(input_s); }

void Lines_window::cb_zero(Address, Address pw) {
	reference_to<Lines_window>(pw).input_zero();
}
void Lines_window::input_zero() { input_s += "0"; input.put(input_s); }

void Lines_window::cb_nine(Address, Address pw) {
	reference_to<Lines_window>(pw).input_nine();
}
void Lines_window::input_nine() { input_s += "9"; input.put(input_s); }

void Lines_window::cb_eight(Address, Address pw) {
	reference_to<Lines_window>(pw).input_eight();
}
void Lines_window::input_eight() { input_s += "8"; input.put(input_s); }

void Lines_window::cb_seven(Address, Address pw) {
	reference_to<Lines_window>(pw).input_seven();
}
void Lines_window::input_seven() { input_s += "7"; input.put(input_s);}

void Lines_window::cb_six(Address, Address pw) {
	reference_to<Lines_window>(pw).input_six();
}
void Lines_window::input_six() { input_s += "6"; input.put(input_s); }

void Lines_window::cb_five(Address, Address pw) {
	reference_to<Lines_window>(pw).input_five();
}
void Lines_window::input_five() { input_s += "5"; input.put(input_s); }

void Lines_window::cb_four(Address, Address pw) {
	reference_to<Lines_window>(pw).input_four();
}
void Lines_window::input_four() { input_s += "4"; input.put(input_s); }

void Lines_window::cb_three(Address, Address pw) {
	reference_to<Lines_window>(pw).input_three();
}
void Lines_window::input_three() { input_s += "3"; input.put(input_s); }

void Lines_window::cb_two(Address, Address pw) {
	reference_to<Lines_window>(pw).input_two();
}
void Lines_window::input_two() { input_s += "2"; input.put(input_s); }

void Lines_window::cb_one(Address, Address pw) {
	reference_to<Lines_window>(pw).input_one();
}
void Lines_window::input_one() { input_s += "1"; input.put(input_s); }


void Lines_window::wait_for_button() {
	while (!button_pushed)Fl::wait();
	button_pushed = false;
	Fl::redraw();
}
void Lines_window::next() {
	button_pushed = true;
}


Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window(xy, w, h, title),
	cin_one(Point(10, 200), 80, 40, "1", cb_one),
	cin_two(Point(110, 200), 80, 40, "2", cb_two),
	cin_three(Point(210, 200), 80, 40, "3", cb_three),
	cin_four(Point(10, 250), 80, 40, "4", cb_four),
	cin_five(Point(110, 250), 80, 40, "5", cb_five),
	cin_six(Point(210, 250), 80, 40, "6", cb_six),
	cin_seven(Point(10, 300), 80, 40, "7", cb_seven),
	cin_eight(Point(110, 300), 80, 40, "8", cb_eight),
	cin_nine(Point(210, 300), 80, 40, "9", cb_nine),
	cin_zero(Point(110, 350), 80, 40, "0", cb_zero),
	cin_dot(Point(10, 350), 80, 40, ".", cb_dot),
	out_put(Point(210, 350), 80, 40, "=", cb_result),
	cin_add(Point(310, 200), 40, 40, "+", cb_add),
	cin_minus(Point(370, 200), 40, 40, "-", cb_minus),
	cin_multiply(Point(310, 250), 40, 40, "*", cb_multiply),
	cin_division(Point(370, 250), 40, 40, "/", cb_division),
	cin_left_bracket(Point(310, 300), 40, 40, "(", cb_left_bracket),
	cin_right_bracket(Point(370, 300), 40, 40, ")", cb_right_bracket),
	cin_exclamation(Point(310, 350), 40, 40, "!", cb_exclamation),
	cin_remainder(Point(370, 350), 40, 40, "%", cb_remainder),
	cin_cin_delete(Point(310, 150), 40, 40, "delete", cb_cin_delete),
	cin_cin_C(Point(370, 150), 40, 40, "C", cb_cin_C),
	cin_cin_M(Point(110, 150), 40, 40, "M", cb_cin_M),
	cin_cin_R(Point(70, 150), 40, 40, "R", cb_cin_R),
	input(Point(50, 10), 370, 50, "input"),
	result(Point(50, 80), 370, 50, "result")
{
	attach(cin_cin_R);
	attach(cin_cin_M);
	attach(cin_cin_C);
	attach(cin_cin_delete);
	attach(cin_remainder);
	attach(cin_exclamation);
	attach(cin_right_bracket);
	attach(cin_left_bracket);
	attach(result);
	attach(input);
	attach(cin_multiply);
	attach(cin_division);
	attach(cin_minus);
	attach(cin_add);
	attach(out_put);
	attach(cin_dot);
	attach(cin_zero);
	attach(cin_nine);
	attach(cin_eight);
	attach(cin_seven);
	attach(cin_five);
	attach(cin_six);
	attach(cin_four);
	attach(cin_three);
	attach(cin_two);
	attach(cin_one);
}

int main()
{
	using namespace Graph_lib;
	Point tl(100, 200);
	Lines_window win(tl, 450, 600, "calculator");
	win.wait_for_button();
	Point p1(100, 200);

}

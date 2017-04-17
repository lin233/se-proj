#include "Simple_window.h"
#include "Graph.h"
#include<iostream>
#include<vector>
using namespace std;

int main()
{

	using namespace Graph_lib;
	Point tl(100, 200);
	Simple_window win(tl, 700, 400, "Canvas");

	Point p1(100, 200);
	Point p2(150, 200);
	Point p3(300, 250);
	Point p4(250, 300);
	Point p5(150, 250);

	Point p6(300, 200);
	Point p7(450, 200);
	Point p8(600, 250);
	Point p9(550, 300);
	Point p10(450, 250);

	double x1 = 0; 
	double x2 = 0;
	double x3 = 0;
	double x4 = 0;
	double x5 = 0;
	vector<Point>haha{ p1,p2,p3,p4,p5 };
	vector<double>heihei{ x1,x2,x3,x4,x5 };

	Polygon convex;
	convex.add(p1);
	convex.add(p2);
	convex.add(p3);
	convex.add(p4);
	convex.add(p5);

	Polygon concave;
	concave.add(p6);
	concave.add(p7);
	concave.add(p8);
	concave.add(p9);
	concave.add(p10);

	int t = 0;
	for (int i = 0; i < 5; i++) {
		heihei[i] = ((haha[i % 5].x) - (haha[(i + 1) % 5].x))*((haha[i].y) - (haha[(i - 1 + 5) % 5].y)) -
			((haha[i].x) - (haha[(i - 1 + 5) % 5].x))*((haha[i].y) - (haha[(i + 1) % 5].y));
		if (heihei[i] < 0) {
			cout << "concave"; 
		}
		else t++;
	};
	if (t == 5)cout << "convex";;


	win.attach(convex);
	win.attach(concave);

	win.wait_for_button();
	return 0;
}

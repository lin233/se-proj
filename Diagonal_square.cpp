#include "Simple_window.h"
#include "Graph.h"
#include<iostream>

using namespace Graph_lib;

Vector_ref<Rectangle>rect;

int diagonal_square(int x, int y, int L, int order,Simple_window& win) {
	if (order <= 0 || L < 4) {
		for (int i = 0; i < rect.size(); i++)
			win.attach(rect[i]);
		return 0;
	}
	else {
		rect.push_back(new Rectangle(Point(x, y), L, L));
		rect.push_back(new Rectangle(Point(x, y + 3 * L / 4), L / 4, L / 4));
		rect.push_back(new Rectangle(Point(x + L / 4, y + L / 2), L / 4, L / 4));
		rect.push_back(new Rectangle(Point(x + L / 2, y + L / 4), L / 4, L / 4));
		rect.push_back(new Rectangle(Point(x + 3 * L / 4, y), L / 4, L / 4));
		return  diagonal_square(x, y + 3 * L / 4, L / 4, order - 1, win) + 
				diagonal_square(x + L / 4, y + 2 * L / 4, L / 4, order - 1, win) + 
				diagonal_square(x + L / 2, y + 1 * L / 4, L / 4, order - 1, win) + 
				diagonal_square(x + 3 * L / 4, y, L / 4, order - 1, win);
	}
};

int main()
{
	int x, y, L, order;
	std::cout << "Please input x:";
	std::cin >> x;
	std::cout << endl << "Please input y:";
	std::cin >> y;
	std::cout << endl << "Please input L:";
	std::cin >> L;
	std::cout << endl << "Please input order:";
	std::cin >> order;

	Point tl(100, 200);
	Simple_window win(tl, 1100, 1100, "Canvas");
	Point p1(100, 200);
	diagonal_square(x, y, L,order,win);

	win.wait_for_button();
	return 0;

}


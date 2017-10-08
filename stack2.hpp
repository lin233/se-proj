#include <iostream>
#include <boost/make_shared.hpp>
using namespace std;
template <class T>
class Stack{
private:
	shared_ptr<T> elem;
	int top_p;
	int maxSize;
	void doubleSpace(){
		shared_ptr<T> tmp = elem;
		elem = shared_ptr<int>(new int[maxSize*2],std::default_delete<int[]>());
		//elem = new T[2 * maxSize];
		//elem = p;
		for(int i = 0; i < maxSize; ++ i)
			elem.get()[i] = tmp.get()[i];
		maxSize *= 2;
		tmp.reset();
	}
public:
	Stack(){
		elem = shared_ptr<int>(new int[10],std::default_delete<int[]>());
		//elem = p;
		maxSize = 10;
		top_p = -1;
	}
	~Stack(){
		elem.reset();
	}
	Stack(const Stack& N){
		
	}
	Stack& operator=(const Stack&){
		
	}
	void push(T x){
		if(top_p == maxSize - 1) doubleSpace();
		elem.get()[ ++ top_p] = x;
	}
	bool pop(T& cell){
		if(top_p == -1) return false;
		cell = elem.get()[top_p -- ];
		return true;
	}
};
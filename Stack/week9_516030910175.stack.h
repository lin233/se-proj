#pragma once
#include<iostream>
#include<memory>
using namespace std;

template<class T>
class Node		//结点
{
public:
	T value;				//value保存值，front指向上一节点
	shared_ptr<Node<T>>front;//智能指针
	Node(T v)
		:value(v), front(NULL) {};
};

template<class T> 
class Stack {
	shared_ptr<Node<T>>top;  //top为顶层元素
	int numElems;		//元素数目
public:
	Stack();
	void push(T elem);
	bool pop(T& cell);
	Stack(const Stack&) = delete;
	Stack& operator=(const Stack&) = delete;

};

template <class T>
Stack<T>::Stack():numElems(0){}

template <class T>
void Stack<T>::push(T elem) {
	numElems++;
	shared_ptr<Node<T>>p1 = make_shared<Node<T>>(elem);
	p1->front = top;		//新插入的元素在top前
	top = p1;				//成为新的top
}

template <class T>
bool Stack<T>::pop(T& cell){
	if (numElems <= 0)return false;
	else{
		--numElems;
		cell = top->value;	//顶层元素录入到cell
		top = top->front;	//新的顶层
		return true;	
	}
}




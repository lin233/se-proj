#pragma once
#include<iostream>
#include<memory>
using namespace std;

template<class T>
class Node		//���
{
public:
	T value;				//value����ֵ��frontָ����һ�ڵ�
	shared_ptr<Node<T>>front;//����ָ��
	Node(T v)
		:value(v), front(NULL) {};
};

template<class T> 
class Stack {
	shared_ptr<Node<T>>top;  //topΪ����Ԫ��
	int numElems;		//Ԫ����Ŀ
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
	p1->front = top;		//�²����Ԫ����topǰ
	top = p1;				//��Ϊ�µ�top
}

template <class T>
bool Stack<T>::pop(T& cell){
	if (numElems <= 0)return false;
	else{
		--numElems;
		cell = top->value;	//����Ԫ��¼�뵽cell
		top = top->front;	//�µĶ���
		return true;	
	}
}




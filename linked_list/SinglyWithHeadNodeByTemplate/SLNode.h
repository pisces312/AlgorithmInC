#include<iostream>
template<class T>
class SLNode
{
public:
	T data;
	SLNode<T>* next;
	//SLNode(){}
	SLNode(T n)
	{
		data=n;
		next=NULL;
	}
};

#include<iostream.h>
class SLNode
{
public:
	int data;
	SLNode* next;
	SLNode(int n=0)
	{
		data=n;
		next=NULL;
	}
};

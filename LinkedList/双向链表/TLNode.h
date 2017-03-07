#include<iostream.h>
class TLNode
{
public:
	int data;
	TLNode *prior;
	TLNode *next;
	TLNode(int n=0)
	{
		data=n;
		prior=NULL;
		next=NULL;
	}
	~TLNode()
	{}
};

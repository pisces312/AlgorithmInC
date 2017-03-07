#include<iostream.h>
class SRLNode
{
public:
	int data;
	SRLNode* next;
	SRLNode(int n=0)
	{
		data=n;
		next=NULL;
	}
};

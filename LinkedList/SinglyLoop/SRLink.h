#include"SRLNode.h"
#include<stdlib.h>
class SRLink
{
public:
	SRLNode* head;
	SRLink();
	SRLink(int n);
	~SRLink();
	int length()const;
	bool isEmpty() const
	{
		return head==NULL;
	}
	bool isFull() const
	{
		return false;
	}
	bool isExist(int i) const;
	SRLNode* index(int i) const;
	int get(int i) const;
	bool set(int i,int n);
	SRLNode* insertbefore(SRLNode* p,int n);
	SRLNode* insertafter(SRLNode* p,int n);
	bool insertbefore(int i,int n);
	bool insertafter(int i,int n);
	bool remove(SRLNode* p);
	bool remove(int i);
	void reverse();
	void output() const;
	void output(SRLNode *p) const;
	void output(int n) const;
};





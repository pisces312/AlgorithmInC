#include"TLNode.h"
#include<stdlib.h>
class TLink
{
public:
	TLNode *head;
	TLink();
	TLink(int n);
	~TLink();
	int TLink::length()const;
	bool isEmpty() const
	{
		return head==NULL;
	}
	bool isFull() const
	{
		return false;
	}
	bool isExist(int i) const;
	TLNode* index(int i) const;
	int get(int i) const;
	bool set(int i,int n);
	TLNode* insertbefore(TLNode* p,int n);
	TLNode* insertafter(TLNode* p,int n);
	bool insertbefore(int i,int n);
	bool insertafter(int i,int n);
	bool remove(TLNode* p);
	bool remove(int i);
	void reverse();
	void reverseoutput() const;
	void output() const;
	void output(TLNode *p) const;
};

TLink::TLink()
{
	head=new TLNode;
}
TLink::TLink(int n)
{
	head=new TLNode;
	TLNode *p=head;
	if(n<0)
	{
		cout<<"输入错误!\n";
		exit(1);
	}
	for(int i=0;i<n;)
	{
		p->next=new TLNode;
		p->next->prior=p;
		p=p->next;
		p->data=++i;
	}
}
TLink::~TLink()
{
	TLNode *p=head,*t;
	while(p!=NULL)
	{
		t=p;
		p=t->next;
		delete t;
	}
	head=NULL;
}
bool TLink::isExist(int i) const
{
	if(i<1||i>length()) 
	{
		cout<<"输入错误! 结点"<<i<<"不存在!\n";
		return false;
	}
	return true;
}

int TLink::length()const
{
	TLNode *p=head->next;
	int i=0;
	while(p!=NULL)
	{
		i++;
		p=p->next;
	}
	return i;
}
TLNode* TLink::index(int i) const
{
	if(!isExist(i)) exit(1);
	TLNode *p=head->next;
	int j=0;
	while(p!=NULL&&j<i-1)
	{
		j++;
		p=p->next;
	}
	return p;
}
int TLink::get(int i) const
{
	if(!isExist(i)) exit(1);
	TLNode *p=head->next;
	int j=0;
	while(p!=NULL&&j<i-1)
	{
		j++;
		p=p->next;
	}
	return p->data;
}
bool TLink::set(int i,int n)
{
	if(!isExist(i)) 
	{
		cout<<"设置失败!\n";
		return false;
	}
	TLNode *p=head->next;
	int j=0;
	while(p!=NULL&&j<i-1)
	{
		j++;
		p=p->next;
	}
	p->data=n;
	return true;
}
TLNode* TLink::insertafter(TLNode* p,int n)
{
	TLNode *q=new TLNode(n);
	q->prior=p;
	q->next=p->next;
	if(p->next!=NULL)
	{
		p->next->prior=q;
	}
	p->next=q;
	return q;
}
TLNode* TLink::insertbefore(TLNode* p,int n)
{
	return insertafter(p->prior,n);
}
bool TLink::insertbefore(int i,int n)
{
	insertbefore(index(i),n);
	return true;
}
bool TLink::insertafter(int i,int n)
{
	insertafter(index(i),n);
	return true;
}
bool TLink::remove(TLNode* p)
{
	TLNode *t=p->next;
	p->prior->next=t;
	if(t!=NULL)
	{
		t->prior=p->prior;	
	}
	delete p;
	return true;
}
bool TLink::remove(int i)
{
	return remove(index(i));
}
void TLink::output(TLNode *p) const
{
	cout<<"Two Link: ";
	if(head->next==NULL)
	{
		cout<<"空表\n";
	}
	while(p!=NULL)
	{
		cout<<p->data;
		p=p->next;
		if(p!=NULL) cout<<"->";
	}
	cout<<endl;
}
void TLink::output() const
{
	output(head->next);
}
void TLink::reverse()
{
	TLNode *p=head->next,*q=NULL,*t=NULL;
	while(p!=NULL)
	{
		q=p->next;
		p->next=t;
		p->prior=q;
		t=p;
		p=q;
	}
	head->next=t;
}
void TLink::reverseoutput() const
{
	TLNode *p=head;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	cout<<"Reversed Two Link: ";
	while(p->prior!=NULL)
	{
		cout<<p->data;
		p=p->prior;
		if(p->prior!=NULL) cout<<"->";
	}
	cout<<endl;
}





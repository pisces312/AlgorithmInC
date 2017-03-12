#include"TLNode.h"
#include<stdlib.h>
class TRLink
{
public:
	TLNode *head;
	TRLink();
	TRLink(int n);
	~TRLink();
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
	void output(int n) const;
};

TRLink::TRLink()
{
	head=new TLNode;
	head->prior=head;
	head->next=head;
}
TRLink::TRLink(int n)
{
	head=new TLNode;
	TLNode *p=head;
	if(n<0)
	{
		std::cout<<"输入错误!\n";
		exit(1);
	}
	for(int i=0;i<n;)
	{
		p->next=new TLNode;
		p->next->prior=p;
		p=p->next;
		p->data=++i;
	}
	p->next=head;
	head->prior=p;
}
TRLink::~TRLink()
{
	TLNode *p=head->next,*t;
	while(p!=head)
	{
		t=p;
		p=t->next;
		delete t;
	}
	head=NULL;
}
bool TRLink::isExist(int i) const
{
	if(i<1||i>length())
	{
		std::cout<<"输入错误! 结点"<<i<<"不存在!\n";
		return false;
	}
	return true;
}

int TRLink::length()const
{
	TLNode *p=head->next;
	int i=0;
	while(p!=head)
	{
		i++;
		p=p->next;
	}
	return i;
}
TLNode* TRLink::index(int i) const
{
	if(!isExist(i)) exit(1);
	TLNode *p=head->next;
	int j=0;
	while(p!=head&&j<i-1)
	{
		j++;
		p=p->next;
	}
	return p;
}
int TRLink::get(int i) const
{
	if(!isExist(i)) exit(1);
	TLNode *p=head->next;
	int j=0;
	while(p!=head&&j<i-1)
	{
		j++;
		p=p->next;
	}
	return p->data;
}
bool TRLink::set(int i,int n)
{
	if(!isExist(i))
	{
		std::cout<<"设置失败!\n";
		return false;
	}
	TLNode *p=head->next;
	int j=0;
	while(p!=head&&j<i-1)
	{
		j++;
		p=p->next;
	}
	p->data=n;
	return true;
}
TLNode* TRLink::insertafter(TLNode* p,int n)
{
	TLNode *q=new TLNode(n);
	q->prior=p;
	q->next=p->next;
	if(p->next!=head)
	{
		p->next->prior=q;
	}
	p->next=q;
	return q;
}
TLNode* TRLink::insertbefore(TLNode* p,int n)
{
	return insertafter(p->prior,n);
}
bool TRLink::insertbefore(int i,int n)
{
	insertbefore(index(i),n);
	return true;
}
bool TRLink::insertafter(int i,int n)
{
	insertafter(index(i),n);
	return true;
}
bool TRLink::remove(TLNode* p)
{
	TLNode *t=p->next;
	p->prior->next=t;
	if(t!=head)
	{
		t->prior=p->prior;
	}
	delete p;
	return true;
}
bool TRLink::remove(int i)
{
	return remove(index(i));
}
void TRLink::output(TLNode *p) const
{
	std::cout<<"Two Link: ";
	if(head->next==head)
	{
		std::cout<<"空表\n";
	}
	while(p!=head)
	{
		std::cout<<p->data;
		p=p->next;
		if(p!=head) std::cout<<"->";
	}
	std::cout<<std::endl;
}
void TRLink::output() const
{
	output(head->next);
}
void TRLink::output(int n) const
{
	TLNode *p=head->next;
	int i=0;
	std::cout<<"Two Ring Link: ";
	while(i<n)
	{
		if(p==head)
		{
			p=p->next;
		}
		std::cout<<p->data;
		if(++i!=n) std::cout<<"->";
		p=p->next;
	}
	std::cout<<std::endl;
}
void TRLink::reverse()
{
	TLNode *p=head->next,*q=NULL,*t=NULL;
	while(p!=head)
	{
		q=p->next;
		p->next=t;
		p->prior=q;
		t=p;
		p=q;
	}
	head->next=t;
}
void TRLink::reverseoutput() const
{
	TLNode *p=head;
	while(p->next!=head)
	{
		p=p->next;
	}
	std::cout<<"Reversed Two Link: ";
	while(p->prior!=head)
	{
		std::cout<<p->data;
		p=p->prior;
		if(p->prior!=head) std::cout<<"->";
	}
	std::cout<<std::endl;
}





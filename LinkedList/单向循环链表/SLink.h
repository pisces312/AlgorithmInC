#include"SLNode.h"
#include<stdlib.h>
class SLink
{
public:
	SLNode* head;
	SLink();
	SLink(int n);
	~SLink();
	int SLink::length()const;
	bool isEmpty() const
	{
		return head==NULL;
	}
	bool isFull() const
	{
		return false;
	}
	bool isExist(int i) const;
	SLNode* index(int i) const;
	int get(int i) const;
	bool set(int i,int n);
	SLNode* insertbefore(SLNode* p,int n);
	SLNode* insertafter(SLNode* p,int n);
	bool insertbefore(int i,int n);
	bool insertafter(int i,int n);
	bool remove(SLNode* p);
	bool remove(int i);
	void reverse();
	void output() const;
	void output(SLNode *p) const;
};
SLink::SLink()
{
	head=new SLNode;
}
SLink::SLink(int n)
{
	head=new SLNode;
	SLNode *p=head;
	if(n<0)
	{
		cout<<"输入错误!\n";
		exit(1);
	}
	for(int i=0;i<n;)
	{
		p->next=new SLNode;
		p=p->next;
		p->data=++i;
	}
}
SLink::~SLink()
{
	SLNode *p=head,*t;
	while(p!=NULL)
	{
		t=p;
		p=t->next;
		delete t;
	}
	head=NULL;
}
bool SLink::isExist(int i) const
{
	if(i<1||i>length()) 
	{
		cout<<"输入错误! 结点"<<i<<"不存在!\n";
		return false;
	}
	return true;
}

int SLink::length()const
{
	SLNode *p=head->next;
	int i=0;
	while(p!=NULL)
	{
		i++;
		p=p->next;
	}
	return i;
}
SLNode* SLink::index(int i) const
{
	if(!isExist(i)) exit(1);
	SLNode *p=head->next;
	int j=0;
	while(p!=NULL&&j<i-1)
	{
		j++;
		p=p->next;
	}
	return p;
}
int SLink::get(int i) const
{
	if(!isExist(i)) exit(1);
	SLNode *p=head->next;
	int j=0;
	while(p!=NULL&&j<i-1)
	{
		j++;
		p=p->next;
	}
	return p->data;
}
bool SLink::set(int i,int n)
{
	if(!isExist(i)) 
	{
		cout<<"设置失败!\n";
		return false;
	}
	SLNode *p=head->next;
	int j=0;
	while(p!=NULL&&j<i-1)
	{
		j++;
		p=p->next;
	}
	p->data=n;
	return true;
}
SLNode* SLink::insertbefore(SLNode* p,int n)
{
	SLNode *q=head->next,*t=head;
	while(q!=p&&q!=NULL)
	{
		t=q;
		q=q->next;
	}
	if(q==p)
	{
		q=t->next;
		t->next=new SLNode(n);
		t->next->next=q;
		return t->next;
	}
	else
	{
		cout<<"无法插入!\n";
		exit(1);
	}
}
SLNode* SLink::insertafter(SLNode* p,int n)
{
	SLNode *t=p->next;
	p->next=new SLNode(n);
	p->next->next=t;
	return p->next;
}
bool SLink::insertbefore(int i,int n)
{
	insertbefore(index(i),n);
	return true;
}
bool SLink::insertafter(int i,int n)
{
	insertafter(index(i),n);
	return true;
}
bool SLink::remove(SLNode* p)
{
	SLNode *q=head->next,*t=head;
	while(q!=p&&q!=NULL)
	{
		t=q;
		q=q->next;
	}
	if(q==p)
	{
		q=q->next;
		delete t->next;
		t->next=q;
		return true;
	}
	else
	{
		cout<<"无法删除!\n";
		exit(1);
	}
	return false;
}
bool SLink::remove(int i)
{
	return remove(index(i));
}
void SLink::output(SLNode *p) const
{
	cout<<"Single Link: ";
	if(head->next==NULL)
	{
		cout<<"空表\n";
	}
	while(p!=NULL)
	{
		cout<<p->data<<" ";
		p=p->next;
	}
	cout<<endl;
}
void SLink::output() const
{
	output(head->next);
}
void SLink::reverse()
{
	SLNode *p=head->next,*q,*t=NULL;
	while(p!=NULL)
	{
		q=p->next;
		p->next=t;
		t=p;
		p=q;
	}
	head->next=t;
}




#include"SRLNode.h"
#include<stdlib.h>
class SRLink
{
public:
	SRLNode* head;
	SRLink();
	SRLink(int n);
	~SRLink();
	int SRLink::length()const;
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
SRLink::SRLink()
{
	head=new SRLNode;
	head->next=head;
}
SRLink::SRLink(int n)
{
	head=new SRLNode;
	SRLNode *p=head;
	if(n<0)
	{
		cout<<"输入错误!\n";
		exit(1);
	}
	for(int i=0;i<n;)
	{
		p->next=new SRLNode;
		p=p->next;
		p->data=++i;
	}
	p->next=head;
}
SRLink::~SRLink()
{
	SRLNode *p=head->next,*t;
	while(p!=head)
	{
		t=p;
		p=t->next;
		delete t;
	}
	delete head;
}
bool SRLink::isExist(int i) const
{
	if(i<1||i>length()) 
	{
		cout<<"输入错误! 结点"<<i<<"不存在!\n";
		return false;
	}
	return true;
}

int SRLink::length()const
{
	SRLNode *p=head->next;
	int i=0;
	while(p!=head)
	{
		i++;
		p=p->next;
	}
	return i;
}
SRLNode* SRLink::index(int i) const
{
	if(!isExist(i)) exit(1);
	SRLNode *p=head->next;
	int j=0;
	while(p!=head&&j<i-1)
	{
		j++;
		p=p->next;
	}
	return p;
}
int SRLink::get(int i) const
{
	if(!isExist(i)) exit(1);
	SRLNode *p=head->next;
	int j=0;
	while(p!=head&&j<i-1)
	{
		j++;
		p=p->next;
	}
	return p->data;
}
bool SRLink::set(int i,int n)
{
	if(!isExist(i)) 
	{
		cout<<"设置失败!\n";
		return false;
	}
	SRLNode *p=head->next;
	int j=0;
	while(p!=head&&j<i-1)
	{
		j++;
		p=p->next;
	}
	p->data=n;
	return true;
}
SRLNode* SRLink::insertbefore(SRLNode* p,int n)
{
	SRLNode *q=head->next,*t=head;
	while(q!=p&&q!=head)
	{
		t=q;
		q=q->next;
	}
	if(q==p)
	{
		q=t->next;
		t->next=new SRLNode(n);
		t->next->next=q;
		return t->next;
	}
	else
	{
		cout<<"无法插入!\n";
		exit(1);
	}
}
SRLNode* SRLink::insertafter(SRLNode* p,int n)
{
	SRLNode *t=p->next;
	p->next=new SRLNode(n);
	p->next->next=t;
	return p->next;
}
bool SRLink::insertbefore(int i,int n)
{
	insertbefore(index(i),n);
	return true;
}
bool SRLink::insertafter(int i,int n)
{
	insertafter(index(i),n);
	return true;
}
bool SRLink::remove(SRLNode* p)
{
	SRLNode *q=head->next,*t=head;
	while(q!=p&&q!=head)
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
bool SRLink::remove(int i)
{
	return remove(index(i));
}
void SRLink::output(SRLNode *p) const
{
	cout<<"Single Ring Link: ";
	if(head->next==head)
	{
		cout<<"空表\n";
	}
	while(p!=head)
	{
		cout<<p->data;
		p=p->next;
		if(p!=head) cout<<"->";
	}
	cout<<endl;
}
void SRLink::output() const
{
	output(head->next);
}
void SRLink::output(int n) const
{
	SRLNode *p=head->next;
	int i=0;
	cout<<"Single Ring Link: ";
	while(i<n)
	{
		if(p==head)
		{
			p=p->next;
		}
		cout<<p->data;
		if(++i!=n) cout<<"->";
		p=p->next;
	}
	cout<<endl;
}
void SRLink::reverse()
{
	SRLNode *p=head->next,*q,*t=head;
	while(p!=head)
	{
		q=p->next;
		p->next=t;
		t=p;
		p=q;
	}
	head->next=t;
}




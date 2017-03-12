#include"SRLink.h"

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
		std::cout<<"输入错误!\n";
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
		std::cout<<"输入错误! 结点"<<i<<"不存在!\n";
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
		std::cout<<"设置失败!\n";
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
		std::cout<<"无法插入!\n";
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
		std::cout<<"无法删除!\n";
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
	std::cout<<"Single Ring Link: ";
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
void SRLink::output() const
{
	output(head->next);
}
void SRLink::output(int n) const
{
	SRLNode *p=head->next;
	int i=0;
	std::cout<<"Single Ring Link: ";
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

//Test
void testSRLink2()
{
	SRLink list(5);
	std::cout<<list.get(3)<<std::endl;
	list.insertafter(5,6);
	list.remove(5);
	list.reverse();

	list.output();
	list.output(19);
}

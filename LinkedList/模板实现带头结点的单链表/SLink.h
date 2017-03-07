#include"SLNode.h"
#include<stdlib.h>
template<class T>
class SLink
{
public:
	SLNode<T>* head;
	SLink();
	SLink(int n);
	SLink(int* array,int n);
	SLink(SLink<T> &list);
	~SLink();
	int length();
	bool isEmpty()
	{
		return head==NULL;
	}
	bool isFull() 
	{
		return false;
	}
	bool isExist(int i);
	SLNode<T>* index(int i);
	T get(int i);
	bool set(int i,T n);
	SLNode<T>* insertbefore(SLNode<T>* p,T n);
	SLNode<T>* insertafter(SLNode<T>* p,T n);
	bool insertbefore(int i,T n);
	bool insertafter(int i,T n);
	bool RemoveNode(SLNode<T>* p);
	bool RemoveNode(int i);
	bool RemoveData(T n);
	void reverse();
	void output();
	void output(SLNode<T> *p);
	int sum();
	SLNode<T>* searchdata(T n);
	SLink<T>* AddLink(SLink<T> a);
};
template<class T>
SLink<T>::SLink()
{
	head=new SLNode<T>(' ');
}
template<class T>
SLink<T>::SLink(int n)
{
	head=new SLNode<T>('\0');
	if(n<0)
	{
		cout<<"输入错误!\n";
		exit(1);
	}
	SLNode<T> *p=head;
	for(int i=0;i<n;i++)
	{
		p->next=new SLNode<T>('\0');
		p=p->next;
	}
}
template<class T>
SLink<T>::SLink(int* array,int n)
{
	head=new SLNode<T>;
	SLNode<T> *p=head;
	for(int i=0;i<n;i++)
	{
		p->next=new SLNode<T>;
		p=p->next;
		p->data=*(array+i);
	}
}
template<class T>
SLink<T>::SLink(SLink<T> &list)
{
	head=new SLNode<T>;
	SLNode<T> *p=(list.head)->next,*t=head;	
	while(p!=NULL)
	{
		insertafter(t,p->data);
		t=t->next;
		p=p->next;
	}
}
template<class T>
SLink<T>::~SLink()
{
	SLNode<T> *p=head,*t;
	while(p!=NULL)
	{
		t=p;
		p=t->next;
		delete t;
	}
	head=NULL;
}
template<class T>
bool SLink<T>::isExist(int i) 
{
	if(i<1||i>length()) 
	{
		cout<<"输入错误! 结点"<<i<<"不存在!\n";
		return false;
	}
	return true;
}
template<class T>
int SLink<T>::length()
{
	SLNode<T> *p=head->next;
	int i=0;
	while(p!=NULL)
	{
		i++;
		p=p->next;
	}
	return i;
}
template<class T>
SLNode<T>* SLink<T>::index(int i) 
{
	if(!isExist(i)) exit(1);
	SLNode<T> *p=head->next;
	int j=0;
	while(p!=NULL&&j<i-1)
	{
		j++;
		p=p->next;
	}
	return p;
}
template<class T>
T SLink<T>::get(int i) 
{
	if(!isExist(i)) exit(1);
	SLNode<T> *p=head->next;
	int j=0;
	while(p!=NULL&&j<i-1)
	{
		j++;
		p=p->next;
	}
	return p->data;
}
template<class T>
bool SLink<T>::set(int i,T n)
{
	SLNode<T> *p=head;
	int c=0;
	while(p->next!=NULL&&c!=i)
	{
		p=p->next;
		c++;
	}
	if(c==i) p->data=n;
	else
	{
		while(c!=i-1)
		{
			cout<<"dafsd\n";
			c++;
			p->next=new SLNode<T>('\0');
			p=p->next;
		}
		p->next=new SLNode<T>(n);
	}
	return true;
}
template<class T>
SLNode<T>* SLink<T>::insertbefore(SLNode<T>* p,T n)
{
	SLNode<T> *q=head->next,*t=head;
	while(q!=p&&q!=NULL)
	{
		t=q;
		q=q->next;
	}
	if(q==p)
	{
		q=t->next;
		t->next=new SLNode<T>(n);
		t->next->next=q;
		return t->next;
	}
	else
	{
		cout<<"无法插入!\n";
		exit(1);
	}
}
template<class T>
SLNode<T>* SLink<T>::insertafter(SLNode<T>* p,T n)
{
	
	SLNode<T> *t=p->next;
	p->next=new SLNode<T>(n);
	p->next->next=t;
	return p->next;
}
template<class T>
bool SLink<T>::insertbefore(int i,T n)
{
	insertbefore(index(i),n);
	return true;
}
template<class T>
bool SLink<T>::insertafter(int i,T n)
{
	insertafter(index(i),n);
	return true;
}
template<class T>
bool SLink<T>::RemoveNode(SLNode<T>* p)
{
	SLNode<T> *q=head->next,*t=head;
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
template<class T>
bool SLink<T>::RemoveNode(int i)
{
	return RemoveNode(index(i));
}
template<class T>
bool SLink<T>::RemoveData(T n)
{
	return RemoveNode(searchdata(n));
}
template<class T>
void SLink<T>::output(SLNode<T>* p) 
{
	cout<<"Single Link: ";
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
template<class T>
void SLink<T>::output() 
{
	output(head->next);
}
template<class T>
void SLink<T>::reverse()
{
	SLNode<T> *p=head->next,*q,*t=NULL;
	while(p!=NULL)
	{
		q=p->next;
		p->next=t;
		t=p;
		p=q;
	}
	head->next=t;
}
template<class T>
int SLink<T>::sum()
{
	SLNode<T> *p=head->next;
	int s=0;
	while(p!=NULL)
	{
		s+=p->data;
		p=p->next;
	}
	return s;
}
template<class T>
SLNode<T>* SLink<T>::searchdata(T n) 
{
	SLNode<T> *p=head->next;
	while(p!=NULL)
	{
		if(p->data==n)	return p;
		p=p->next;
	}
	return NULL;
}
template<class T>
SLink<T>* SLink<T>::AddLink(SLink<T> a)
{
	SLink<T> *c=new SLink<T>;
	SLNode<T> *p=head->next,*t=c->head;
	
	while(p!=NULL)
	{
		c->insertafter(t,p->data);
		t=t->next;
		p=p->next;
	}
	p=a.head->next;
	while(p!=NULL)
	{
		c->insertafter(t,p->data);
		t=t->next;
		p=p->next;
	}
	return c;
}

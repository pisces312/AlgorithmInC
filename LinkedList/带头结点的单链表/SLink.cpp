#include"SLink.h"
#include<iostream>
using namespace std;

int test() {
    SLink list1(10),list2(30);
    SLink list3(list2);
    list3.output();
    return 0;
}
SLNode::SLNode(int n):data(n),next(NULL) {
}
SLink::SLink():head(NULL) {
    head=new SLNode;
}
SLink::SLink(int n):head(NULL) {
    head=new SLNode;
    SLNode *p=head;
    for(int i=0; i<n;) {
        p->next=new SLNode;
        p=p->next;
        p->data=++i;
    }
}
SLink::SLink(int* array,int n=0):head(NULL) {
    head=new SLNode;
    SLNode *p=head;
    for(int i=0; i<n; i++) {
        p->next=new SLNode;
        p=p->next;
        p->data=*(array+i);
    }
}
SLink::SLink(SLink &list):head(NULL) {
    head=new SLNode;
    SLNode *p=(list.head)->next,*t=head;
    while(p!=NULL) {
        insertafter(t,p->data);
        t=t->next;
        p=p->next;
    }
}
SLink::~SLink() {
    SLNode *p=head,*t;
    while(p!=NULL) {
        t=p;
        p=t->next;
        delete t;
    }
    head=NULL;
}

bool SLink::isEmpty() const {
    return head==NULL;
}
bool SLink::isFull() const {
    return false;
}
bool SLink::isExist(int i) const {
    if(i<1||i>length()) {
        cout<<"输入错误! 结点"<<i<<"不存在!\n";
        return false;
    }
    return true;
}

int SLink::length()const {
    SLNode *p=head->next;
    int i=0;
    while(p!=NULL) {
        i++;
        p=p->next;
    }
    return i;
}
SLNode* SLink::index(int i) const {
    if(!isExist(i)) return NULL;
    SLNode *p=head->next;
    int j=0;
    while(p!=NULL&&j<i-1) {
        j++;
        p=p->next;
    }
    return p;
}
//int SLink::get(int i) const {
//    if(!isExist(i)) return NULL;
//    SLNode *p=head->next;
//    int j=0;
//    while(p!=NULL&&j<i-1) {
//        j++;
//        p=p->next;
//    }
//    return p->data;
//}
bool SLink::set(int i,int n) {
    if(!isExist(i)) {
        return false;
    }
    SLNode *p=head->next;
    int j=0;
    while(p!=NULL&&j<i-1) {
        j++;
        p=p->next;
    }
    p->data=n;
    return true;
}
SLNode* SLink::insertbefore(SLNode* p,int n) {
    SLNode *q=head->next,*t=head;
    while(q!=p&&q!=NULL) {
        t=q;
        q=q->next;
    }
    if(q==p) {
        q=t->next;
        t->next=new SLNode(n);
        t->next->next=q;
        return t->next;
    }
    return NULL;
}
SLNode* SLink::insertafter(SLNode* p,int n) {

    SLNode *t=p->next;
    p->next=new SLNode(n);
    p->next->next=t;
    return p->next;
}
bool SLink::insertbefore(int i,int n) {
    insertbefore(index(i),n);
    return true;
}
bool SLink::insertafter(int i,int n) {
    insertafter(index(i),n);
    return true;
}
bool SLink::removeNode(SLNode* p) {
    SLNode *q=head->next,*t=head;
    while(q!=p&&q!=NULL) {
        t=q;
        q=q->next;
    }
    if(q==p) {
        q=q->next;
        delete t->next;
        t->next=q;
        return true;
    }
    return false;
}
bool SLink::removeNode(int i) {
    return removeNode(index(i));
}
bool SLink::removeData(int n) {
    return removeNode(searchdata(n));
}

void SLink::output(SLNode *p) const {
    cout<<"Single Link: ";
    if(head->next==NULL) {
        cout<<"空表\n";
    }
    while(p!=NULL) {
        cout<<p->data;
        p=p->next;
        if(p!=NULL) cout<<"->";
    }
    cout<<endl;
}
void SLink::output() const {
    output(head->next);
}
void SLink::reverse() {
    SLNode *p=head->next,*q,*t=NULL;
    while(p!=NULL) {
        q=p->next;
        p->next=t;
        t=p;
        p=q;
    }
    head->next=t;
}
int SLink::sum() {
    SLNode *p=head->next;
    int s=0;
    while(p!=NULL) {
        s+=p->data;
        p=p->next;
    }
    return s;
}
SLNode* SLink::searchdata(int n) const {
    SLNode *p=head->next;
    while(p!=NULL) {
        if(p->data==n)	return p;
        p=p->next;
    }
    return NULL;
}
SLink* SLink::AddLink(SLink a) {
    SLink *c=new SLink;
    SLNode *p=head->next,*t=c->head;

    while(p!=NULL) {
        c->insertafter(t,p->data);
        t=t->next;
        p=p->next;
    }
    p=a.head->next;
    while(p!=NULL) {
        c->insertafter(t,p->data);
        t=t->next;
        p=p->next;
    }
    return c;
}




#include"OneLink.h"
#include<iostream>
using namespace std;
OneLink::OneLink() {
    head=new OneLinkNode();
}
OneLink::OneLink(int n) {
    head=NULL;
    OneLinkNode *p,*t;
    int i=1;
    head=new OneLinkNode(i++);
    p=head;
    while(i<=n) {
        t=new OneLinkNode(' ');
        p->next=t;
        p=t;
        ++i;
    }
}
OneLink::~OneLink() {
    OneLinkNode *p=head,*t;
    while(p!=NULL) {
        t=p;
        p=p->next;
        delete t;
    }
    head=NULL;
}
int OneLink::length()const {
    OneLinkNode *p=head;
    int i=0;
    while(p!=NULL) {
        i++;
        p=p->next;
    }
    return i;
}
OneLinkNode* OneLink::index(int i)const {
    if(i<=0) return NULL;
    int j=1;
    OneLinkNode *p=head;
    while(j<i&&p!=NULL) {
        j++;
        p=p->next;
    }
    return p;
}
OneLinkDataType OneLink::get(int i)const {
    OneLinkNode *p=index(i);
    if(p!=NULL)
        return p->data;
    else
        return ' ';
}
bool OneLink::set(int i,OneLinkDataType n) {
    OneLinkNode *p=index(i);
    if(p==NULL) {
        int a=2;
        p=head;
        while(p->next!=NULL) {
            p=p->next;
            a++;
        }
        if(a==i) {
            p->next=new OneLinkNode(n);
            return true;
        }
        return false;
    } else {
        p->data=n;
        return true;
    }
    return false;
}
void OneLink::output(OneLinkNode *p)const {
    while(p!=NULL) {
        std::cout<<p->data<<" ";
        p=p->next;
    }
    std::cout<<std::endl;
}
void OneLink::output()const {
    output(head);
}

#ifndef SLINK_H_INCLUDED
#define SLINK_H_INCLUDED
int test();
class SLNode {
public:
    int data;
    SLNode* next;
    SLNode(int n=0);
};
class SLink {
public:
    SLNode* head;
    SLink();
    SLink(int n);
    SLink(int* array,int n);
    SLink(SLink &list);
    ~SLink();
    int length()const;
    bool isEmpty() const;
    bool isFull() const;
    bool isExist(int i) const;
    SLNode* index(int i) const;
//    int get(int i) const;
    bool set(int i,int n);
    SLNode* insertbefore(SLNode* p,int n);
    SLNode* insertafter(SLNode* p,int n);
    bool insertbefore(int i,int n);
    bool insertafter(int i,int n);
    bool removeNode(SLNode* p);
    bool removeNode(int i);
    bool removeData(int n);
    void reverse();
    void output() const;
    void output(SLNode *p) const;
    int sum();
    SLNode* searchdata(int n) const;
    SLink* AddLink(SLink a);
};


#endif


#include "../common.h"
/**
Find the mid node of linkedlist

Slow and fast pointers

If empty, NULL
If one or two element, first element

**/

namespace search_mid_node {
using namespace std;

typedef struct Node {
    int data;
    Node* next;
} Node;

Node * findMiddleNodeOfLinedList(Node *head)   {
    if(NULL == head || NULL == head->next)
        return head;
    Node *p1 = head;
    Node *p2 = head;
    while(NULL != p2->next && NULL != p2->next->next ) {
        p2 = p2->next->next;
        p1 = p1->next;
    }
    return p1;
}


Node* searchMidNode(Node* root) {
    if(root==NULL) return NULL;
//    if(root->next==NULL||root->next->next==NULL) return root;
    Node* slow=root;
    Node* fast=root->next;
    while(fast) {
//        printf("slow:%d,fast:%d\n",slow->data,fast->data);
        fast=fast->next;
        if(fast) {
            fast=fast->next;
            slow=slow->next;
        } else break;
    }
    return slow;
}



//C++ version
//return iterator of node
list<int>::iterator searchMidNode(list<int> *aList) {
    //Make sure at least one element
    if (aList->empty())
        return aList->end();

    list<int>::iterator slow=aList->begin();
    list<int>::iterator fast=aList->begin();

    while (fast!=aList->end()) {
        ++fast;
        if (fast!=aList->end()) {
            ++fast;
            ++slow;
        } else
            break;
    }
    return slow;

}
void testSearchMidList() {
    list<int> *aList=new list<int>;
    aList->push_back(0);
    aList->push_back(1);
    aList->push_back(2);
    aList->push_back(3);
    aList->push_back(4);
    aList->push_back(5);
    list<int>::iterator mid=searchMidNode(aList);
    printf("mid:%d\n",*mid);
    assert(*mid==3);


    int n=10;
    Node* midNode=NULL;
    Node* root=NULL;
    Node* pre=NULL;
    midNode=searchMidNode(root);
    assert(midNode==NULL);
    for(int i=0; i<n; ++i) {
        Node* newNode=(Node*)malloc(sizeof(Node));
        newNode->data=i;
        newNode->next=NULL;
        if(pre) {
            pre->next=newNode;
        } else {
            root=newNode;
        }
        pre=newNode;

        midNode=searchMidNode(root);
        printf("list size:%d, mid:%d\n",i+1,midNode->data);
        assert((i/2)==midNode->data);

        midNode=findMiddleNodeOfLinedList(root);
        printf("list size:%d, mid:%d\n",i+1,midNode->data);
        assert((i/2)==midNode->data);
    }

}
}

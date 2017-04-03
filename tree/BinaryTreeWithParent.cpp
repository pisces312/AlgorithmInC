/*
* Copyright (c) 2010,���ϴ�ѧ���ݿ������
* All rights reserved.
*
* �ļ����ƣ�
* ժ    Ҫ����Ҫ�������ļ�������
*
* ��ǰ�汾��1.0
* ��    �ߣ�����
* ������ڣ�2010��
*/
#include<stdio.h>
#include<stdlib.h>
#include "BinaryTreeWithParent.h"
#include<stack>
#include<string.h>
namespace BinaryTreeWithParent {
using namespace std;
void PrintString(const char* str,int len) {
    for(int i=0; i<len; ++i) {
        printf("%c",str[i]);
    }
    printf("\n");
}

    //�����������������ڵ�ĵ�һ������
    Node* BinaryTree::GetFirstAncestor(Node* n1, Node*n2) {
        if(n1==NULL||n2==NULL||n1==n2) return NULL;
        //
        Node* p=n1->parent;
        while(p){
            p->flag=true;
            p=p->parent;
        }
        p=n2->parent;
        while(p&&!p->flag){
            p=p->parent;
        }

        bool found=p&&p->flag;

        //////////////////////////////////
        //���ñ�ǣ��Ա��´�ʹ�ã���ʡ��
        Node* q=n1->parent;
        while(q){
            q->flag=false;
            q=q->parent;
        }
        //////////////////////////////////



        if(found){
            return p;
        }
        return NULL;
    }

    int BinaryTree::GetDepth(Node* p){
        if(p==NULL) return 0;
        int left=GetDepth(p->left);
        int right=GetDepth(p->right);
        return std::max(left,right)+1;
    }
    int BinaryTree::GetDepth(){
        return GetDepth(root);
    }
//BTreeNode* BTree::treeSearch2(BTreeNode *node,char ch) {
//    BTreeNode *p=node;
//    while(p!=NULL) {
//        if(ch==p->data)
//            return p;
//        if(ch<p->data)
//            return treeSearch2(p->left,ch);
//        else
//            return treeSearch2(p->right,ch);
//    }
//    return NULL;
//}
//BTreeNode* BTree::treeSearch(char ch) {
//    BTreeNode *p=root;
//    while(p!=NULL) {
//        if(ch==p->data)
//            return p;
//        if(ch<p->data)
//            p=p->left;
//        else
//            p=p->right;
//    }
//    cout<<"û���ҵ�"<<ch<<endl;
//    return NULL;
//}
//BTreeNode* BTree::treeInsert(char ch,BTreeNode *p) {
//    if(p==NULL)
//        p=new BTreeNode(ch);
//    else {
//        if(ch<=p->data)
//            p->left=treeInsert(ch,p->left);
//        else
//            p->right=treeInsert(ch,p->right);
//    }
//    return p;
//}
//void BTree::searchTreeCreate(char str[]) {
//    root=NULL;
//    int i=0;
//    while(str[i]!='\0') {
//        cout<<str[i]<<" ";
//        root=treeInsert(str[i],root);
//        i++;
//    }
//    cout<<endl;
//}
//
//
//
//
//bool BTree::isComplete() {
//    BTreeNode *p=root;
//    bool cm=true,b=true;
//    LQueue<BTreeNode*> q;
//    if(p!=NULL) {
//        q.enQueue(p);
//        while(!q.isEmpty()) {
//            p=q.deQueue();
//            if(p->left==NULL) {
//                if(p->right!=NULL)
//                    return false;
//                b=false;
//            } else {
//                cm=b;
//                q.enQueue(p->left);
//                if(p->right==NULL)
//                    b=false;
//                else
//                    q.enQueue(p->right);
//
//            }
//        }
//    }
//    return cm;
//}
//
//
//
//void BTree::swapStack(BTreeNode *p) {
//    LinkStack<BTreeNode*> s;
//    BTreeNode *t;
//    if(p!=NULL) {
//        s.push(p);
//        do {
//            p=s.pop();
//            if((p->left!=NULL)||(p->right!=NULL)) {
//                t=p->right;
//                p->right=p->left;
//                p->left=t;
//            }
//            if(p->left!=NULL)
//                s.push(p->left);
//            if(p->right!=NULL)
//                s.push(p->right);
//        } while(!s.isEmpty());
//    }
//}
//
//void BTree::inSwapCreate() {
//    BTreeNode *t=root;
//    root=inSwap(root);
//    destroyTree(t);
//}
//void BTree::preSwapCreate() {
//    BTreeNode *t=root;
//    root=preSwap(root);
//    destroyTree(t);
//}
//BTreeNode* BTree::inSwap(BTreeNode *b) {
//    BTreeNode *t,*t1,*t2;
//    if(b==NULL) t=NULL;
//    else {
//        t=new BTreeNode;
//        t1=inSwap(b->left);
//        t->data=b->data;
//        t2=inSwap(b->right);
//        t->left=t2;
//        t->right=t1;
//    }
//    return t;
//}
//BTreeNode* BTree::preSwap(BTreeNode *b) {
//    BTreeNode *t,*t1,*t2;
//    if(b==NULL) t=NULL;
//    else {
//        t=new BTreeNode;
//        t->data=b->data;
//        t1=preSwap(b->left);
//        t2=preSwap(b->right);
//        t->left=t2;
//        t->right=t1;
//    }
//    return t;
//}
//
//
//void BTree::printTree(BTreeNode *p,int n) {
//    if(p==NULL) return;
//    printTree(p->left,n+1);
//    for(int i=0; i<n-1; ++i)
//        cout<<"   ";
//    cout<<p->data<<endl;
//    printTree(p->right,n+1);
//}
//BTreeNode* BTree::layerCreate(dataType *str,int i) {
//    BTreeNode *p=NULL;
//    static int len=strlen(str);
//    if(i-1<len) {
//        p=new BTreeNode(str[i-1]);
//        p->left=layerCreate(str,2*i);
//        p->right=layerCreate(str,2*i+1);
//    }
//    return p;
//}
//
//BTree BTree::getLeftSub() {
//    BTreeNode *subTreePtr;
//    if(isEmpty()) return BTree();
//    copyTree(root->left,subTreePtr);
//    return BTree(subTreePtr);
//}
//BTree BTree::getRightSub() {
//    BTreeNode *subTreePtr;
//    if(isEmpty()) return BTree();
//    copyTree(root->right,subTreePtr);
//    return BTree(subTreePtr);
//}
//bool BTree::detachLeftSub(BTree &leftTree) {
//    if(isEmpty()) return false;
//    leftTree=BTree(root->left);
//    root->left=NULL;
//    return true;
//}
//bool BTree::detachRightSub(BTree &rightTree) {
//    if(isEmpty()) return false;
//    rightTree=BTree(root->right);
//    root->right=NULL;
//    return true;
//}
//BTree& BTree::operator=(const BTree &t) {
//    if(this!=&t) {				//�����������ͬ��ִ��
//        destroyTree(root);
//        copyTree(t.root,root);
//    }
//    return *this;
//}
//void BTree::copyTree(BTreeNode *p,BTreeNode *&newTreePtr) {
//    if(p!=NULL) {
//        newTreePtr=new BTreeNode(p->data);
//        copyTree(p->left,newTreePtr->left);
//        copyTree(p->right,newTreePtr->right);
//    } else newTreePtr=NULL;       //����
//}
//
//
//bool BTree::attachLeftSub(BTree &t) {
//    if(isEmpty()||root->left!=NULL) return false;
//    else {
//        root->left=t.root;
//        t.root=NULL;                   //  Ϊʲô�����??????
//    }
//    return true;
//}
//bool BTree::attachRightSub(BTree &t) {
//    if(isEmpty()||root->right!=NULL) return false;
//    else {
//        root->right=t.root;
//        t.root=NULL;
//    }
//    return true;
//}
//bool BTree::attachRight(const dataType str) {
//    if(isEmpty()||root->right!=NULL) return false;
//    else
//        root->right=new BTreeNode(str);
//    return true;
//}
//
//bool BTree::attachLeft(const dataType str) {
//    if(isEmpty()||root->left!=NULL) return false;
//    else
//        root->left=new BTreeNode(str);
//    return true;
//}
//bool BTree::isEmpty() {
//    return root==NULL;
//}
//void BTree::setRootData(const dataType str) {
//    if(!isEmpty())
//        root->data=str;
//    else
//        root=new BTreeNode(str);
//}
//

//void BTree::PrintTable2(BTreeNode *p) {
//    static n=0;
//    if(p==NULL) return;
//    else {
//        cout<<p->data;
//        if(p->left!=NULL||p->right!=NULL) {
//            cout<<'(';
//            if(p->left==NULL)
//                cout<<'#';
//            PrintTable2(p->left);
//            if(p->right!=NULL)
//                cout<<',';
//            else
//                cout<<",#";
//            PrintTable2(p->right);
//            cout<<')';
//            n++;
//        }
//    }
//    if(n==BTreeDepth(root)+1) {
//        n=0;
//        cout<<endl;
//    }
//}
//dataType* BTree::PrintTable(BTreeNode *p) {
//    static count=BTreeCount(root);
//    static dataType* str=new dataType[count*5];
//    static i=0,n=0;
//    int l=strlen(str);
//    if(i>=l) {
//        i=n=0;
//    }
//    if(p==NULL) return str;
//    else {
//        str[i++]=p->data;
//        n++;
//        if(p->left!=NULL||p->right!=NULL) {
//            str[i++]='(';
//            if(p->left==NULL)
//                str[i++]='#';
//            PrintTable(p->left);
//            if(p->right!=NULL)
//                str[i++]=',';
//            else {
//                str[i++]=',';
//                str[i++]='#';
//            }
//            PrintTable(p->right);
//            str[i++]=')';
//        }
//    }
//    if(n==BTreeCount())
//        str[i]='\0';
//    return str;
//}
//dataType BTree::MaxValue(BTreeNode *p) {
//    if(p==NULL) return '\0';
//    else {
//        dataType k1,k2;
//        k1=MaxValue(p->left);
//        k2=MaxValue(p->right);
//        k1=k1>k2?k1:k2;
//        return k1>p->data?k1:p->data;
//    }
//}
//int BTree::NodeLevel(BTreeNode *p,dataType str) {
//    if(p==NULL) return 0;
//    if(p->data==str) return 1;
//    else {
//        int c1=NodeLevel(p->left,str);
//        if(c1>=1) return c1+1;
//        int c2=NodeLevel(p->right,str);
//        if(c2>=1) return c2+1;
//        return 0;
//    }
//}
//bool BTree::FindNode(BTreeNode *p,dataType str) {
//    if(p==NULL) return false;
//    if(p->data==str) {
//        return true;
//    } else {
//        if(FindNode(p->left,str)) return true;
//        if(FindNode(p->right,str)) return true;
//        return false;
//    }
//}
//int BTree::CountNode(BTreeNode *p,dataType str) {
//    if(p==NULL) return 0;
//    if(p->data==str)
//        return CountNode(p->left,str)+CountNode(p->right,str)+1;
//    return CountNode(p->left,str)+CountNode(p->right,str);
//}
//int BTree::BTreeDepth(BTreeNode *p) {
//    if(p==NULL) return 0;
//    else {
//        int dep1=BTreeDepth(p->left);
//        int dep2=BTreeDepth(p->right);
//        if(dep1>dep2) return ++dep1;
//        else return ++dep2;
//    }
//}
//int BTree::BTreeDepth2(BTreeNode *p) {
//    int hp,tp,lc;
//    BTreeNode* que[max];
//    int h=0;
//    if(p!=NULL) {
//        hp=0;	//��ǰ�����Ľ��
//        tp=1;
//        lc=1;	//���ڵ�λ��Ϊ1
//        que[1]=p;	//���
//        do {
//            hp=(hp%max)+1;
//            p=que[hp];		//����
//            if(p->left!=NULL) {
//                tp=(tp%max)+1;
//                que[tp]=p->left; //���
//            }
//            if(p->right!=NULL) {
//                tp=(tp%max)+1;
//                que[tp]=p->right;	//���
//            }
//            if(hp==lc) {
//                h++;
//                lc=tp;	//��һ�����ұߵĽڵ��ڶ����е�λ��
//            }
//        } while(hp!=tp);
//    }
//    return h;
//}
//
//
//
//BTreeNode* BTree::tableCreate(dataType *str) {
//    BTreeNode *p=NULL;
//    static int i=0;
//    static int l=strlen(str);
//    if(i>=l) i=0;
//    if((str[i]>='A'&&str[i]<='Z')||(str[i]>='a'&&str[i]<='z')) {
//        p=new BTreeNode(str[i++]);
//        if(str[i]=='(') {
//            i++;
//            p->left=tableCreate(str);
//            i++;
//            p->right=tableCreate(str);
//            i++;
//        }
//    }
//    if(str[i]=='#'||str[i]=='.')
//        i++;
//    return p;
//}
//void BTree::Property(BTreeNode *p,int &n0,int &n2) {
//    if(root==NULL) {
//        n0=-1;
//        n2=-1;
//        return;
//    }
//    if(p!=NULL) {
//        if(p->left==NULL&&p->right==NULL)
//            n0++;
//        if(p->left!=NULL&&p->right!=NULL)
//            n2++;
//        Property(p->left,n0,n2);
//        Property(p->right,n0,n2);
//    }
//}
//int BTree::BTreeLeafCount(BTreeNode *p) {
//    if(p==NULL) p=root;
//    return root->BTreeLeafCount(p);
//}
//int BTree::BTreeCount(BTreeNode *p) {
//    if(p==NULL) p=root;
//    return root->BTreeCount(p);
//}
//void BTree::OutputLeaf(BTreeNode *p) {
//    if(p==NULL) p=root;
//    root->OutputLeaf(p);
//    cout<<endl;
//}
//
//
//void BTree::destroyTree(BTreeNode *p) {
//    if(p!=NULL) {
//        destroyTree(p->left);
//        destroyTree(p->right);
//        delete p;
//    }
//}
//
//


}

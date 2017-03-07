/*
* Copyright (c) 2010,东南大学数据库课题组
* All rights reserved.
*
* 文件名称：
* 摘    要：简要描述本文件的内容
*
* 当前版本：1.0
* 作    者：倪力
* 完成日期：2010年
*/
#include<stdio.h>
#include<stdlib.h>
#include "BinaryTree.h"
#include<stack>
#include<iostream>
using namespace std;
namespace CommonBinaryTree {

void PrintString(const char* str,int len) {
    for(int i=0; i<len; ++i) {
        printf("%c",str[i]);
    }
    printf("\n");
}
void BinaryTree::CreateFromPreAndIn(Node** root,const char* pre,const char* in,int treeLen) {
    if(treeLen==0) return ;
#ifdef TREE_DEBUG
    printf("pre:");
    PrintString(pre,treeLen);
    printf("in:");
    PrintString(in,treeLen);
    printf("len:%d\n\n",treeLen);
#endif

    *root=new Node(*pre);//根

    ++m_nodeNum;//计算节点数

    if(treeLen==1) { //先序到底
        return;
    }

    //在中序中找到根的位置
    const char* p=in;
    while(*p&&*p!=*pre) {
        ++p;
    }

    int leftLen=p-in;
    //left
    CreateFromPreAndIn(&(*root)->left,pre+1,in,leftLen);
    int rightLen=treeLen-leftLen-1;
    //right
    CreateFromPreAndIn(&(*root)->right,pre+1+leftLen,in+1+leftLen,rightLen);
}
Node* BinaryTree::CreateFromPreAndIn(const char* pre,const char* in) {
    if(pre==NULL||in==NULL) return NULL;
    int len=strlen(pre);
    CreateFromPreAndIn(&root,pre,in,len);
    return root;
}

void BinaryTree::InOrderTraverse(Node* p) {
    if(p==NULL) return;
    InOrderTraverse(p->left);
    printf("%c ",p->data);
    InOrderTraverse(p->right);
}
void BinaryTree::InOrderTraverse() {
    InOrderTraverse(root);
    printf("\n");
}

void BinaryTree::InOrderTraverseIter() {
    stack<Node*> s;
    Node*p=root;
    while(true) {
        while(p) {
            s.push(p);
            p=p->left;
        }
        if(!s.empty()) {
            p=s.top();
            s.pop();
            printf("%c ",p->data);
            p=p->right;
        } else {
            break;
        }
    }
    printf("\n");
}

void BinaryTree::InOrder2() {
    stack<Node*> stack;
    //p是遍历指针
    Node* p = root;
    //栈不空或者p不空时循环
    while(p || !stack.empty()) {
        if(p != NULL) {
            //存入栈中
            stack.push(p);
            //遍历左子树
            p = p->left;
        } else {
            //退栈，访问根节点
            p = stack.top();
            printf("%c ",p->data);
            stack.pop();
            //访问右子树
            p = p->right;
        }
    }//while
}


void BinaryTree::PostOrderTraverse(Node* p) {
    if(p==NULL) return;
    PostOrderTraverse(p->left);
    PostOrderTraverse(p->right);
    printf("%c ",p->data);


}
void BinaryTree::PostOrderTraverse() {
    PostOrderTraverse(root);
    printf("\n");
}
//非递归后序遍历
void BinaryTree::PostOrderTraverseIter() {
    stack<Node*> s;
    Node*p=root;
    while(p) {
        s.push(p);
        p=p->left;
    }
    while(!s.empty()) {
        p=s.top();
        if(p->flag) {
            s.pop();
            printf("%c ",p->data);
        } else {
            p->flag=true;
            p=p->right;
            while(p) {
                s.push(p);
                p=p->left;
            }
        }
    }
    printf("\n");
}
void BinaryTree::PostOrderTraverseIter3() {
    stack<Node*> s;
    Node*p=root;
    while(true) {
        if(p&&!p->flag)
            do {
                s.push(p);
                p=p->left;
            } while(p);
        while(!s.empty()) {
            p=s.top();
            if(p->flag) {
                s.pop();
                printf("%c ",p->data);
            } else {
                p->flag=true;
                p=p->right;
                break;
            }
        }
        if(s.empty()) break;
//        printf("%s,%s\n",p?"not null":"null",s.empty()?"empty":"not empty");
    }
    printf("\n");
}
void BinaryTree::PostOrderTraverseIter2() {
    stack<Node*> s;
    Node*p=root;
    while(true) {
        while(p) {
            p->flag=false;
            s.push(p);
            p=p->left;
        }
        if(!s.empty()) {
            p=s.top();
            if(p->flag) {
                s.pop();
                printf("%c ",p->data);
                p=NULL;
            } else {
                p->flag=true;
                p=p->right;
            }
        } else break;
    }
    printf("\n");

}


//后序遍历(非递归)
struct NodePost {
    Node* node;
    char tag;
};
void BinaryTree::PostOrder2() {
    stack<NodePost*> stack;
    //p是遍历指针
    Node* p = root;
    NodePost* BT;
    //栈不空或者p不空时循环
    while(p != NULL || !stack.empty()) {
        //遍历左子树
        while(p != NULL) {
            BT = (NodePost*)malloc(sizeof(NodePost));
            BT->node = p;
            //访问过左子树
            BT->tag = 'L';
            stack.push(BT);
            p = p->left;
        }
        //左右子树访问完毕访问根节点
        while(!stack.empty() && (stack.top())->tag == 'R') {
            BT = stack.top();
            //退栈
            stack.pop();
            printf("%c ",BT->node->data);
        }
        //遍历右子树
        if(!stack.empty()) {
            BT = stack.top();
            //访问过右子树
            BT->tag = 'R';
            p = BT->node;
            p = p->right;
        }
    }//while
}

Node** BinaryTree::ToArray(int& n) {
    Node** nodes=new Node*[m_nodeNum];
    int i=0;
    stack<Node*> s;
    Node*p=root;
    while(true) {
        while(p) {
            s.push(p);
            p=p->left;
        }
        if(!s.empty()) {
            p=s.top();
            s.pop();
            nodes[i++]=p;
            p=p->right;
        } else {
            break;
        }
    }
    n=m_nodeNum;
    return nodes;

}

void BinaryTree::preOrderStack() {
    stack<Node*> s;
    Node *p=root;
    if(p==NULL) return;
    cout<<"非递归先序遍历二叉树: ";
    while(p!=NULL||!s.empty()) {
        while(p!=NULL) {
            printf("%c ",p->data);
            s.push(p);
            p=p->left;
        }
        p=s.top();
        s.pop();
        p=p->right;
    }
    printf("\n");
}

void BinaryTree::preOrderStack2() {
    stack<Node*> s;
    Node *p=root;
    if(p==NULL) return;
    cout<<"非递归先序遍历二叉树: ";
    while(p!=NULL||!s.empty()) {
        if(p!=NULL) {
            printf("%c ",p->data);
            s.push(p);
            p=p->left;
        } else {
            p=s.top();
            s.pop();
            p=p->right;
        }
    }
    printf("\n");
}
//
//    Node* BinaryTree::CreateFromPreAndIn(const char* pre,const char* in){
//        if(pre==NULL||in==NULL) return NULL;
//
//        //stack<Node*> p;
//
//
//    }
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
//    cout<<"没有找到"<<ch<<endl;
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
//void BTree::inpostInitiate(dataType *poststr,dataType *instr) {
//    if(root!=NULL)
//        destroyTree();
//    root=inpostCreate(poststr,instr);
//}
//BTreeNode* BTree::inpostCreate(SSStr poststr,SSStr instr) {
//    BTreeNode *p=NULL;
//    int n=poststr.length();
//    if(n>0) {
//        char ch=poststr.GetChar(n);
//        int k=instr.IndexChar(ch);
//        if(k>0) {
//            p=new BTreeNode(ch);
//            SSStr postsub=poststr.GetSub(1,k-1);		//取左子树的后序串
//            SSStr insub=instr.GetSub(1,k-1);		//取左子树的中序串
//            p->left=inpostCreate(postsub,insub);		//建左子树
//
//            postsub=poststr.GetSub(k,n-k);
//            insub=instr.GetSub(k+1,n-k);
//            p->right=inpostCreate(postsub,insub);
//        }
//    }
//    return p;
//}

//
//void BTree::preinInitiate(dataType *str1,dataType *str2) {
//    if(root!=NULL)
//        destroyTree();
//    root=preinCreate(str1,str2);
//}
//BTreeNode* BTree::preinCreate(SSStr prestr,SSStr instr) {
//    BTreeNode *p=NULL;
//    int n=prestr.length();
//    if(n>0) {
//        char ch=prestr.GetChar(1);
//        int k=instr.IndexChar(ch);
//        if(k>0) {
//            p=new BTreeNode(ch);
//            SSStr presub=prestr.GetSub(2,k-1);		//取左子树的先序串
//            SSStr insub=instr.GetSub(1,k-1);		//取左子树的中序串
//            p->left=preinCreate(presub,insub);		//建左子树
//
//            presub=prestr.GetSub(k+1,n-k);
//            insub=instr.GetSub(k+1,n-k);
//            p->right=preinCreate(presub,insub);
//        }
//    }
//    return p;
//}
//
//void BTree::layerInitiate(dataType *str) {
//    if(root!=NULL)
//        destroyTree(root);
//    root=layerCreate(str);
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
//    if(this!=&t) {				//如果两个棵相同则不执行
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
//    } else newTreePtr=NULL;       //空树
//}
//
//
//bool BTree::attachLeftSub(BTree &t) {
//    if(isEmpty()||root->left!=NULL) return false;
//    else {
//        root->left=t.root;
//        t.root=NULL;                   //  为什么必须加??????
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
//void BTree::InOrderStack() {
//    cout<<"中序非递归遍厉二叉树: ";
//    BTreeNode *p=root;
//    LinkStack<BTreeNode*> s;
//    while(p!=NULL||!s.isEmpty()) {
//        if(p!=NULL) {
//            s.push(p);
//            p=p->left;
//        } else {
//            p=s.pop();
//            cout<<p->data<<" ";
//            p=p->right;
//        }
//    }
//    cout<<endl;
//}
//void BTree::LayerOrder(BTreeNode *p) {
//    cout<<"层次遍历二叉树: ";
//    LQueue<BTreeNode*> q;
//    q.enQueue(p);
//    while(!q.isEmpty()) {
//        p=q.deQueue();
//        cout<<p->data<<" ";
//        if(p->left!=NULL)
//            q.enQueue(p->left);
//        if(p->right!=NULL)
//            q.enQueue(p->right);
//    }
//    cout<<endl;
//}
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
//        hp=0;	//当前搜索的结点
//        tp=1;
//        lc=1;	//根节点位置为1
//        que[1]=p;	//入队
//        do {
//            hp=(hp%max)+1;
//            p=que[hp];		//出队
//            if(p->left!=NULL) {
//                tp=(tp%max)+1;
//                que[tp]=p->left; //入队
//            }
//            if(p->right!=NULL) {
//                tp=(tp%max)+1;
//                que[tp]=p->right;	//入队
//            }
//            if(hp==lc) {
//                h++;
//                lc=tp;	//下一层最右边的节点在队列中的位置
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
//void BTree::tableInitiate(dataType *str) {
//    destroyTree(root);
//    if(str!="")
//        root=tableCreate(str);
//}
//void BTree::preInitiate(dataType *str) {
//    destroyTree(root);
//    if(str!="")
//        root=preCreate(str);
//}
//BTreeNode *BTree::preCreate(dataType *str) {
//    BTreeNode *p=NULL;
//    static int i=0;
//    static int l=strlen(str);
//    if(i>=l) i=0;					//防止第二次调用时i不用0开始增加
//    if(str[i]!='.') {
//        p=new BTreeNode(str[i++]);
//        p->left=preCreate(str);
//        p->right=preCreate(str);
//    } else i++;
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
//BTree::BTree(dataType *str) {
//    root=NULL;						//?????
//    if(str!="")
//        root=preCreate(str);
//}
//BTree::BTree(BTreeNode *p) {
//    root=p;
//}
//BTree::BTree(const BTree &t) {
//    copyTree(t.root,root);
//}
//BTree::~BTree() {
//    destroyTree(root);
//    root=NULL;
//}
//void BTree::destroyTree(BTreeNode *p) {
//    if(p!=NULL) {
//        destroyTree(p->left);
//        destroyTree(p->right);
//        delete p;
//    }
//}
//
//
//void BTree::PreOrder(BTreeNode *p) {
//    if(p==NULL) p=root;
//    cout<<"先序遍历二叉树: ";
//    root->PreOrder(p);
//    cout<<endl;
//}
//void BTree::InOrder(BTreeNode *p) {
//    if(p==NULL) p=root;
//    cout<<"中序遍历二叉树: ";
//    root->InOrder(p);
//    cout<<endl;
//}
//void BTree::PostOrder(BTreeNode *p) {
//    if(p==NULL) p=root;
//    cout<<"后序遍历二叉树: ";
//    root->PostOrder(p);
//    cout<<endl;
//}


}

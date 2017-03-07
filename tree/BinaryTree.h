#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include "../common.h"

#define TREE_DEBUG
//一般的二叉树，无父母节点
namespace CommonBinaryTree {
    void test1();
void PrintString(const char* str,int len);
struct Node {
    //basic members
    Node* left;
    Node* right;
    int data;
    //
    //for post traverse
    bool flag;
    /////////////////////////////////

    Node(char d):left(NULL),right(NULL),data(d),flag(false) {
//        Reset();
    }
//    Node(int d):data(d) {
//        Reset();
//    }
//    void Reset() {
//        left=NULL;
//        right=NULL;
//        flag=false;
//    }
};
class BinaryTree {
    Node *root;
    int m_nodeNum;
    void CreateFromPreAndIn(Node** root,const char* pre,const char* in,int treeLen);
public:

    BinaryTree():root(NULL),m_nodeNum(0) {
    }

    ~BinaryTree() {

    }
    int GetTreeNodeNum(){
        return m_nodeNum;
    }
    /**
    **/
    //从前序和中序构造树
    Node* CreateFromPreAndIn(const char* pre,const char* in);



    //递归的中序遍历
    void InOrderTraverse(Node* p) ;
    void InOrderTraverse();
    //非递归中序遍历
    void InOrderTraverseIter();

    void PostOrderTraverse(Node* p) ;
    void PostOrderTraverse();
    //非递归后序遍历
    void PostOrderTraverseIter();
    void PostOrderTraverseIter2();
    void PostOrderTraverseIter3();
    Node** ToArray(int& n) ;

    Node* BuildCompleteTree(int n);

    void preOrderStack();
    void preOrderStack2();
    void InOrder2();
    void PostOrder2();

    //clear all nodes
    void Reset() {
    }

};



}


#endif // BINARYTREE_H_INCLUDED

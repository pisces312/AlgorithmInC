#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include "../common.h"

#define TREE_DEBUG
//һ��Ķ��������޸�ĸ�ڵ�
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
    //��ǰ�����������
    Node* CreateFromPreAndIn(const char* pre,const char* in);



    //�ݹ���������
    void InOrderTraverse(Node* p) ;
    void InOrderTraverse();
    //�ǵݹ��������
    void InOrderTraverseIter();

    void PostOrderTraverse(Node* p) ;
    void PostOrderTraverse();
    //�ǵݹ�������
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

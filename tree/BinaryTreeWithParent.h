#ifndef BINARYTREEWITHPARENT_H_INCLUDED
#define BINARYTREEWITHPARENT_H_INCLUDED


namespace BinaryTreeWithParent {
void PrintString(const char* str,int len);
struct Node {
    //basic members
    Node* left;
    Node* right;
    Node* parent;
    int data;
    //
    //for post traverse
    bool flag;




    Node(char d):left(NULL),right(NULL),parent(NULL),data(d),flag(false) {
//        Reset();
    }
    Node(int d):left(NULL),right(NULL),parent(NULL),data(d),flag(false) {
//        Reset();
    }
//    void Reset() {
//        left=NULL;
//        right=NULL;
//        flag=false;
//    }
    void Print(){
        printf("%c ",data);
    }
};
class BinaryTree {
    Node *root;
    int m_nodeNum;
    void CreateFromPreAndIn(Node* pr,Node** root,const char* pre,const char* in,int treeLen);
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

    Node** ToArray(int& n) ;
    //
    //�����������������ڵ�ĵ�һ������
    Node* GetFirstAncestor(Node* n1, Node*n2);

    //���
    //from 1
    int GetDepth(Node* p);
    int GetDepth();


    Node* BuildCompleteTree(int n);



    //clear all nodes
    void Reset() {
    }
    /////////////////////////////////////////////////////////////////

};



}

#endif // BINARYTREEWITHPARENT_H_INCLUDED

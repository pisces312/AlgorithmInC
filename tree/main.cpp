#include <iostream>
#include "BinaryTree.h"
#include "BinaryTreeWithParent.h"
using namespace std;
namespace BinaryTreeWithParent {
void PrintNodesArray(Node** nodes,int n) {
    for(int i=0; i<n; ++i) {
        printf("%c ",nodes[i]->data);
    }
    printf("\n");

}
void test1() {

//    const char* pre="abdce";
//    const char* in="dbaec";
    const char* pre="abdheicfgjk";
    const char* in="hdbeiafcgkj";
    int n;
    /**
    pre: h d b e i a f c g k j
    in:  h d b e i a f c g k j
    post:h d i e b f k j g c a
    **/
    BinaryTree b;
    //1
    b.CreateFromPreAndIn(pre,in);
    printf("node num=%d\n",b.GetTreeNodeNum());
    Node** nodes=b.ToArray(n);
    PrintNodesArray(nodes,n);
    //2
//    b.InOrderTraverse();
    //3
//    b.InOrderTraverseIter();
    //4
//    b.PostOrderTraverse();
    //5
//    b.PostOrderTraverseIter();
    //6
    //(i c)->a
    Node* p=b.GetFirstAncestor(nodes[4],nodes[7]);
    p->Print();
    printf("\n");
    //(h i)->b
    p=b.GetFirstAncestor(nodes[4],nodes[0]);
    p->Print();
    printf("\n");

    //7
    int depth=b.GetDepth();
    printf("tree depth=%d\n",depth);

}
void testGetFirstAncestor(){
    BinaryTree b;
//    const char* pre="abdce";
//    const char* in="dbaec";
    const char* pre="abdheicfgjk";
    const char* in="hdbeiafcgkj";
    /**
    pre: h d b e i a f c g k j
    in:  h d b e i a f c g k j
    post:h d i e b f k j g c a
    **/
    b.CreateFromPreAndIn(pre,in);
    int n;
    Node** nodes=b.ToArray(n);
    //i c:a
    Node* p=b.GetFirstAncestor(nodes[4],nodes[7]);
    p->Print();
    printf("\n");



}

}

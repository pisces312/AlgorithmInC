//#include "bitree_test.h"
#include "bitree.h"
#include "../common.h"



//    a(b,c)
//    b(d,e)
//    c(f,g)
//    d(h,)
//    e(,i)
//    f()
//    g(,j)
//    h()
//    i()
//    j(,k)
//    k()
//                     a
//             b                        c
//        d          e          f              g
//      h               i                          j
//                                                k
//
//    pre: h d b e i a f c g k j
//    in:  h d b e i a f c g k j
//    post:h d i e b f k j g c a
BiTNode* testTreeCreationByPreAndIn() {
    int pre[]= {'a','b','d','h','e','i','c','f','g','j','k'};
    int in[]= {'h','d','b','e','i','a','f','c','g','k','j'};
//    const char* pre="abdheicfgjk";
//    const char* in="hdbeiafcgkj";

    BiTNode* root=createByPreAndIn(pre,in,11);
    return root;

}

BiTNode* testTreeCreationByPostAndIn() {
    int post[]= {'h','d','i','e','b','f','k','j','g','c','a'};
    int in[]= {'h','d','b','e','i','a','f','c','g','k','j'};

    BiTNode* root=createByPostAndIn(post,in,11);
    preOrderTraverse(root);
    printf("\n");
    inOrderTraverse(root);
    printf("\n");
    postOrderTraverse(root);
    printf("\n");
    return root;

}



void testTreeTraverse() {
    BiTNode* root= testTreeCreationByPreAndIn();
    preOrderTraverse(root);
    printf("\n");
    inOrderTraverse(root);
    printf("\n");
    postOrderTraverse(root);
    printf("\n");
}

BiTNodeWithFlag* createByPreAndIn2(int* pre,int* in,int nodeCount) {
    if(nodeCount==0)
        return NULL;
    BiTNodeWithFlag *root=(BiTNodeWithFlag*)malloc(sizeof(BiTNodeWithFlag));
    root->data=pre[0];
    int i=0;
    while(pre[0]!=in[i])
        ++i;
    root->lchild=createByPreAndIn2(pre+1,in,i);
    root->rchild=createByPreAndIn2(pre+1+i,in+i+1,nodeCount-i-1);
    return root;
}

void testTreeTraverseStack() {
    BiTNode* root= testTreeCreationByPreAndIn();
    preOrderTraverseStack(root);
    printf("\n");
    preOrderTraverseStack2(root);
    printf("\n");
    preOrderTraverseStack3(root);
    printf("\n");
    preOrderTraverseStack4(root);
    printf("\n");
    inOrderTraverseStack(root);
    printf("\n");
    postOrderTraverseStack(root);
    printf("\n");
    postOrderTraverseStack2(root);
    printf("\n");

    int pre[]= {'a','b','d','h','e','i','c','f','g','j','k'};
    int in[]= {'h','d','b','e','i','a','f','c','g','k','j'};

    BiTNodeWithFlag* root2=createByPreAndIn2(pre,in,11);
    postOrderTraverseStackWithFlag1(root2);
    printf("\n");
    postOrderTraverseStackWithFlag2(root2);
    printf("\n");

}

void testTree() {
    testTreeTraverseStack();
//    testTreeTraverse();
//    testTreeCreationByPostAndIn();
//    testTreeCreationByPreAndIn();
}

#ifndef BITREE_H_INCLUDED
#define BITREE_H_INCLUDED
//17/3/31
typedef struct BiTNode {
    struct BiTNode *lchild, *rchild;
    int data;
} BiTNode;

typedef struct BiTNodeWithFlag{
    struct BiTNodeWithFlag *lchild, *rchild;
    int data;
    int flag;
} BiTNodeWithFlag;


typedef struct BiTNode *BiTree;

/////////////////////////////////
//Tree creation
BiTNode* createByPreAndIn(int* pre,int* in,int nodeCount);
BiTNode* createByPostAndIn(int* post,int* in,int nodeCount);
//!No pre and post

/////////////////////////////////
//Tree traverse recursive version
void preOrderTraverse(BiTNode* root);
void inOrderTraverse(BiTNode* root);
void postOrderTraverse(BiTNode* root);

//Tree traverse stack version
void preOrderTraverseStack(BiTNode* root);
void preOrderTraverseStack2(BiTNode* root);
void preOrderTraverseStack3(BiTNode* p);
void preOrderTraverseStack4(BiTNode* p);
void inOrderTraverseStack(BiTNode* p);
void postOrderTraverseStack(BiTNode* p);
void postOrderTraverseStack2(BiTNode* p);
void postOrderTraverseStackWithFlag1(BiTNodeWithFlag* p);
void postOrderTraverseStackWithFlag2(BiTNodeWithFlag* p);
void postOrderTraverseStackWithFlag3(BiTNodeWithFlag* p);

void layerTraverseByQueue(BiTNode* p);
void layerTraverse2(BiTNode* p);
void traverseOneLevel(BiTNode* root,int level);
int traverseOneLevel2(BiTNode* root,int level);
#endif // BITREE_H_INCLUDED

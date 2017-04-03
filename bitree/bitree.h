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

////////////////////////////////
//Layer traverse
//Top down and left to right
void layerTraverseByBFS(BiTNode* p);
void layerTraverseByOneQueue(BiTNode* p);
void layerTraverseByTwoQueue(BiTNode* p);
void layerTraverseRecursive(BiTNode* p);
int traverseOneLevel(BiTNode* root,int level);
void layerTraverseByArray(BiTNode* p);
//Top down and right to left
int traverseFromR2L(BiTNode* root,int level);
void layerTraverseByQueueR2L(BiTNode* p);
void layerTraverseByQueueR2L2(BiTNode* p);
//Bottom up and right to left
void layerTraBottomUpAndR2L(BiTNode* p);
void layerTraBottomUpAndR2L2(BiTNode* p);

//输出二叉树第 m 层的第 k 个节点值(m, k 均从 0 开始计数)
//Get kth nodes of level m (m,k starts from 0)
int getKthValueOfLevel(BiTNode* p,int m,int k);
int getKthValueOfLevel2(BiTNode* root,int m,int k);
#endif // BITREE_H_INCLUDED

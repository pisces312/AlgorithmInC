#include "bitree.h"
#include "../common.h"
//max stack size
#define MAXSIZE 100
//No validation for input
BiTNode* createByPreAndIn(int* pre,int* in,int nodeCount) {
//    printf("len:%d\n",nodeCount);
//Only handle node==0 case
//Also used to set NULL for leaf
    if(nodeCount==0)
        return NULL;

    BiTNode *root=(BiTNode*)malloc(sizeof(BiTNode));
    root->data=pre[0];

//    printf("data:%c\n",root->data);

    //Find current root pos in InOrderSeq
    int i=0;
    while(pre[0]!=in[i])
        ++i;

//    printf("leftLen:%d,rightLen:%d\n",i,nodeCount-i-1);

    root->lchild=createByPreAndIn(pre+1,in,i);
    root->rchild=createByPreAndIn(pre+1+i,in+i+1,nodeCount-i-1);
    return root;
}

BiTNode* createByPostAndIn(int* post,int* in,int nodeCount) {
    if(nodeCount==0)
        return NULL;

    BiTNode *root=(BiTNode*)malloc(sizeof(BiTNode));
    root->data=post[nodeCount-1];

    int i=0;
    while(post[nodeCount-1]!=in[i])  ++i;

    root->lchild=createByPostAndIn(post,in,i);
    root->rchild=createByPostAndIn(post+i,in+i+1,nodeCount-i-1);
    return root;
}


void preOrderTraverse(BiTNode* root) { //采用递归方式先序遍历二叉树BT
    if(root != NULL) {
        printf("%c ", root->data);//输出该结点（根结点）
        preOrderTraverse(root->lchild);  //遍历左子树
        preOrderTraverse(root->rchild);//遍历右子树
    }
}

void inOrderTraverse(BiTNode* root) { //采用递归方式中序遍历二叉树BT
    if(root != NULL) {
        inOrderTraverse(root->lchild);  //遍历左子树
        printf("%c ", root->data);//输出该结点（根结点）
        inOrderTraverse(root->rchild);//遍历右子树
    }
}

void postOrderTraverse(BiTNode* root) { //采用递归方式后序遍历二叉树BT
    if(root != NULL) {
        postOrderTraverse(root->lchild);  //遍历左子树
        postOrderTraverse(root->rchild);//遍历右子树
        printf("%c ", root->data);//输出该结点（根结点）
    }
}

//采用非递归方式先序遍历二叉树BT
void preOrderTraverseStack(BiTNode* p) {
    BiTNode* stack[MAXSIZE];//p表示当前结点，栈stack[]用来存储结点
    int top = -1; //栈空

    if(p == NULL)
        return;

//p!=NULL is for entering the loop in first time
//because top<0 at that time
    while(p || top >= 0) {
        if(p!=NULL) { //先输出结点数据，再遍历左孩子
            printf("%c ",p->data);//输出该结点
            ++top;
            stack[top] = p;
            p = p->lchild;
        } else {//访问栈顶元素右孩子，并退栈
            p = stack[top];
            --top;
            p= p->rchild;
        }
    }
}

void preOrderTraverseStack2(BiTNode* p) {
    if(p==NULL) return;

    BiTNode* stack[MAXSIZE];
    int top = 0;
    while(true) {
        if(p!=NULL) { //先输出结点数据，再遍历左孩子
            printf("%c ",p->data);//输出该结点
            stack[top] = p;
            ++top;
            p = p->lchild;
        } else {//访问栈顶元素右孩子，并退栈
            --top;
            //Only check stack when pop action
            if(top<0)
                break;
            p = stack[top];
            p= p->rchild;
        }
    }
}
//Using std::stack, same as version 1
void preOrderTraverseStack3(BiTNode* p) {
    std::stack<BiTNode*> s;
    while(p || !s.empty()) {
        if(p != NULL) {
            //访问根节点
            printf("%c ",p->data);
            //入栈
            s.push(p);
            //遍历左子树
            p = p->lchild;
        } else {
            //退栈
            p = s.top();
            s.pop();
            //遍历右子树
            p = p->rchild;
        }
    }
}

void preOrderTraverseStack4(BiTNode* p) {
    std::stack<BiTNode*> s;
    while(true) {
        //1. Visit root
        //2. Traverse left child
        while(p) {
            printf("%c ",p->data);
            s.push(p);
            p=p->lchild;
        }
        //3. Pop and traverse right child until stack is empty
        if(!s.empty()) { //check empty first, can avoid the root is NULL
            p=s.top();
            s.pop();
            p=p->rchild;
        } else {
            break;
        }
    }
}


//采用非递归方式中序遍历二叉树BT
void inOrderTraverseStack(BiTNode* p) {
    BiTNode* stack[MAXSIZE];//p表示当前结点，栈stack[]用来存储结点
    int top = -1; //栈空

    if(p == NULL)
        return;

//p!=NULL is for entering the loop in first time
//because top<0 at that time
    while(p || top >= 0) {
        if(p!=NULL) { //先输出结点数据，再遍历左孩子
            ++top;
            stack[top] = p;
            p = p->lchild;
        } else {//访问栈顶元素右孩子，并退栈
            p = stack[top];
            --top;
            printf("%c ",p->data);//输出该结点
            p= p->rchild;
        }
    }
}

//采用非递归方式后序遍历二叉树BT
void postOrderTraverseStack(BiTNode* p) {
    BiTNode* s[MAXSIZE];//p表示当前结点，栈stack[]用来存储结点
    int tag[MAXSIZE] = {0}; //用来标志栈顶元素的右孩子是否被访问过，0表示未访问，1表示已访问
    int top = -1; //栈空

    if(p == NULL)
        return;

    while(p || top >= 0) {
        if(p != NULL) { //首先访问左子树
            s[++top] = p;
            tag[top] = 0;
            p = p->lchild;
        } else if(tag[top] == 0) {
            //若右子树尚未访问，访问栈顶元素右孩子，并做好标记
            p=s[top];
            p=p->rchild;
            tag[top]= 1;
        } else {
            //否则输出栈顶元素并退栈
            //!Not change p's value here
            //Because left and right have visited,
            //current p must be NULL and it will be the next element
            //on the stack
            //!If use p=s[top], it has to set p to NULL back
            printf("%c ",s[top]->data);
            top--; //pop
        }
    }
}

//No need to check whether root is NULL for "while(true)"
void postOrderTraverseStack2(BiTNode* p) {
    BiTNode* s[MAXSIZE];
    int tag[MAXSIZE];
    int top = -1;
    while(true) {
        while(p) {
            s[++top] = p;
            tag[top] = 0;
            p = p->lchild;
        }
        if(top>=0) {
            if(tag[top] == 0) {
                p= s[top];
                p= p->rchild;
                tag[top]= 1;
            } else {
                printf("%c ",s[top]->data);
                top--;
            }
        } else
            break;
    }
}

//Avoid set p=NULL and push back
void postOrderTraverseStackWithFlag1(BiTNodeWithFlag* p) {
    std::stack<BiTNodeWithFlag*> s;
    while(true) {
        while(p) {
            p->flag=false;
            s.push(p);
            p=p->lchild;
        }
        if(!s.empty()) {
            if(s.top()->flag) {
                //!Not change p here
                //!Still use s.top()
                printf("%c ",s.top()->data);
                s.pop();
            } else {
                p=s.top();
                p->flag=true;
                p=p->rchild;
            }
        } else
            break;
    }
}

//Not recommended
void postOrderTraverseStackWithFlag2(BiTNodeWithFlag* p) {
    std::stack<BiTNodeWithFlag*> s;
    while(true) {
        while(p) {
            p->flag=false;
            s.push(p);
            p=p->lchild;
        }
        if(!s.empty()) {
            //After while, p must be NULL
            //! But p's value is changed unexpectedly here
            p=s.top();
            if(p->flag) {
                printf("%c ",p->data);
                s.pop();
                p=NULL;//! so have to restore it to original value(NULL)
            } else {
                p->flag=true;
                p=p->rchild;
            }
        } else
            break;
    }
}



//Pop and push back
//Not recommended
void postOrderTraverseStackWithFlag3(BiTNodeWithFlag* p) {
    std::stack<BiTNodeWithFlag*> s;
    while(true) {
        while(p) {
            p->flag=false;
            s.push(p);
            p=p->lchild;
        }
        if(!s.empty()) {
            //Pop, no matter the flag
            p=s.top();
            s.pop();
            if(p->flag) {
                printf("%c ",p->data);
                p=NULL; //Set back to NULL
            } else {
                p->flag=true;
                s.push(p); //Push back
                p=p->rchild;
            }
        } else
            break;
    }
}


//////////////////////////////////////////////
//
//Layer traverse
//
/////////////////////////////////////////////

////////////////////////////
//Top down and left to right
//!Use queue, not distinguish each level
void layerTraverseByBFS(BiTNode* p) {
    if(p==NULL)
        return;
    std::queue<BiTNode*> q;
    q.push(p);
    while(!q.empty()) {
        p=q.front();
        q.pop();
        printf("%c ",p->data);
        if(p->lchild) q.push(p->lchild);
        if(p->rchild) q.push(p->rchild);
    }
}


//root is on level 0
//recursive version
//void traverseOneLevel(BiTNode* root,int level) {
//    if(!root||level<0)
//        return;
//    if(level==0) {
//        printf("%c ",root->data);
//        return;
//    }
//    traverseOneLevel(root->lchild,level-1);
//    traverseOneLevel(root->rchild,level-1);
//}
//!
int traverseOneLevel(BiTNode* root,int level) {
    if(!root||level<0)
        return 0;
    if(level==0) {
        printf("%c ",root->data);
        return 1;
    }
    return traverseOneLevel(root->lchild,level-1)+
           traverseOneLevel(root->rchild,level-1);
}



//Have redundant traverse
void layerTraverseRecursive(BiTNode* p) {
    int level=0;
    while(traverseOneLevel(p,level)) {
        ++level;
        printf("\n");
    }
}

//Not know the number of tree, use vector
//similar as layerTraverseByArray2
//void layerTraverseByArray(BiTNode* p) {
//    if(p==NULL)
//        return;
//    std::vector<BiTNode*> arr;
//    arr.push_back(p);
//    //[first,last)
//    int cur=0;//index
//    int last=1;//index
//    int i=0;//backup previous "last"
//    while(cur<last) {
//        for(i=last; cur<last; ++cur) { //print by level
//            printf("%c ",arr[cur]->data);
//            if(arr[cur]->lchild) {
//                arr.push_back(arr[cur]->lchild);
//                ++i;
//            }
//            if(arr[cur]->rchild) {
//                arr.push_back(arr[cur]->rchild);
//                ++i;
//            }
//        }
//        last=i;
//        printf("\n");
////        printf("first:%d,last:%d\n",first,last);
//    }
//}
//!Use two indexes
//Drawback: use vector
void layerTraverseByArray(BiTNode* p) {
    if(p==NULL)
        return;
    std::vector<BiTNode*> vec;
    vec.push_back(p);
    int cur=0;
    while(cur<vec.size()) { //cur<totalSize
        //the next pos of last element
        //store the previous "vec.size()"
        //because vec will bi changed in the loop
        int last=vec.size();
        while(cur<last) {
            printf("%c ",vec[cur]->data);
            if(vec[cur]->lchild)
                vec.push_back(vec[cur]->lchild);
            if(vec[cur]->rchild)
                vec.push_back(vec[cur]->rchild);
            ++cur;
        }
        printf("\n");
    }
}

//!!Use two queues
void layerTraverseByTwoQueue(BiTNode* p) {
    if(p==NULL)
        return;
    std::deque<BiTNode*> q1,q2;//q1 for current level, q2 for next level
    q1.push_back(p);
    do {
        do {
            p=q1.front();
            q1.pop_front();
            printf("%c ",p->data);
            if(p->lchild)
                q2.push_back(p->lchild);
            if(p->rchild)
                q2.push_back(p->rchild);
        } while(!q1.empty());
        q1.swap(q2);//swap two queues
        printf("\n");
    } while(!q1.empty());
}

//!Better than layerTraverseByArray2,
//no need "vector" to store all nodes
//Can distinguish each level
void layerTraverseByOneQueue(BiTNode* p) {
    if(p==NULL)
        return;
    std::queue<BiTNode*> q;
    q.push(p);
    int len=1;//for each level
    int i=0; //for iterate current level
    int j=0; //remember current len
    while(len) { //if next level has nodes, can use "!q.empty()" instead
        //current level loop
        for(i=0,j=len,len=0; i<j; ++i) {//len is reset to 0 for next level
            p= q.front();
            q.pop();
            printf("%c ",p->data);
            if(p->lchild) {
                q.push(p->lchild);
                ++len;
            }
            if(p->rchild) {
                q.push(p->rchild);
                ++len;
            }
        }
        printf("\n");
    }
}


////////////////////////////
//Top down and right to left

int traverseFromR2L(BiTNode* root,int level) {
    if(!root||level<0)
        return 0;
    if(level==0) {
        printf("%c ",root->data);
        return 1;
    }
    return traverseFromR2L(root->rchild,level-1)+
           traverseFromR2L(root->lchild,level-1);
}

//swap the visit order for two children
//first right, then left
void layerTraverseByQueueR2L(BiTNode* p) {
    if(p==NULL)
        return;
    std::queue<BiTNode*> q;
    q.push(p);
    while(!q.empty()) {
        p=q.front();
        q.pop();
        printf("%c ",p->data);
        if(p->rchild) q.push(p->rchild);
        if(p->lchild) q.push(p->lchild);
    }
}

void layerTraverseByQueueR2L2(BiTNode* p) {
    if(p==NULL)
        return;
    std::queue<BiTNode*> q;
    q.push(p);
    int len=1;//for each level
    int i=0; //for iterate current level
    int j=0; //remember current len
    while(len) { //if next level has nodes, can use "!q.empty()" instead
        //current level loop
        for(i=0,j=len,len=0; i<j; ++i) {//len is reset to 0 for next level
            p= q.front();
            q.pop();
            printf("%c ",p->data);
            if(p->rchild) {
                q.push(p->rchild);
                ++len;
            }
            if(p->lchild) {
                q.push(p->lchild);
                ++len;
            }
        }
        printf("\n");
    }
}
////////////////////////////
//Bottom up and right to left
void layerTraBottomUpAndR2L(BiTNode* p) {
    if(p==NULL)
        return;
    std::vector<BiTNode*> vec;
    vec.push_back(p);
    int cur=0;
    int last=1;
    while(cur<vec.size()) {
        last=vec.size();
        while(cur<last) {
            if(vec[cur]->lchild)
                vec.push_back(vec[cur]->lchild);
            if(vec[cur]->rchild)
                vec.push_back(vec[cur]->rchild);
            ++cur;
        }
    }
    //Reserve output
    for(cur=vec.size()-1; cur>=0; --cur)
        printf("%c ",vec[cur]->data);
}


void layerTraBottomUpAndR2L2(BiTNode* p) {
    if(p==NULL)
        return;
    std::vector<BiTNode*> vec;
    vec.push_back(p);
    std::stack<int> level;
    level.push(0);
    int cur=0;
    int last=1;
    while(cur<vec.size()) {
        last=vec.size();
        level.push(last);//save last of current level
        while(cur<last) {
            if(vec[cur]->lchild)
                vec.push_back(vec[cur]->lchild);
            if(vec[cur]->rchild)
                vec.push_back(vec[cur]->rchild);
            ++cur;
        }
    }
    //Reserve output
    int preLast=vec.size();
    while(!level.empty()) {
        last=level.top();
        level.pop();
        for(cur=preLast-1; cur>=last; --cur)
            printf("%c ",vec[cur]->data);
        preLast=last;
        printf("\n");
    }
}
//////////////////////////////////////
//k>=0,m>=0
BiTNode* getKthValueOfLevelCore(BiTNode* root,int m,int k,int*c) {
    if(!root||m<0)
        return NULL;
    if(m==0) {
        if(*c==k)
            return root;
        ++(*c);
        return NULL;
    }
    BiTNode* node=getKthValueOfLevelCore(root->lchild,m-1,k,c);
    if(node)
        return node;
    return getKthValueOfLevelCore(root->rchild,m-1,k,c);
}

int getKthValueOfLevel(BiTNode* root,int m,int k) {
    int c=0;
    BiTNode* node= getKthValueOfLevelCore(root,m,k,&c);
    if(node)
        return node->data;
    return 0;
}


int getKthValueOfLevel2(BiTNode* p,int m,int k)  {
    if(p==NULL)
        return 0;
    std::queue<BiTNode*> q;
    q.push(p);
    int level=0;
    int len=1;//for each level
    int i=0; //for iterate current level
    int j=0; //remember current len
    while(len) { //if next level has nodes, can use "!q.empty()" instead
        //current level loop
        for(i=0,j=len,len=0; i<j; ++i) {//len is reset to 0 for next level
            p= q.front();
            q.pop();

            if(level==m&&i==k)
                return p->data;

            if(p->lchild) {
                q.push(p->lchild);
                ++len;
            }
            if(p->rchild) {
                q.push(p->rchild);
                ++len;
            }
        }
        ++level;
    }
}

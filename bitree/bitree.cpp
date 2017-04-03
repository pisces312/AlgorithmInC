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


void preOrderTraverse(BiTNode* root) { //���õݹ鷽ʽ�������������BT
    if(root != NULL) {
        printf("%c ", root->data);//����ý�㣨����㣩
        preOrderTraverse(root->lchild);  //����������
        preOrderTraverse(root->rchild);//����������
    }
}

void inOrderTraverse(BiTNode* root) { //���õݹ鷽ʽ�������������BT
    if(root != NULL) {
        inOrderTraverse(root->lchild);  //����������
        printf("%c ", root->data);//����ý�㣨����㣩
        inOrderTraverse(root->rchild);//����������
    }
}

void postOrderTraverse(BiTNode* root) { //���õݹ鷽ʽ�������������BT
    if(root != NULL) {
        postOrderTraverse(root->lchild);  //����������
        postOrderTraverse(root->rchild);//����������
        printf("%c ", root->data);//����ý�㣨����㣩
    }
}

//���÷ǵݹ鷽ʽ�������������BT
void preOrderTraverseStack(BiTNode* p) {
    BiTNode* stack[MAXSIZE];//p��ʾ��ǰ��㣬ջstack[]�����洢���
    int top = -1; //ջ��

    if(p == NULL)
        return;

//p!=NULL is for entering the loop in first time
//because top<0 at that time
    while(p || top >= 0) {
        if(p!=NULL) { //�����������ݣ��ٱ�������
            printf("%c ",p->data);//����ý��
            ++top;
            stack[top] = p;
            p = p->lchild;
        } else {//����ջ��Ԫ���Һ��ӣ�����ջ
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
        if(p!=NULL) { //�����������ݣ��ٱ�������
            printf("%c ",p->data);//����ý��
            stack[top] = p;
            ++top;
            p = p->lchild;
        } else {//����ջ��Ԫ���Һ��ӣ�����ջ
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
            //���ʸ��ڵ�
            printf("%c ",p->data);
            //��ջ
            s.push(p);
            //����������
            p = p->lchild;
        } else {
            //��ջ
            p = s.top();
            s.pop();
            //����������
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


//���÷ǵݹ鷽ʽ�������������BT
void inOrderTraverseStack(BiTNode* p) {
    BiTNode* stack[MAXSIZE];//p��ʾ��ǰ��㣬ջstack[]�����洢���
    int top = -1; //ջ��

    if(p == NULL)
        return;

//p!=NULL is for entering the loop in first time
//because top<0 at that time
    while(p || top >= 0) {
        if(p!=NULL) { //�����������ݣ��ٱ�������
            ++top;
            stack[top] = p;
            p = p->lchild;
        } else {//����ջ��Ԫ���Һ��ӣ�����ջ
            p = stack[top];
            --top;
            printf("%c ",p->data);//����ý��
            p= p->rchild;
        }
    }
}

//���÷ǵݹ鷽ʽ�������������BT
void postOrderTraverseStack(BiTNode* p) {
    BiTNode* s[MAXSIZE];//p��ʾ��ǰ��㣬ջstack[]�����洢���
    int tag[MAXSIZE] = {0}; //������־ջ��Ԫ�ص��Һ����Ƿ񱻷��ʹ���0��ʾδ���ʣ�1��ʾ�ѷ���
    int top = -1; //ջ��

    if(p == NULL)
        return;

    while(p || top >= 0) {
        if(p != NULL) { //���ȷ���������
            s[++top] = p;
            tag[top] = 0;
            p = p->lchild;
        } else if(tag[top] == 0) {
            //����������δ���ʣ�����ջ��Ԫ���Һ��ӣ������ñ��
            p=s[top];
            p=p->rchild;
            tag[top]= 1;
        } else {
            //�������ջ��Ԫ�ز���ջ
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
//!queue version
void layerTraverseByQueue(BiTNode* p) {
    std::queue<BiTNode*> q;
    if(p==NULL) return;
    q.push(p);
    while(!q.empty()) {
        BiTNode* p=q.front();
        q.pop();
        printf("%c ",p->data);
        if(p->lchild) q.push(p->lchild);
        if(p->rchild) q.push(p->rchild);
    }
}

//root is on level 0
//recursive version
void traverseOneLevel(BiTNode* root,int level) {
    if(!root||level<0)
        return;
    if(level==0) {
        printf("%c ",root->data);
        return;
    }
    traverseOneLevel(root->lchild,level-1);
    traverseOneLevel(root->rchild,level-1);
}

int traverseOneLevel2(BiTNode* root,int level) {
    if(!root||level<0)
        return 0;
    if(level==0) {
        printf("%c ",root->data);
        return 1;
    }
    return traverseOneLevel2(root->lchild,level-1)+
           traverseOneLevel2(root->rchild,level-1);
}
//Have redundant traverse
void layerTraverse2(BiTNode* p) {
    int level=0;
    while(traverseOneLevel2(p,level)) ++level;
}

//!TODO not know number
//void layerTraverseByArray(BiTNode* p) {
//    std::vector<BiTNode*> arr;
//
//    if(p==NULL) return;
//
//    BiTNode*
//    q.push(p);
//
//    while(!q.empty()) {
//        BiTNode* p=q.front();
//        q.pop();
//        printf("%c ",p->data);
//        if(p->lchild) q.push(p->lchild);
//        if(p->rchild) q.push(p->rchild);
//    }
//}

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "common.h"
//typedef int elemType ;

/************************************************************************/
/*             �����ǹ������Ա����Ӵ洢��������������18���㷨        */

/* 1.��ʼ�����Ա����õ�����ı�ͷָ��Ϊ�� */
/* 2.�������Ա��˺������븺����ֹ��ȡ����*/
/* 3.��ӡ��������ı���*/
/* 4.������Ա�L�е�����Ԫ�أ����ͷŵ�����L�����еĽ�㣬ʹ֮��Ϊһ���ձ� */
/* 5.���ص�����ĳ��� */
/* 6.��鵥�����Ƿ�Ϊ�գ���Ϊ���򷵻أ������򷵻أ� */
/* 7.���ص������е�pos������е�Ԫ�أ���pos������Χ����ֹͣ�������� */
/* 8.�ӵ������в��Ҿ��и���ֵx�ĵ�һ��Ԫ�أ������ҳɹ��򷵻ظý��data��Ĵ洢��ַ�����򷵻�NULL */
/* 9.�ѵ������е�pos������ֵ�޸�Ϊx��ֵ�����޸ĳɹ����أ������򷵻أ� */
/* 10.������ı�ͷ����һ��Ԫ�� */
/* 11.�������ĩβ���һ��Ԫ�� */
/* 12.�������е�pos�����λ�ò���Ԫ��Ϊx�Ľ�㣬������ɹ����أ������򷵻أ� */
/* 13.�����������в���Ԫ��x��㣬ʹ�ò������Ȼ���� */
/* 14.�ӵ�������ɾ����ͷ��㣬���Ѹý���ֵ���أ���ɾ��ʧ����ֹͣ�������� */
/* 15.�ӵ�������ɾ����β��㲢��������ֵ����ɾ��ʧ����ֹͣ�������� */
/* 16.�ӵ�������ɾ����pos����㲢��������ֵ����ɾ��ʧ����ֹͣ�������� */
/* 17.�ӵ�������ɾ��ֵΪx�ĵ�һ����㣬��ɾ���ɹ��򷵻�1,���򷵻�0 */
/* 18.����2��Ԫ�ص�λ�� */
/* 19.�����Ա���п������� */
/************************************************************************/
typedef struct Node {   /* ���嵥���������� */
    int element;
    Node *next;
} Node;


/* 1.��ʼ�����Ա����õ�����ı�ͷָ��Ϊ�� */
void initList(Node **pNode) {
    *pNode = NULL;
    printf("initList����ִ�У���ʼ���ɹ�\n");
}

/* 2.�������Ա��˺������븺����ֹ��ȡ����*/
//Node *creatList(Node *pHead) {
//    Node *p1;
//    Node *p2;
//
//    p1=p2=(Node *)malloc(sizeof(Node)); //�����½ڵ�
//    if(p1 == NULL || p2 ==NULL) {
//        printf("�ڴ����ʧ��\n");
//        exit(0);
//    }
//    memset(p1,0,sizeof(Node));
//
//    scanf("Input an element: %d",&p1->element);    //�����½ڵ�
//    p1->next = NULL;         //�½ڵ��ָ����Ϊ��
//    while(p1->element > 0) {      //�����ֵ����0�������ֱ�������ֵΪ��
//        if(pHead == NULL) {     //�ձ������ͷ
//            pHead = p1;
//        } else {
//            p2->next = p1;       //�ǿձ������β
//        }
//        p2 = p1;
//        p1=(Node *)malloc(sizeof(Node));    //��������һ���ڵ�
//        if(p1 == NULL || p2 ==NULL) {
//            printf("�ڴ����ʧ��\n");
//            exit(0);
//        }
//        memset(p1,0,sizeof(Node));
//        scanf("%d",&p1->element);
//        p1->next = NULL;
//    }
//    printf("creatList����ִ�У��������ɹ�\n");
//    return pHead;           //���������ͷָ��
//}

/* 3.��ӡ��������ı���*/
void printList(Node *pHead) {
    if(NULL == pHead) { //����Ϊ��
        printf("PrintList����ִ�У�����Ϊ��\n");
    } else {
        while(NULL != pHead) {
            printf("%d ",pHead->element);
            pHead = pHead->next;
        }
        printf("\n");
    }
}

/* 4.������Ա�L�е�����Ԫ�أ����ͷŵ�����L�����еĽ�㣬ʹ֮��Ϊһ���ձ� */
void clearList(Node *pHead) {
    Node *pNext;            //����һ����pHead���ڽڵ�

    if(pHead == NULL) {
        printf("clearList����ִ�У�����Ϊ��\n");
        return;
    }
    while(pHead->next != NULL) {
        pNext = pHead->next;//������һ����ָ��
        free(pHead);
        pHead = pNext;      //��ͷ����
    }
    printf("clearList����ִ�У������Ѿ����\n");
}

/* 5.���ص�����ĳ��� */
int sizeList(Node *pHead) {
    int size = 0;
    while(pHead != NULL) {
        size++;         //��������size��С�������ʵ�ʳ���С1
        pHead = pHead->next;
    }
    printf("sizeList����ִ�У������� %d \n",size);
    return size;    //�����ʵ�ʳ���
}

/* 6.��鵥�����Ƿ�Ϊ�գ���Ϊ���򷵻أ������򷵻أ� */
int isEmptyList(Node *pHead) {
    if(pHead == NULL) {
        printf("isEmptyList����ִ�У�����Ϊ��\n");
        return 1;
    }
    printf("isEmptyList����ִ�У�����ǿ�\n");
    return 0;
}

Node* getNode(Node *pHead, int pos) {
    int i=0;
    if(pos < 1)
        return NULL;
    if(pHead == NULL)
        return NULL;
    while(pHead !=NULL) {
        if(++i == pos)
            break;
        pHead = pHead->next; //�Ƶ���һ���
    }
    if(i < pos)
        return NULL;
    return pHead;
}

/* 7.���ص������е�pos������е�Ԫ�أ���pos������Χ����ֹͣ�������� */
int getElement(Node *pHead, int pos) {
    Node* node=getNode(pHead,pos);
    if(node) return node->element;
    return 0;
}

/* 9.�ѵ������е�pos������ֵ�޸�Ϊx��ֵ�����޸ĳɹ����أ������򷵻أ� */
int modifyElem(Node *pNode,int pos,int x) {
    Node *node=getNode(pNode,pos);
    if(node){
        node->element=x;
        return 0;
    }
    return 1;
}

/* 10.������ı�ͷ����һ��Ԫ�� */
int insertHeadList(Node **pNode,int insertElem) {
    Node *pInsert = (Node *)calloc(1,sizeof(Node));
    pInsert->element = insertElem;
    pInsert->next = *pNode;
    *pNode = pInsert;
//    printf("insertHeadList����ִ�У����ͷ����Ԫ�سɹ�\n");
    return 0;
}

/* 11.�������ĩβ���һ��Ԫ�� */
int insertLastList(Node **pNode,int insertElem) {
    Node *pInsert;
    Node *pTmp; //����һ����ʱ����������ŵ�һ���ڵ�

    pInsert = (Node *)calloc(1,sizeof(Node)); //����һ���½ڵ�
    pInsert->element = insertElem;

    if(*pNode==NULL) {
        *pNode=pInsert;
    } else {
        pTmp = *pNode;
        while(pTmp->next != NULL)
            pTmp = pTmp->next;
        pTmp->next = pInsert;   //������ĩβ�ڵ����һ���ָ������ӵĽڵ�
    }

//    printf("insertLastList����ִ�У����β����Ԫ�سɹ�\n");

    return 0;
}

/******************************************************************/
void testList() {
    Node *pList=NULL;
//    int length = 0;
    int i;

    int posElem;

    initList(&pList);       //�����ʼ��
    printList(pList);       //����������ӡ����

//    insertHeadList(&pList,5);   //��ͷ����Ԫ��12
//    printList(pList);

//    insertLastList(&pList,10);  //��β����Ԫ��10
//    printList(pList);



//    pList=creatList(pList); //��������
//    printList(pList);



    for(i=1; i<=10; ++i)
        insertLastList(&pList,i);  //��β����Ԫ��10


    sizeList(pList);        //����ĳ���
    printList(pList);

    isEmptyList(pList);     //�ж������Ƿ�Ϊ������

    posElem = getElement(pList,3);  //��ȡ������Ԫ�أ����Ԫ�ز���3�����򷵻�0
    printf("getElement����ִ�У�λ�� 3 �е�Ԫ��Ϊ %d\n",posElem);
    printList(pList);

//    getElemAddr(pList,5);   //���Ԫ��5�ĵ�ַ

    modifyElem(pList,4,1);  //��������λ��4�ϵ�Ԫ���޸�Ϊ1
    printList(pList);

    insertHeadList(&pList,5);   //��ͷ����Ԫ��12
    printList(pList);

    insertLastList(&pList,10);  //��β����Ԫ��10
    printList(pList);

    clearList(pList);       //�������

}


#endif // LIST_H_INCLUDED

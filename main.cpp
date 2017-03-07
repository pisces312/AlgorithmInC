#include "common.h"
//#include"LinearList/LinearList.h"
//#include"LinkedList/��ͷ�����ĵ�����/SLink.h"
#include "prime.h"
#include "Search/search.h"
#include "graph/graph.h"
#include "tree/BinaryTree.h"
#include "sort/sort.h"
#include "list.h"
//using namespace std;

////////////////////////////////////////////////////////////
/**
쳲���������
0,1,2,3,4,5,6, 7, 8, 9,10
0,1,1,2,3,5,8,13,21,34,55
f(0)=0,f(1)=1
**/
long fibonacci(long n) {
    if(n<0) {
        return -1;
    }
    if(n==0) {
        return 0;
    }
    if(n==1) {
        return 1;
    }
    return fibonacci(n-1)+fibonacci(n-2);
}

long fibonacci2(long n) {
    int pre=0,pre2=1,s=0;
    if(n<0) {
        return -1;
    }
    if(n==0) {
        return 0;
    }
    if(n==1) {
        return 1;
    }
    for(int i=2; i<=n; ++i) {
        s=pre+pre2;
        pre=pre2;
        pre2=s;
    }
    return s;
}

void testFibonacci() {
    printf("%ld\n",fibonacci2(-1));
    printf("%ld\n",fibonacci2(0));
    printf("%ld\n",fibonacci2(1));
    printf("%ld\n",fibonacci2(2));
    printf("%ld\n",fibonacci2(10));

    printf("%ld\n",fibonacci(-1));
    printf("%ld\n",fibonacci(0));
    printf("%ld\n",fibonacci(1));
    printf("%ld\n",fibonacci(2));
    printf("%ld\n",fibonacci(10));
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
//ȫ����
void permutation(char *s, int start, int end) {
    if (start == end) {
        printf("%s\n", s);
        return;
    }
    for (int i = start; i < end; i++) {
        std::swap(s[start],s[i]);
        permutation(s, start + 1, end);
        std::swap(s[start],s[i]);
    }
}
void testPermutation() {
    char a[]="abcd";


    permutation(a, 0, strlen(a));
}
////////////////////////////////////////////////////////////
/**
 * if has loop return 1 else return 0
 */
int hasLoop(Node *node) {
    Node *pFast=node;
    Node *pSlow=node;
    if (pFast == NULL || pFast->next == NULL)
        return 0;
    do {
        pFast = pFast->next->next;
        pSlow = pSlow->next;
//        if(pFast != NULL) {
//            printf("fast=%d ",pFast->element);
//        }
//        if(pSlow != NULL) {
//            printf("slow=%d",pSlow->element);
//        }
//        printf("\n");
    } while (pFast != pSlow &&pFast != NULL && pFast->next != NULL ) ;
    return (pFast == pSlow);
}

void testLoop() {

    Node *pList=NULL;
    int length = 0;
    int i;

    int posElem;

    initList(&pList);       //������ʼ��
    printList(pList);       //������������ӡ����

//    insertHeadList(&pList,5);   //��ͷ����Ԫ��12
//    printList(pList);

//    insertLastList(&pList,10);  //��β����Ԫ��10
//    printList(pList);



//    pList=creatList(pList); //��������
//    printList(pList);



    for(i=1; i<=10; ++i)
        insertLastList(&pList,i);  //��β����Ԫ��10


    sizeList(pList);        //�����ĳ���
    printList(pList);

    Node* n10=getNode(pList,10);
    Node* n6=getNode(pList,6);
    n10->next=n6;

//    int e1=getElement(pList,1);
//    printf("%d\n",e1);

    int flag=hasLoop(pList);
    printf("%d\n",flag);


}
////////////////////////////////////////////////////////////

//void test2() {
//    int a[]= {2,1,6,9,5,8,7};
//    int n=sizeof(a)/sizeof(int);
////    int m=partition(a,0,n-1);
////    printf("%d\n",m);
//    quickSortNonRecursive(a,n);
//    printArray(a,n);
//}
//////////////////////////////////////////////////////////////////////
void hanoi(int n,char A,char B,char C) {
    if(n==1) {
        printf("Move disk %d from %c to %c\n",n,A,C);
    } else {
        hanoi(n-1,A,C,B);
        printf("Move disk %d from %c to %c\n",n,A,C);
        hanoi(n-1,B,A,C);
    }
}

void hanoi2(int n,char a,char b,char c) {
    static int step=0;
    //һ�����ӵ�������ֱ�Ӵ�a��cһ������
    if(n==1) printf("Step %d: Move disk %d from %c to %c\n",++step,n,a,c);
    else {
        hanoi2(n-1,a,c,b);
        hanoi2(1,a,b,c);
        hanoi2(n-1,b,a,c);
    }
}


int main() {
 //   Cutedge::testCutedge();
//    Cutpoint2::testCutpoint();
//    Cutpoint::testCutpoint();
//    testList();
//    testLoop();


//
//    typedef struct Node {
//        struct Node* next;
//        int data;
//    } Node;
//List list;
//    Node* list=(Node*)malloc(sizeof(Node));




//typedef struct ListNode{
//    struct ListNode* next;
//    int data;
//}*List;
////List list;
//List list=(List)malloc(sizeof(struct ListNode));
//struct List* list=(struct List*)malloc(sizeof(struct List));

//List* list=new List;




//    LinkedList::testLoop();


//    hanoi2(3,'a','b','c');
//    hanoi('a','b','c',3);
   testSortMain();
//    mstByPrim();
//    test2();
//    mstByKruskal();
//testSortMain();
//    UnionFind::testUnionFind();
//    testHeapSort();
//    createHeap1();
//    createHeap2();
//CommonBinaryTree::test1();

//testPrime();
//    shortestPathByBellmanFoardCheckingNegativeCircle() ;
//        shortestPathByBellmanFoard();
//    shortestPathByDijkstra();

//    shortestPathByBellmanFoardUsingQueue();

//    shortestPathByDijkstraLinkedGraph();
//    testLinkGraph();

//    shortestPathByFloydWarshall();
//    ShortestPathByDFS::shortestPathByDFS();
//    bfsGraph();
//    dfsGraph();
//    mazebyBFS();
//    mazebyDFS();
//    permutationByDFS();
//    testFibonacci();

//    LinearList::test();
//    LinkedList::WithHeadNode::test();
    return 0;
}

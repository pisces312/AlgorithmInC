#include "common.h"
//#include"LinearList/LinearList.h"
#include "quiz/prime.h"
#include "search/search.h"
#include "graph/graph.h"
#include "tree/BinaryTree.h"
#include "sort/sort.h"
#include "list.h"
#include "linked_list/Singly/OneLink.h"


int factorial(int n) {
    if(n==1) return 1;
    return factorial(n-1)*n;
}


////////////////////////////////////////////////////////////

void permutation(char *s, int start, int end) {
    if(start == end) {
        printf("%s\n", s);
        return;
    }
    for(int i = start; i < end; i++) {
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
    if(pFast == NULL || pFast->next == NULL)
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
    } while(pFast != pSlow &&pFast != NULL && pFast->next != NULL) ;
    return (pFast == pSlow);
}

void testLoop() {

    Node *pList=NULL;
//    int length = 0;
    int i;

//    int posElem;

    initList(&pList);
    printList(pList);

//    insertHeadList(&pList,5);
//    printList(pList);

//    insertLastList(&pList,10);
//    printList(pList);



//    pList=creatList(pList);
//    printList(pList);



    for(i=1; i<=10; ++i)
        insertLastList(&pList,i);


    sizeList(pList);
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
    if(n==1) printf("Step %d: Move disk %d from %c to %c\n",++step,n,a,c);
    else {
        hanoi2(n-1,a,c,b);
        hanoi2(1,a,b,c);
        hanoi2(n-1,b,a,c);
    }
}

int testOneLink() {
    OneLink link1(8);
    link1.set(2,'9');
    link1.output();
    return 0;
}



extern void testTree();
extern void testMaxContinuousSeqSum();
extern void testBitCount();
extern void testGCD();
extern void testLCM();
extern void testStringAlg();

namespace simplegraph{
extern void testDFSGraph();
}
namespace graphmatrix{
extern void testDFS();
extern void testPrim();
extern void testDijkstra();
}
extern void testKMax();
namespace UnionFind{
extern void testUnionFind();
}
int main() {

UnionFind::testUnionFind();

    testKMax();

graphmatrix::testDijkstra();
graphmatrix::testPrim();
    graphmatrix::testDFS();
simplegraph::testDFSGraph();
//    test2DArray();
//    testStringAlg();
//    testLCM();
//    testGCD();
//testBitCount();
//testMaxContinuousSeqSum();
//    testTree();
//    testSortMain();


//    testOneLink();
//   Cutedge::testCutedge();
//    Cutpoint2::testCutpoint();
//    Cutpoint::testCutpoint();
//    testList();
//    testLoop();

//    LinkedList::testLoop();


//    hanoi2(3,'a','b','c');
//    hanoi('a','b','c',3);

testSortMain();
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

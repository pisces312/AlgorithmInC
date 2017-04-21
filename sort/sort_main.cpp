#include "sort.h"
#include "../common.h"


/**
To show Chinese
Other option: -fexec-charset=GBK -finput-charset=UTF-8

*/
#define PASS() printf("%s------pass!\n",__FUNCTION__)

#define TEST(F) {\
 memcpy(keys,org,sizeof(int)*n);\
testCore((F),keys,n,#F);}

#define testSort(F,N) \
    {int* keys=new int[(N)];\
createRandomData(keys,(N));\
   testCore((F),keys,(N),#F);\
    delete[] keys;\
    }

int getIntegerDigit(int t) {
    int m=0;
    while(t) {
        t/=10;
        ++m;
    }
    return m;
}
typedef void (*SortFunc)(int* keys,int n);
//typedef int (*SortFunc)(int* keys,int b,int e);
//typedef int (*SearchFixedFunc)(int* keys, const int key);

//C++ sort
void testCPPLibSort(int n=10) {
    int* keys=new int[n];
    time_t seed;
    time(&seed);
    srand(seed);
    for(int i=0; i<n; ++i) {
        //最大不超过n
        keys[i]=rand()%n;
    }
    std::sort(keys,keys+n);
    printArray(keys,n);

}
void testCLibQSort(int n=10) {
    int* keys=new int[n];
    time_t seed;
    time(&seed);
    srand(seed);
    for(int i=0; i<n; ++i) {
        //最大不超过n
        keys[i]=rand()%n;
    }
    qsort(keys,n,sizeof(int),compareInt);
    printArray(keys,n);
}

void testBitSort(int n=100) {
    int* keys=new int[n];
    createRandomUniqPostiveData(keys,n);
    bitSortNoDuplicatePositiveInteger(keys,n,n);
    printArray(keys,n);
    assertSorted(keys,n);
    delete[] keys;

}
void testRadixSort(int n=10) {
    int m=getIntegerDigit(n);
    int* keys=new int[n];
    time_t seed;
    time(&seed);
    srand(seed);
    for(int i=0; i<n; ++i) {
        keys[i]=rand()%n;
    }
    printArray(keys,n);
    radixSortForPositiveInteger(keys,n,m,10);


    printArray(keys,n);
    assertSorted(keys,n);
    delete[] keys;


}



#define testCore(F,K,N,S) {\
    if((N)<100) printArray((K),(N));\
    int start = clock();\
    (F)((K),(N));\
    int clicks = clock() - start;\
    printf("%-32.32s\tn=%d\tclicks=%d\ttime=%gns\n",\
           (S),(N), clicks,\
           1e9*clicks/((float) CLOCKS_PER_SEC));\
    if((N)<100) printArray((K),(N));\
    assertSorted((K),(N));}


/**

insertSort1              n=123456        clicks=53354    time=5.3354e+010ns
insertSort2              n=123456        clicks=17623    time=1.7623e+010ns
insertSort3              n=123456        clicks=11888    time=1.1888e+010ns
insertSortWithBisearch   n=123456        clicks=9151     time=9.151e+009ns
quickSortLomuto          n=123456        clicks=30       time=3e+007ns
quickSortSedgewick       n=123456        clicks=40       time=4e+007ns
quickSortTwoWay          n=123456        clicks=20       time=2e+007ns
quickSortFinal           n=123456        clicks=10       time=1e+007ns
selectSort               n=123456        clicks=52277    time=5.2277e+010ns
shellSort                n=123456        clicks=80       time=8e+007ns
heapSort1                n=123456        clicks=40       time=4e+007ns
heapSort2                n=123456        clicks=60       time=6e+007ns
heapSort3                n=123456        clicks=50       time=5e+007ns
heapSort4                n=123456        clicks=30       time=3e+007ns
heapSortByMaxHeap        n=123456        clicks=50       time=5e+007ns
bubbleSort1              n=123456        clicks=85358    time=8.5358e+010ns
bubbleSortWithFlag       n=123456        clicks=86560    time=8.656e+010ns
mergeSort1               n=123456        clicks=20       time=2e+007ns
mergeSort2               n=123456        clicks=30       time=3e+007ns
radixSort                n=123456        clicks=340      time=3.4e+008ns

**/
void testDriverCore(int* keys,unsigned int n) {
    const unsigned int STACK_MAX_SIZE=1024*1024;
    if(keys==NULL||n<0) return;
//    int* keys=new int[n];
    int* org=new int[n];
    memcpy(org,keys,sizeof(int)*n);
//    printArray(keys,n);
    ////////////////////////////
//    printf("begin testing...\n");
    //!If use large and ordered data, quicksort will first crash
    //!due to stack size
    if(n<(STACK_MAX_SIZE)/sizeof(int)/4) {
        TEST(quickSortLomuto);
        TEST(quickSortSedgewick);
        TEST(quickSortTwoWayPartition);
        TEST(quickSortFinal);
    } else {
        printf("Ignore the slow algs when %d>=%d\n",n,(STACK_MAX_SIZE)/sizeof(int)/4);
    }


//!slower than recursive because stack is set manually
    TEST(quickSortNonRecursive);
    TEST(quickSortNonRecursive2);

    TEST(heapSort);
    TEST(heapSort2);
    TEST(heapSortIdxFromOne);
//    TEST(heapSortIdxFromOne2);
    TEST(heapSort3);
    TEST(heapSort4);

    TEST(mergeSortTopDown);
    TEST(mergeSortBottomUp);

    {
        memcpy(keys,org,sizeof(int)*n);
        int m=getIntegerDigit(n);
        int start = clock();
        radixSortForPositiveInteger(keys,n,m,10);
        int clicks = clock() - start;
        printf("%-16.16s\tn=%d\tclicks=%d\ttime=%gns\n",
               "radixSortForPositiveInteger",n, clicks,
               1e9*clicks/((float) CLOCKS_PER_SEC));
        if(n<50) printArray(keys,n);
        assertSorted(keys,n);
    }


    if(n<88888) {
        TEST(shellSort);
        TEST(insertSort);
        TEST(insertSort2);
        TEST(insertSortWithBisearch);
        TEST(selectSort);
        TEST(bubbleSort1);
        TEST(bubbleSortWithFlag);
        TEST(bubbleSortWithPos);
        TEST(bubbleSortWithTwoDirs);
        TEST(bubbleSortWithTwoDirsAndPos);
    } else {
        printf("Ignore the slow algs when %d>=%d",n,88888);
    }

    delete[] org;
}


void testDriver(int n) {
    int* keys=new int[n];
    int i;
    printf("testing random data...\n");
    for(i=0; i<n; ++i)
        keys[i]=rand()%n;
    testDriverCore(keys,n);

    printf("\ntesting ordered data...\n");
    for(i=0; i<n; ++i)
        keys[i]=i;
    testDriverCore(keys,n);

    printf("\ntesting same data...\n");
    for(i=0; i<n; ++i)
        keys[i]=0;
    testDriverCore(keys,n);

    delete[] keys;


}
void testShowingDetail(int n=100) {
    int* org=new int[n];
    int* keys=new int[n];
    createRandomUniqPostiveData(org,n);
    memcpy(keys,org,sizeof(int)*n);
    printArray(org,n);

    insertSortShowingDetail(keys,n);
    assertSorted(keys,n);
//    printArray(keys,n);
    memcpy(keys,org,sizeof(int)*n);

    shellSortShowingDetail(keys,n);
    assertSorted(keys,n);
//    printArray(keys,n);
    memcpy(keys,org,sizeof(int)*n);

    selectSortShowingDetail(keys,n);
    assertSorted(keys,n);
//    printArray(keys,n);
    memcpy(keys,org,sizeof(int)*n);

    quickSortShowingDetail(keys,n);
    assertSorted(keys,n);
//    printArray(keys,n);
    memcpy(keys,org,sizeof(int)*n);

    bubbleSortShowingDetail(keys,n);
    assertSorted(keys,n);
//    printArray(keys,n);
    memcpy(keys,org,sizeof(int)*n);


    delete[] keys;
    delete[] org;
}

void testQuickSortForDup() {
    int* ptr=NULL;
    int n=0;

    int a[]= {99,5,36,2,19,1,46,12,7,22,25,28,17,92};
    ptr=a;
    n=sizeof(a)/sizeof(int);
    printArray(ptr,n);
    quickSortForDup(ptr,n);
    printArray(ptr,n);
    printf("\n");

    int b[]= {2,1,1,1,1,1,1};
    ptr=b;
    n=sizeof(b)/sizeof(int);
    printArray(ptr,n);
    quickSortForDup(ptr,n);
    printArray(ptr,n);
    printf("\n");

}

//Test sort with well-prepared data
void testSortFunc(SortFunc func) {
    int* ptr=NULL;
    int n=0;

    //case 1
    int a[]= {99,5,36,2,19,1,46,12,7,22,25,28,17,92};
    ptr=a;
    n=sizeof(a)/sizeof(int);
    printArray(ptr,n);
    func(ptr,n);
    printArray(ptr,n);
    printf("\n");
    assertSorted(ptr,n);

    //case 2
    //The case that most values are the same
    int b[]= {2,1,1,1,1,1,1};
    ptr=b;
    n=sizeof(b)/sizeof(int);
    printArray(ptr,n);
    func(ptr,n);
    printArray(ptr,n);
    printf("\n");
    assertSorted(ptr,n);


    //case 3
    //One element
    int c[]= {0};
    ptr=c;
    n=sizeof(c)/sizeof(int);
    printArray(ptr,n);
    func(ptr,n);
    printArray(ptr,n);
    printf("\n");
    assertSorted(ptr,n);



    //Random case
    testSort(func,99);

    //Sorted data
    n=50000;
//    n=100;
    int* sorted=(int*)malloc(n*sizeof(int));
    for(int i=0; i<n; ++i)
        sorted[i]=i;
    func(sorted,n);


}


int testSortMain() {


//!incorrect
//    testSortFunc(quickSortForDup);

//testSortFunc(mergeSortTopDown);
//testSortFunc(mergeSortBottomUp);
//    testSortFunc(heapSort2);
//testSortFunc(heapSort);
//testSortFunc(quickSortLomuto);
//testSortFunc(bubbleSortWithTwoDirsAndPos);
//testSortFunc(bubbleSortWithTwoDirs);
//testSortFunc(bubbleSortWithPos);
//testSortFunc(selectSortMinMax);
//testSortFunc(selectSort);
//testSortFunc(shellSort4);
//testSortFunc(shellSort3);
//testSortFunc(shellSort2);
//testSortFunc(quickSortNonRecursive);
//    testSortFunc(quickSortTwoWayPartition3);

//    testSortFunc(quickSortTwoWayPartition2);

//    testSortFunc(quickSortTwoWayPartition);
//    testSortFunc(quickSortLomuto2);



    int n=100;
//int n=123456;
//int n=50000;
//    int n=12345;

    testDriver(n);




//
//    int* keys=new int[n];
//    int* result;
//    int i;
//    printf("testing random data...\n");
//    for(i=0; i<n; ++i)
//        keys[i]=rand()%n;
//    printArray(keys,n);
//    mergeSort(keys,n);
////    mergeSort2(keys,n);
//    printArray(keys,n);
//    assertSorted(keys,n);
//
//
//

//testShowingDetail();

//    testRadixSort(10);
//    testRadixSort(100);
//
//testSort(insertSortWithBisearch,n);
//    testBitSort();

//    testSort(mergeSort2,n);
//    testSort(mergeSort1,n);
//testSort(selectSort,n);
//testSort(bubbleSortWithFlag,n);
//    testSort(bubbleSort1,n);
//    testCLibQSort();
//    testSort(quickSortFinal,100);
//    testSort(quickSortFinal,40);
//    testSort(quickSortTwoWayPartition);
//    testSort(quickSortSedgewick);
//    testSort(quickSortLomuto);
//    testSort(insertSort3);
//    testSort(insertSort2);
//    testSort(insertSort1);
//    testCPPLibSort();
    return 0;
}

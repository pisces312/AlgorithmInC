#include "../common.h"
#include "../sort/sort.h"
/**
Just get K max, no need to sort the k elements!!


**/
inline int compareIntDecr(const void* x,const void* y) {
    return *(int*)y-*(int*)x;
}

//Decrease order sort and get first k elements
int* kMaxBySort(int k,int* x,int n) {
    qsort(x,n,sizeof(int),compareIntDecr);
//Build result
    int* result=new int[k];
    for(int i=0; i<k; ++i)
        result[i]=x[i];
    return result;
}
//////////////////////////////////////////////////////////
//Decrease sort order
//Use first element as pivot
static int partitionForKMax(int*x,int low,int high) {
    if(low >= high)
        return -1;
    int pivot = x[low];
    while(low < high) {
        while(low < high && pivot >= x[high]) --high;
        x[low] = x[high];
        while(low < high && x[low] >= pivot) ++low;
        x[high] = x[low];
    }
    x[low] = pivot;
    return low;
}

//Make [0,k) to be result
static void kMaxByPartition(int k,int* x,int low,int high) {
    int p=partitionForKMax(x,low,high);
    if(p<0)
        return;
    if(p-low+1==k) {
        printf("  [=k]: p=%d,k=%d, find[%d,%d]\n",p,k,low,p);
        return;
    }
    //|...|p|p+1,...,k-1|k,...|
    //p=3,k=8 |...|3|4,...,7|8,...|
    //(8-1)-(3+1)+1=4
    //find k-p-1 max
    if(p-low+1<k) {
        printf("  [<k]: p=%d,k=%d, find[%d,%d]\n",p,k,low,p);
        kMaxByPartition(k-p+low-1,x,p+1,high);
    } else {
        //|...,k-1|k,...|p|p+1,...|
        //p=8,k=3 |...,2|3,...|8|9,...|
        //Still find k max, right border decreased
        printf("  [>k]: p=%d,k=%d\n",p,k);
        kMaxByPartition(k,x,low,p-1);
    }
}
int* kMaxByPartition(int k,int* x,int n) {
    kMaxByPartition(k,x,0,n-1);

    int* result=new int[k];
    for(int i=0; i<k; ++i)
        result[i]=x[i];
    return result;
}

//////////////////////////////////////////////////////


static void kMaxByPartition2(int k,int* x,int low,int high,int* result) {
    int p=partitionForKMax(x,low,high);
    if(p<0)
        return;

//p divides result to two sets
//[low,p],[p+1,high]
    if(p-low+1==k) {
        printf("  [=k]: p=%d,k=%d, find[%d,%d]\n",p,k,low,p);
        //Return the whole set
        for(int i=low; i<=p; ++i)
            result[i]=x[i];
        return;
    }
    //|...|p|p+1,...,k-1|k,...|
    //p=3,k=8 |...|3|4,...,7|8,...|
    //(8-1)-(3+1)+1=4
    //find k-p-1 max
    if(p-low+1<k) {
        printf("  [<k]: p=%d,k=%d, find[%d,%d]\n",p,k,low,p);
        for(int i=low; i<=p; ++i)
            result[i]=x[i];
        kMaxByPartition2(k-p+low-1,x,p+1,high,result);
    } else {
        //|...,k-1|k,...|p|p+1,...|
        //p=8,k=3 |...,2|3,...|8|9,...|
        //Still find k max, right border decreased
        printf("  [>k]: p=%d,k=%d\n",p,k);
        kMaxByPartition2(k,x,low,p-1,result);
    }
}
int* kMaxByPartition2(int k,int* x,int n) {
    int* result=new int[k];
    kMaxByPartition2(k,x,0,n-1,result);
    return result;
}


//////////////////////////////////////////////////////

static int compareToK(int k,int*x,int n,int midVal) {
    int c=0;
    for(int i=0; i<n; ++i) {
        if(x[i]>=midVal) {
            ++c;
            if(c>k)    {
                break;
            }
        }
    }
    return c-k;
}

static void findMinMax(int *x, int n, int& minVal,int& maxVal) {
    if(n<=0) {
        minVal=INT_MAX;
        maxVal=INT_MIN;
        return;
    }
    minVal=x[0];
    maxVal=x[0];
    for(int i=0; i<n-1; i+=2) {
        if(x[i]<=x[i+1]) {
            if(x[i]<minVal) {
                minVal=x[i];
            }
            if(x[i+1]>maxVal) {
                maxVal=x[i+1];
            }
        } else {
            if(x[i+1]<minVal) {
                minVal=x[i+1];
            }
            if(x[i]>maxVal) {
                maxVal=x[i];
            }
        }
    }

    if(n&0x1) { //odd number
        if(x[n-1]<minVal)
            minVal=x[n-1];
        if(x[n-1]>maxVal)
            maxVal=x[n-1];
    }


}

//For data that distributed in a large range
int* kMaxBySearch(int k,int* x,int n) {
    int* result=new int[k];
//    double d=0.5;
//    double maxVal=INT_MAX;
//    double minVal=INT_MIN;
//    int d=1;
//    int maxVal=INT_MAX;
//    int minVal=INT_MIN;

    int maxVal;
    int minVal;
    int midVal=INT_MAX;
    int preMidVal=INT_MAX;
    findMinMax(x,n,minVal,maxVal);

    while(maxVal>minVal) { //cannot use maxVal-minVal
        preMidVal=midVal;
        //!!cannot add directly, exceed max value of int
//        midVal=minVal+(maxVal-minVal)/2;
        midVal=maxVal/2+minVal/2;
        //if max-min=1, next mid will not change, need exit
        if(preMidVal==midVal)
            break;

        printf("[%d,%d]\n",minVal,maxVal);
        if(compareToK(k,x,n,midVal)>=0) {
            minVal=midVal;
        } else {
            maxVal=midVal;
        }
    }
//    printf("%d\n",minVal);

    //Set result
    int j=0;
    for(int i=0; i<n; ++i)
        if(x[i]>minVal) {
            result[j]=x[i];
            ++j;
        }
    //x>min are counted, add same min value at last
    for(; j<k; ++j)
        result[j]=minVal;

    return result;
}


//!TODO [0,2^(m-1)] [2^(m-1),2^m]
int* kMaxBySearch2(int k,int* x,int n) {
    return NULL;
}

//!TODO Use heap
int* kMaxByHeap(int k,int* x,int n) {
    return NULL;
}


void testKMax() {
    //
    int* keys=NULL;
    int k=3;
    int a[]= {99,5,36,2,19,1,46,12,7,22,25,28,17,92};
    int n=sizeof(a)/sizeof(int);
    int * result=kMaxBySort(k,a,n);
    printArray(result,k);
    printf("\n");

    result=kMaxByPartition(k,a,n);
    printArray(result,k);
    printf("\n");

    result=kMaxByPartition2(k,a,n);
    printArray(result,k);
    printf("\n");

    result=kMaxBySearch(k,a,n);
    printArray(result,k);
    printf("\n");
//
    int b[]= {2,1,1,1,1,1,1};
    n=sizeof(b)/sizeof(int);
    result=kMaxBySort(k,b,n);
    printArray(result,k);
    printf("\n");

    result=kMaxByPartition(k,b,n);
    printArray(result,k);
    printf("\n");

    result=kMaxByPartition2(k,b,n);
    printArray(result,k);
    printf("\n");

    result=kMaxBySearch(k,b,n);
    printArray(result,k);
    printf("\n");

    //
    n=100;
    k=10;
    keys=new int[n];
    createRandomData(keys,n);
    result=kMaxBySort(k,keys,n);
    printArray(result,k);
    printf("\n");

    result=kMaxByPartition(k,keys,n);
    printArray(result,k);
    printf("\n");

    result=kMaxByPartition2(k,keys,n);
    printArray(result,k);
    printf("\n");

    result=kMaxBySearch(k,keys,n);
    printArray(result,k);
    printf("\n");
    delete[] keys;
}

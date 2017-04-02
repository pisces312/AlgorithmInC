#include "max_seq_sum.h"
#include "../common.h"


typedef int(*MaxSeqSumFunc)(int*,int, int*, int*);
typedef int(*MaxSeqSumFunc2)(int*,int);

void testMaxContinuousSeqSumInternal(MaxSeqSumFunc func,int* a, int n) {
    int max,left,right;
    max=func(a,n,&left,&right);
    //Check result
    printf("maxSeq=[%d:%d], sum=%d\n",left,right,max);
    for(int i=left; i<=right; ++i) {
        printf("%d ",a[i]);
    }
    printf("\n");
}

void testMaxContinuousSeqSumInternal2(MaxSeqSumFunc2 func,int* a, int n) {
    int max=func(a,n);
    //Check result
    printf("sum=%d\n",max);
}


void testMaxContinuousSeqSum() {
    int n;
    int *a;

    int d1[]= {2,1,-3,7,1,9,-12,5,0,-1,7};
    n=sizeof(d1)/sizeof(int);
    a=d1;
    testMaxContinuousSeqSumInternal(maxSeqSum1,a,n);
    testMaxContinuousSeqSumInternal(maxSeqSum2,a,n);
    testMaxContinuousSeqSumInternal(maxSeqSum3,a,n);
    testMaxContinuousSeqSumInternal2(maxSeqSum4,a,n);


    int d2[]= { -2, 11, -4, 13, -5, -2 };
    n=sizeof(d2)/sizeof(int);
    a=d2;
    testMaxContinuousSeqSumInternal(maxSeqSum1,a,n);
    testMaxContinuousSeqSumInternal(maxSeqSum2,a,n);
    testMaxContinuousSeqSumInternal(maxSeqSum3,a,n);
    testMaxContinuousSeqSumInternal2(maxSeqSum4,a,n);

}

#include "../common.h"


template <typename T>
int linearSearchGeneric(const T* keys, const int n,int b,int e, const T key) {
    int i = b;
    while (i <= e && keys[i]!=key)
        ++i;
    if (i > e)
        return -1;
    return i;
}


int linearSearch(int* keys, int n,int b,int e, int key) {
    int i = b;
    while (i <= e && keys[i]!=key)
        ++i;
    if (i > e)
        return -1;
    return i;
}


void testSearch() {
    int a[]= {4,2,7,3,8,4,2,1,9};
    int n=sizeof(a)/sizeof(int);

    int i=linearSearchGeneric<int>(a,n,0,n-1,1);
    printf("a[%d]=%d\n",i,a[i]);

    i=linearSearch(a,n,0,n-1,1);
    printf("a[%d]=%d\n",i,a[i]);
}

#include "common.h"

void printArray(int*a,int low,int high) {
    if(!a) return;
    if(low<0) return;
    for(int i=low; i<=high; ++i)
        printf("%d ",a[i]);
    printf("\n");
}

void printArray(int*a,int n) {
    printArray(a,0,n-1);
}
//释放二维数组
void free_Array2D(void **arr) {
    if(arr != NULL)
        free(arr);
}




//Test utils

void assertSorted(int *x,int n) {
    for(int i=1; i<n; ++i)
        if(x[i-1]>x[i])
            assert(false);
}
void createRandomData(int* keys,int n) {
    time_t seed;
    time(&seed);
    srand(seed);
    for(int i=0; i<n; ++i)
        keys[i]=rand()%n;
}
void createRandomUniqPostiveData(int* keys,int n) {
    time_t seed;
    time(&seed);
    srand(seed);
    for(int i=0; i<n; ++i)
        keys[i]=i;
    int a=0,b=0;
    for(int i=0; i<n; ++i) {
        a=rand()%n;
        b=rand()%n;
        swap(keys,a,b);
    }
}


//template<class T>
//void display(T a[],int n) {
//    for(int i=0; i<n; i++)
//        std::cout<<a[i]<<" ";
//    std::cout<<std::endl;
//}

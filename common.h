#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <memory.h>

#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <algorithm>

//定义打印宏，并在打印信息前加入文件名、行号、函数名
#define PRINTFUNC() \
    printf("<%s>: ",__FUNCTION__)
//此宏展开后，类似于printf("123"),printf("456");
#define TRACE1 (printf("%s(%d)-<%s>: ",__FILE__, __LINE__, __FUNCTION__), printf)

//此宏展开后，类似于printf("%d""%d", 1, 2);
#define TRACE2(fmt,...) \
    printf("%s(%d)-<%s>: "##fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

inline void swapInt(int* a,int* b) {
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
//inline void swap(int* x,int i, int j)
//{ int t = x[i];
//  x[i] = x[j];
//  x[j] = t;
//}
inline void swap(int* x,const int i, const int j) {
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}
void printArray(int*a,int n) ;

/* getbits:  get n bits from position p */
inline unsigned getbits(unsigned x, int p, int n) {
    return (x >> (p+1-n)) & ~(~0 << n);
}
inline int isEven(int n) {
    return !(n&0x1);
}
//template<class T>
//void display(T a[],int n) {
//    for(int i=0; i<n; i++)
//        std::cout<<a[i]<<" ";
//    std::cout<<std::endl;
//}
//template<class T>
//void display(T* a,int n);
//void display(T a[],int n);
#endif // COMMON_H_INCLUDED

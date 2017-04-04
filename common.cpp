#include "common.h"
void printArray(int*a,int n) {
    int i;
    if(!a) return;
    if(n<1) return;
    for(i=0; i<n; ++i)
        printf("%d ",a[i]);
    printf("\n");
}
//释放二维数组
void free_Array2D(void **arr) {
    if(arr != NULL)
        free(arr);
}
//template<class T>
//void display(T a[],int n) {
//    for(int i=0; i<n; i++)
//        std::cout<<a[i]<<" ";
//    std::cout<<std::endl;
//}

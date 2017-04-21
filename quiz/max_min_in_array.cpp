//2.10 寻找数组中的最大值和最小值
//
//1，可以将者看成两个独立的问题。
//个需要比较N次，需要比较2*N次。
//
//2，我们可以两两分组。
//每一对中较小的放左边，较大放右边。 N/2次。
//奇数位比较N/2次，找到最小值。
//偶数位比较N/2次，找到最大值。
//总的比较次数：1.5N。
//缺点：破坏了原数组。
//
//3，维持两个变量min和max。
//取出两个数，相比较1次。
//较小的和min比较，决定是否更新min。
//同理，更新max。
//可见处理两个数，比较3次。
//总的比较次数：1.5N
//优点：不会破坏原来的数组。
//
//4，分治思想
#include <iostream>
using namespace std;
//递归实现
//分治
void maxmin(int a[],int low,int high,int& max,int& min) { //引用作为参数的强大作用
    int k, max1,min1,max2,min2;
    if(high-low==1||high-low==0) {
        a[low]>a[high]? (max = a[low], min = a[high]):(max = a[high], min = a[low]);
    } else {
        k=(high+low)/2;
        maxmin(a,low,k,max1,min1);
        maxmin(a,k+1,high,max2,min2);
        //一层比较两次
        max=max1>max2? max1:max2;
        min=min1<min2? min1:min2;
    }
}
void MaxMin2(int *a,int n,int& max,int& min) {
    max=min=a[n-1];
    if((n&0x1)!=0)
        --n;

    for(int i=0; i<n-1; i+=2)
        if(a[i]>a[i+1]) {
            max=a[i]>max?a[i]:max;
            min=a[i+1]<min?a[i+1]:min;
        } else {
            max=a[i+1]>max?a[i+1]:max;
            min=a[i]<min?a[i]:min;
        }

}
void testMaxInInArray() {
    int max,min;
    int data[]= {8,3,6,2,1,9,4,5,7};
    int num=sizeof(data)/sizeof(data[0]);
//    maxmin(data,0,num-1,max,min);
    MaxMin2(data,num,max,min);
    cout<<"最大值:"<<max<<endl;
    cout<<"最小值:"<<min<<endl;
}
//
//复杂度分析：
//
//f(2) = 1;
//f(n) = 2*f(n/2) + 2; (注：一层需要比较两次)
//可以推出f(n) = 1.5*n -2;
//可见总的比较次数仍然没有减少。

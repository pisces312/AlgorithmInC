#include "../common.h"
/**
0,1,2,3,4,5,6, 7, 8, 9,10
0,1,1,2,3,5,8,13,21,34,55
f(0)=0,f(1)=1
**/
//Recursive version
long fibonacci(long n) {
    if(n<=0)
        return 0;
    if(n==1)
        return 1;
    return fibonacci(n-1)+fibonacci(n-2);
}
//Iteration version
long fibonacci2(long n) {
    int pre=0,pre2=1,s=0;
    if(n<=0)
        return 0;
    if(n==1)
        return 1;
    for(int i=2; i<=n; ++i) {
        s=pre+pre2;
        pre=pre2;
        pre2=s;
    }
    return s;
}
//!TODO matrix version

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

#include "../common.h"
//Calculate greatest common divisor
//x and y must be positive integer
//x>0 and y>0

//!Basic way, use "%"
//No need to make sure x>=y
//Because if x<=y, gcd(y,x%y)=gcd(y,x)
//just equivalent to swap x and y
int gcd(int x,int y) {
    return (!y)?x:gcd(y,x%y);
}
//Use "-" instead of "%"
//Make sure x>=y
int gcd2(int x,int y) {
    if(x<y) //swap x and y by argument order adjust
        return gcd2(y,x);
    if(y==0)
        return x;
    return gcd2(y,x-y); //Not consider argument order
//    return gcd2(x-y,y); //ok
}

//Use ">>" to avoid big integer division
int gcd3(int x,int y) {
    if(x<y)
        return gcd3(y,x);
    if(y==0)
        return x;
    if(isEven(x)) {
        if(isEven(y)) //must *2 if both are divided by 2
            return gcd3(x>>1,y>>1)<<1;
        return gcd3(x>>1,y);
    }
    if(isEven(y))
        return gcd3(x,y>>1);
    return gcd3(y,x-y);
}
void testGCD() {
    int n=gcd(42,30);
    printf("%d\n",n);

    n=gcd(30,42);
    printf("%d\n",n);

    n=gcd2(42,30);
    printf("%d\n",n);

    n=gcd2(30,42);
    printf("%d\n",n);

    n=gcd3(42,30);
    printf("%d\n",n);

    n=gcd3(30,42);
    printf("%d\n",n);

}

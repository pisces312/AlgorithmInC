#include"../common.h"
extern int gcd(int,int);
//x=gcd*a, y=gcd*b
//lcm=a*b*gcd=a*gcd*b*gcd/gcd=x*y/gcd

int lcm(int x,int y) {
    return x*y/gcd(x,y);
}

void testLCM() {
    int n=lcm(42,30);
    printf("%d\n",n);

    n=lcm(30,42);
    printf("%d\n",n);
}

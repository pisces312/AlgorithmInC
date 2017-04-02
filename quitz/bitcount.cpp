#include"bitcount.h"
#include"../common.h"
#include <nmmintrin.h>


int bitCountByRemainder(unsigned int n) {
    unsigned int c = 0 ;
    while(n > 0) {
        if((n %2) == 1)
            ++c ;
        n/=2;
    }
    return c ;
}


int bitCountByBitOp(unsigned int n) {
    unsigned int c = 0 ; // 计数器
    while(n > 0) {
        if((n & 0x1) == 1) // 当前位是1
            ++c ; // 计数器加1
        n >>= 1 ; // 移位
    }
    return c ;
}

int bitCountByBitOp2(unsigned int n) {
    unsigned int c = 0 ; // 计数器
    for(c = 0; n>0 ; n >>= 1)  // 循环移位
        c += n & 1 ; // 如果当前位是1，则计数器加1
    return c ;
}

int bitCountFast(unsigned int n) {
    unsigned int c = 0 ;
    for(c = 0; n; ++c)
        n &= (n - 1) ; // 清除最低位的1
    return c ;
}


int bitCountByDynamicTable(unsigned int n) {
    unsigned char BitsSetTable256[256] = {0} ;

    // 初始化表
//1.如果它是偶数，那么n的二进制中1的个数与n/2中1的个数是相同的
//因为n是由n/2左移一位而来，而移位并不会增加1的个数。
//2.如果n是奇数，那么n的二进制中1的个数是n/2中1的个数+1
//因为当n是奇数时，n相当于n/2左移一位再加1。
    for(int i = 0; i < 256; i++)
        BitsSetTable256[i] = (i & 1) + BitsSetTable256[i / 2];

    unsigned int c = 0 ;

    // 查表
//    分割为4部分，每部分8bit，对于这四个部分分别求出1的个数，再累加起来即可。
//    而8bit对应2^8 = 256种01组合方式
//! use 8bit char pointer to access to each part of 32bit int
    unsigned char * p = (unsigned char *) &n ;
    c = BitsSetTable256[p[0]] +
        BitsSetTable256[p[1]] +
        BitsSetTable256[p[2]] +
        BitsSetTable256[p[3]];

    return c ;
}

int bitCountStatic4bitTable(unsigned int n) {
    unsigned int table[16] = {
        //0(0),1(1),2(10),3(11)
        0, 1, 1, 2,
        //4(100),5(101),6(110),7(111)
        1, 2, 2, 3,
        //8(1000),9(1001),10(1010),11(1011)
        1, 2, 2, 3,
        //12(1100),13(1101),14(1110),15(1111)
        2, 3, 3, 4
    } ;

    unsigned int c = 0 ;
    while(n) {
        c += table[n & 0xf] ;
        n >>= 4 ;
    }
    return c ;
}


int bitCountStatic8bitTable(unsigned int n) {
    unsigned int table[256] = {
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    };

    return table[n & 0xff] +
           table[(n >> 8) & 0xff] +
           table[(n >> 16) & 0xff] +
           table[(n >> 24) & 0xff] ;
}


int bitCountParalell(unsigned int n) {
    n = (n & 0x55555555) + ((n >> 1) & 0x55555555) ;
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333) ;
    n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f) ;
    n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff) ;
    n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff) ;
    return n ;
}

//About mod calculate
int bitCountParalell2(unsigned int n) {
    //32bits at most has 32
    //
    //every 2bits group, 01,10
    n = (n & 0x55555555) + ((n >> 1) & 0x55555555) ;
    //every 4bits group, 0001,0010,0011,0100
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333) ;
    //every 8bits group
    n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f) ;
    return n%255;
}




//Oct, not Hex
int bitCountBy3bitGroup(unsigned int n) {
    //1. For every 3bit group: (4a + 2b + c) – (2a + b) – a = a + b + c
    //   Count 1's number within each 3bit group
    //2. Calculate 2a+b for 3bit group
    //  1) n>>1
    //  When right shift, higher 3bit group's lowest bit become
    //  highest bit of lower 3bit group
    //  To make sure every 3bit group divide 2 will not larger than
    //  original value
    //  E.g.
    //    111|001 -> divide 2 -> 011|101, expect value is 011|001
    //  2) So have to &033333333333
    //  033333333333=011|011|011|011...
    //  011111111111=001|001|001|001...
    //3. Calculate a, similar as #2
    //4. Sum nearby 3bit group: tmp + (tmp >> 3)
    //      Some groups will be summed twice
    //   E.g. (a)001 (b)010 (c)011 (d)100
    //       +       (a)001 (b)010 (c)011 (d)100
    //       =   001    011    101    111
    //       &   000    111    000    111
    //       =   000    011  | 000    111
    //   1's number in 6bit group
    //       Should only keep odd groups, so & 030707070707
    //       011|000|111|000|111|000|111|...
    //5. Every 6bit group now
    //   x0+x1*64+x2*64*64 = x0+x1+x2 (mod 63)
    unsigned int tmp = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);
    return ((tmp + (tmp >> 3)) & 030707070707) % 63;
}


struct _byte {
    unsigned a:1;
    unsigned b:1;
    unsigned c:1;
    unsigned d:1;
    unsigned e:1;
    unsigned f:1;
    unsigned g:1;
    unsigned h:1;
};

unsigned bitCountOfChar(unsigned char b) {
    struct _byte *by = (struct _byte*)&b;
    return (by->a+by->b+by->c+by->d+by->e+by->f+by->g+by->h);
}
int bitCountByByteStruct(unsigned int n) {
    unsigned char * p = (unsigned char *) &n;
    return bitCountOfChar(p[0]) +
           bitCountOfChar(p[1]) +
           bitCountOfChar(p[2]) +
           bitCountOfChar(p[3]);
}

//-msse4.2
//target specific option mismatch
inline int bitCountByCPU(unsigned int n) {
    return _mm_popcnt_u32(n) ;
}

///////////////////////////////
typedef int(*BitCountFunc)(unsigned int);


/**
Print, time, assert
F: function
N: number
**/
#define assertBitCount(F,N) {\
    int start = clock();\
    int c=(F)((N));\
    int clicks = clock() - start;\
    printf("%s(%d)=%d\tclicks=%d\ttime=%gns\n",\
           (#F),(N),c, clicks,\
           1e9*clicks/((float) CLOCKS_PER_SEC)); \
    assert(c==bitCountByRemainder(N));}

//Add different algorithm
void testBitCountCore(unsigned int n) {
    assertBitCount(bitCountByRemainder,n);
    assertBitCount(bitCountByBitOp,n);
    assertBitCount(bitCountByBitOp2,n);
    assertBitCount(bitCountFast,n);
    assertBitCount(bitCountByDynamicTable,n);
    assertBitCount(bitCountStatic4bitTable,n);
    assertBitCount(bitCountStatic8bitTable,n);
    assertBitCount(bitCountBy3bitGroup,n);
    assertBitCount(bitCountParalell,n);
    assertBitCount(bitCountParalell2,n);
    assertBitCount(bitCountByByteStruct,n);
    assertBitCount(bitCountByCPU,n);
}

//Add different input
void testBitCount() {
    testBitCountCore(65535);
    testBitCountCore(42235);
    testBitCountCore(19283);
//    printf("%d\n",((1+64+64*64+64*64*64)%63));

}

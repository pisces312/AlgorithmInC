#include "../common.h"
////////////////////////////////////////
//Check whether one number is prime


namespace prime {
//Basic version
//According to concept
//Time: O(n)
bool isPrimeBasic(unsigned long long n) {
    if(n<2) return false;
    for (unsigned long long i=2; i<n; i++)
        if (n%i==0)
            return false;
    return true;
}

//Narrow scope
//Only handle odd divider
//Time: O(n/2)
bool isPrimeOnlyWithOdd(unsigned long long n) {
    if(n<2) return false;
    if(n==2) return true;
    if(n%2==0) return false;
    for (unsigned long long i=3; i<n; i+=2)
        if (n%i==0) return false;
    return true;
}

//Narrow scope
//定理: 如果n不是素数, 则n有满足1<d<=sqrt(n)的一个因子d.
//证明: 如果n不是素数, 则由定义n有一个因子d满足1<d<n.
//如果d大于sqrt(n), 则n/d是满足1<n/d<=sqrt(n)的一个因子.
//!Use i*i<=n
bool isPrimeSqrt(const unsigned long long n) {
    if(n<2) return false;
    if(2==n) return true;
    if(n%2==0) return false;
    for (unsigned long long i = 3; i*i < n; i += 2)
        if (!(n % i))
            return false;
    return true;
}


//Use sqrt
//!Must use i<=sqrtN, otherwise 4,16 can be treated as prime
bool isPrimeSqrt2(unsigned long long n) {
    if(n < 2) return false;
    unsigned long long sqrtN=(unsigned long long)sqrt(n);
    for (unsigned long long i=2; i<=sqrtN; i++)
        if (n%i==0)
            return false;
    return true;
}
//Use sqrt + optimization for even number
bool isPrimeSqrt3(unsigned long long n) {
    if(n<2) return false;
    if(2==n) return true;
    if(n%2==0) return false;
    unsigned long long sqrtN=(unsigned long long)sqrt(n);
    //Start with odd and increase by 2
    for (unsigned long long i=3; i<=sqrtN; i+=2)
        if (n%i==0)
            return false;
    return true;
}

////////////////////////////////////////////////
// Filter

//By default, all are prime
//max n
//print filter all

bool* primeByFilter(unsigned long long n) {
    if(n<2) return NULL;

    bool* primes=(bool*)malloc((n+1)*sizeof(bool));
    //By default, all are prime
    memset(primes,1,(n+1)*sizeof(bool));
    primes[0]=0;
    primes[1]=0;

    //Handle even number
    for (unsigned long long i = 4; i <= n; primes[i]=0,i += 2);
    //!Max divider is sqrtN
    for (unsigned long long i = 3,rsqrt= (unsigned long long)sqrt(n); i <= rsqrt; i += 2)
        //!Only consider prime, but will greatly enhance performance
        if (primes[i])
            for (unsigned long long j = 2*i; j <= n; j += i)
                primes[j] = 0;
    return primes;
}

//By default, all odd number are prime except 1
bool* primeByFilter2(unsigned long long n) {
    if(n<2) return NULL;

    //By default, all are not prime
    bool* primes=(bool*)calloc(n+1,sizeof(bool));
    primes[2]=1;

    //Handle odd number
    for (unsigned long long i = 3; i <= n; primes[i]=1,i += 2);
    //!Max divider is sqrtN
    for (unsigned long long i = 3,rsqrt= (unsigned long long)sqrt(n); i <= rsqrt; i += 2)
        if (primes[i]) //!Only consider prime
            for (unsigned long long j = 2*i; j <= n; j += i)
                primes[j] = 0;
    return primes;
}

//Only care whether one element is prime, primes[n]
//So just ignore all even numbers
bool isPrimeByFilter(int n) {
    if(n<2) return false;
    if(2==n) return true;
    if(n%2==0) return false;

    bool* primes=(bool*)malloc((n+1)*sizeof(bool));
    memset(primes,1,(n+1)*sizeof(bool));
    primes[0]=0;
    primes[1]=0;

    //!Not handle even number here, it's handled in "if(n%2==0)"
    for (int i = 3,rsqrt= (int)sqrt(n); i <= rsqrt; i += 2)
        if (primes[i]) //!Only consider prime factor
            for (int j = 2*i; j <= n; j += i)
                primes[j] = 0;

    bool result=primes[n];
    free(primes);
    return result;
}

static int showPrimeFromArrayMap(bool* arr, int len) {
    int c=0;
    for (int i=2; i<len; i++)
        if (arr[i]) {
            printf("%ld ",i);
            ++c;
        }
    printf("\n");
    return c;
}
static int countPrimeFromArrayMap(bool* arr, int len) {
    int c=0;
    for (int i=2; i<len; i++)
        if (arr[i])
            ++c;
    return c;
}

/////////////////////////////////////////////////

//!Output primes from [0,n] directly
//定理: 如果n不是素数, 则n有满足1<d<=sqrt(n)的一个"素数"因子d.
//证明: I1. 如果n不是素数, 则n有满足1<d<=sqrt(n)的一个因子d.
//I2. 如果d是素数, 则定理得证, 算法终止.
//I3. 令n=d, 并转到步骤I1
unsigned long long* makePrimes(unsigned long long n,unsigned int* primeCnt) {

    //n/2 means only odd number can be prime, the only exception is 2
    //Store prime
    unsigned long long* primes=(unsigned long long*)malloc((n/2+1)*sizeof(unsigned long long));

    int cnt=2; //initial size of primes array
    primes[0] = 2;
    primes[1] = 3;

    for(int i = 5; i<=n && cnt<n; i += 2) { //cnt will be changed dynamically
        bool flag = true;
        for(int j = 1; primes[j]*primes[j] <= i; ++j) {
            if(i%primes[j] == 0) {
                flag = false;
                break;
            }
        }
        if(flag) primes[cnt++] = i;
    }

    *primeCnt=cnt;
    return primes;
}

typedef struct Node {
    unsigned long long data;
    Node* next;
} Node;

Node* makePrimesLinkedList2(unsigned long long n) {

    Node* root=(Node*)malloc(sizeof(Node));
    root->data=2;
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->data=3;
    newNode->next=NULL;
    root->next=newNode;
    Node* lastNode=newNode;

    for(int i = 5; i<=n; i += 2) {
        bool flag = true;
        for(Node* p=root; (p->data)*(p->data)<=i; p=p->next) {
            if(i%p->data == 0) {
                flag = false;
                break;
            }
        }
        if(flag) {
            newNode=(Node*)malloc(sizeof(Node));
            newNode->data=i;
            newNode->next=NULL;
            lastNode->next=newNode;
            lastNode=newNode;
        }
    }

    return root;
}




std::list<unsigned long long>* makePrimesLinkedList(unsigned long long n) {

    std::list<unsigned long long>* primes=new std::list<unsigned long long>();
    primes->push_back(2);
    primes->push_back(3);

    for(int i = 5; i<=n; i += 2) {
        bool flag = true;
        for(std::list<unsigned long long>::iterator prime=primes->begin(); (*prime)*(*prime)<=i; ++prime) {
            if(i%(*prime) == 0) {
                flag = false;
                break;
            }
        }
        if(flag) primes->push_back(i);
    }

    return primes;
}




/////////////////////////////////////////////////
static unsigned int getBit(int index) {
    unsigned int k;
    switch (index) {
    case 0:
        k=0x80000000;
        break;
    case 1:
        k=0x40000000;
        break;
    case 2:
        k=0x20000000;
        break;
    case 3:
        k=0x10000000;
        break;
    case 4:
        k=0x08000000;
        break;
    case 5:
        k=0x04000000;
        break;
    case 6:
        k=0x02000000;
        break;
    case 7:
        k=0x01000000;
        break;
    case 8:
        k=0x00800000;
        break;
    case 9:
        k=0x00400000;
        break;
    case 10:
        k=0x00200000;
        break;
    case 11:
        k=0x00100000;
        break;
    case 12:
        k=0x00080000;
        break;
    case 13:
        k=0x00040000;
        break;
    case 14:
        k=0x00020000;
        break;
    case 15:
        k=0x00010000;
        break;
    case 16:
        k=0x00008000;
        break;
    case 17:
        k=0x00004000;
        break;
    case 18:
        k=0x00002000;
        break;
    case 19:
        k=0x00001000;
        break;
    case 20:
        k=0x00000800;
        break;
    case 21:
        k=0x00000400;
        break;
    case 22:
        k=0x00000200;
        break;
    case 23:
        k=0x00000100;
        break;
    case 24:
        k=0x00000080;
        break;
    case 25:
        k=0x00000040;
        break;
    case 26:
        k=0x00000020;
        break;
    case 27:
        k=0x00000010;
        break;
    case 28:
        k=0x00000008;
        break;
    case 29:
        k=0x00000004;
        break;
    case 30:
        k=0x00000002;
        break;
    case 31:
        k=0x00000001;
        break;
    }
    return k;
}
static void setBit(unsigned int& num,int index,int value) {
    unsigned int k=getBit(index);
    if (value>0)
        num|=k;
    else {//不能用异或
        //这里必须用有符号数
        k=~k;
        num&=k;
    }
}
static void printBit(unsigned int num) {
    for (unsigned int k=0x80000000; k>0; k>>=1)
        if (num&k)
            printf("%d",1);
        else
            printf("%d",0);
    printf("\n");
}

static int showPrimeFromBitMap(unsigned int* arr, int capacity,int bits) {
    int c=0;
    for (int i=0,x=0,len=capacity*bits+1; i<len; i++)
        for (unsigned int j=0,b=0x80000000; j<bits&&x<capacity; j++,b>>=1,++x) {
            if (arr[i]&b) {
                printf("%ld ",x);
                ++c;
            }
        }
    printf("\n");
    return c;
}

static int countPrimeFromBitMap(unsigned int* arr, int capacity,int bits) {
    int c=0;
    for (int i=0,x=0,len=capacity*bits+1; i<len; i++)
        for (unsigned int j=0,b=0x80000000; j<bits&&x<capacity; j++,b>>=1,++x) {
            if (arr[i]&b) {
                ++c;
            }
        }
    return c;
}
//Filter + Bitmap
//Calculate the prime between [0,capacity]
void primeUsingBit(unsigned long long capacity=100) {
    //使用int作为bit的容器,win32中位32位
    unsigned int each=32;
    unsigned int size=capacity/each+1;
    unsigned int* array=new unsigned int[size];
    unsigned long i;
    for (i=0; i<size; i++)
        array[i]=0xffffffff;
    setBit(array[0],0,0);
    setBit(array[0],1,0);

    unsigned long seed=1,div,count;
    unsigned long square=sqrt(capacity);
    do {
        for (i=seed+1; i<capacity; i++) {
            int p=i/each;
            int index=i%each;
            int c=0;
            unsigned int k=0x80000000;
            while (c<index) {
                k>>=1;
                c++;
            }
            if ((array[p]&k)!=0) {
                seed=i;
                break;
            }

        }
        //这里以种子的平方开始筛，平方以内的数已被前面的素数筛过了

        for (div=seed*seed; div<capacity; div+=seed) {
            int p=div/each;
            int index=div%each;
            setBit(array[p],index,0);
        }
    } while (i<square);


    int c=showPrimeFromBitMap(array,capacity,each);
    printf("Count:%d\n",c);
}
//改进版
//必须用unsigned long long 数据类型才能够表示大的数
//使用位来筛,可以计算完1亿内的素数！！
unsigned int* primeUsingBit2(unsigned long long capacity) {
    //Use only 32bit of int
    int bits=32;
    unsigned long long size=capacity*bits+1;
    unsigned int* array=new unsigned int[size];
    unsigned long long i,div,d;
    for (i=0ull; i<size; i++)
        array[i]=0x55555555;
    //Special cases
    setBit(array[0],0,0);
    setBit(array[0],1,0);
    setBit(array[0],2,1);

    for (i=3ull; i<capacity; i+=2)
        for (div=i*i,d=i*2; div<capacity; div+=d)
            setBit(array[div>>5],div%bits,0);
    return array;
}

//筛法求素数,效率高！！
//ordinal限制素数
void prime(int ordinal) {
    int size=200000;//素数最大值

    //默认值为0
    bool* array=new bool[size];
    for (int i=0; i<size; i++)
        array[i]=true;
    int seed=2,div,i;
    do {
        div=seed+seed;
        for (; div<size; div+=seed)
            array[div]=false;
        //选择种子
        for (i=seed+1; i<size; i++)
            if (array[i]) {
                seed=i;
                break;
            }
    } while (i<size);


    for (int i=2,count=0; i<size; i++)
        if (array[i]) {
            count++;
            printf("[%d]:%d\n",count,i);
            if (count==ordinal)
                break;
        }
}



typedef bool(*PrimeCheck)(unsigned long long);

void testPrimeValidate(unsigned long long n) {
    printf("--------%lu--------\n",n);
    printf("%d\n",isPrimeBasic(n));
    printf("%d\n",isPrimeOnlyWithOdd(n));
    printf("%d\n",isPrimeSqrt(n));
    printf("%d\n",isPrimeSqrt2(n));
    printf("%d\n",isPrimeSqrt3(n));
    printf("%d\n",isPrimeByFilter(n));
}

void testPrime() {
    testPrimeValidate(4);
    testPrimeValidate(1997);




    primeUsingBit(100ull);


//    unsigned long long  capacity=100ull;
    unsigned long long  capacity=1000000ull;
    int c=0;
    unsigned int* array=NULL;
    BEGIN_TIMING();
    array=primeUsingBit2(capacity);
    STOP_TIMING();
    printf("Mem usage: %luKB\n",(sizeof(unsigned int)*(capacity/32+1))/1024);
    c=countPrimeFromBitMap(array,capacity,32);
    printf("Count:%d\n",c);
    if(capacity<=100) {
        c=showPrimeFromBitMap(array,capacity,32);
    }

    bool* result=NULL;
    BEGIN_TIMING();
    result=primeByFilter(capacity);
    STOP_TIMING();
    printf("Mem usage: %luKB\n",(sizeof(bool)*(capacity+1))/1024);
    c=countPrimeFromArrayMap(result,capacity+1);
    printf("Count:%d\n",c);
    if(capacity<=100) {
        c=showPrimeFromArrayMap(result,capacity+1);
    }


    BEGIN_TIMING();
    result=primeByFilter2(capacity);
    STOP_TIMING();
    printf("Mem usage: %luKB\n",(sizeof(bool)*capacity+1)/1024);
    c=countPrimeFromArrayMap(result,capacity+1);
    printf("Count:%d\n",c);
    if(capacity<=100) {
        c=showPrimeFromArrayMap(result,capacity+1);
    }

    unsigned int cnt=0;
    unsigned long long* primes=NULL;
    BEGIN_TIMING();
    primes=makePrimes(capacity,&cnt);
    STOP_TIMING();
    printf("Mem usage: %luKB\n",(sizeof(unsigned long long)*(capacity/2+1))/1024);
    printf("Count:%ld\n",cnt);
    if(capacity<=100) {
        for(int i=0; i<cnt; ++i)
            printf("%llu ",primes[i]);
        printf("\n");
    }


    std::list<unsigned long long>* primesList=NULL;
    BEGIN_TIMING();
    primesList=makePrimesLinkedList(capacity);
    STOP_TIMING();
    printf("Count:%ld\n",cnt);
    if(capacity<=100) {
        for(std::list<unsigned long long>::iterator itr=primesList->begin(); itr!=primesList->end(); ++itr)
            printf("%llu ",*itr);
        printf("\n");
    }


    Node* primeNode=NULL;
    BEGIN_TIMING();
    primeNode=makePrimesLinkedList2(capacity);
    STOP_TIMING();
    printf("Count:%ld\n",cnt);
    if(capacity<=100) {
        for(Node* p=primeNode; p!=NULL; p=p->next) {
            printf("%llu ",p->data);
        }
        printf("\n");
    }
}
}

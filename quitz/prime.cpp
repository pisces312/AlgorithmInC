#include "prime.h"
#include "../common.h"
//求素数
//平方根方法判断素数
bool isPrime(unsigned long long n) {
    unsigned long long sqrtN=(unsigned long long)sqrt(n);
    for (unsigned long long i=2; i<sqrtN; i++)
        if (n%i==0)
            return false;
    return true;
}
bool isPrime2(unsigned long long n) {
    unsigned long long sqrtN;
    if(2==n)
        return true;
    if(!(n%2))
        return false;
    sqrtN=(unsigned long long)sqrt(n);
    for (unsigned long long i=3; i<sqrtN; i+=2)
        if (n%i==0)
            return false;
    return true;
}
bool isPrime64(const unsigned long long n) {
    unsigned long long i;
    if(2==n) {
        return true;
    }
    if (!(n % 2))
        return false;
    for (i = 3; i*i <= n; i += 2)
        if (!(n % i))
            return false;
    return true;
}

unsigned int getBit(int index) {
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
void setBit(unsigned int& num,int index,int value) {
    //法二
    unsigned int k=getBit(index);
    if (value>0) {

        num|=k;
    } else {//不能用异或
        //这里必须用有符号数
        k=~k;
        num&=k;
    }
    //法一
//    unsigned int k=0x80000000;
//    for (int i=0;i<index;i++) {
//        k>>=1;
//    }
//    if (value>0) {
//
//        num|=k;
//    } else {//不能用异或
//        //这里必须用有符号数
//        k=~k;
//        num&=k;
//    }

}
void printBit(unsigned int num) {
    for (unsigned int k=0x80000000; k>0; k>>=1)
        if (num&k)
            printf("%d",1);
        else
            printf("%d",0);
    printf("\n");
}

//使用位来筛,可以计算完1亿内的素数！！
void primeUsingBit() {
    //最大的范围，不包括capacity本身
    unsigned long capacity=100;
//    unsigned long capacity=100000000;
    //使用int作为bit的容器,win32中位32位
    unsigned int each=8*sizeof(int);
//    cout<<"unit size="<<each<<endl;
    unsigned int size=capacity/each+1;
    unsigned int* array=new unsigned int[size];
//    cout<<"array size="<<size<<endl;
    unsigned long i;
    for (i=0; i<size; i++) {
        //初始化为1，表示默认都是1
        array[i]=0xffffffff;
//        print(array[i]);
    }
    setBit(array[0],0,0);
    setBit(array[0],1,0);
//    print(array[0]);

//    cout<<"\ninitilize finished\n";


    unsigned long seed=1,div,count;
    unsigned long square=sqrt(capacity);
    do {
        //选择种子
//        count=seed+1;
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
//                cout<<"seed="<<seed<<endl;
                break;
            }

        }
//        for (i=(seed+1)/each;i<size;i++) {

//            for (unsigned int j=0,k=0x80000000;j<each;j++,k>>=1) {
//
//                if ((array[i]&k)!=0) {
//                    seed=count;
//                    cout<<"seed="<<seed<<endl;
//                    break;
//                }
//                count++;
//            }

//        }
        //这里以种子的平方开始筛，平方以内的数已被前面的素数筛过了

        for (div=seed*seed; div<capacity; div+=seed) {
            int p=div/each;

            int index=div%each;
//            cout<<p<<" "<<index<<endl;
            setBit(array[p],index,0);
        }


    } while (i<square);
//    cout<<"prime filter complete\n";
//    print(array[0]);


    count=0;
    for (i=0; i<size; i++)
        for (unsigned int j=0,k=0x80000000; j<each; j++,k>>=1) {
            if (count>=capacity)
                break;
            if ((array[i]&k)!=0)
                printf("%ld\n",count);
            count++;
        }

}
//改进版
//必须用unsigned long long 数据类型才能够表示大的数
//使用位来筛,可以计算完1亿内的素数！！
void primeUsingBit2() {
    unsigned long long capacity=2000000ull;
    //使用int作为bit的容器,win32中位32位
    int each=8*sizeof(int);
//    cout<<"unit size="<<each<<endl;
    unsigned long long size=capacity/each+1;
    unsigned int* array=new unsigned int[size];
//    cout<<"array size="<<size<<endl;
    unsigned long long i;
    for (i=0; i<size; i++) {
        //初始化为1，表示默认都是1
        array[i]=0xffffffff;
//        print(array[i]);
    }
    setBit(array[0],0,0);
    setBit(array[0],1,0);
//    print(array[0]);

//    cout<<"\ninitilize finished\n";

    unsigned long long sum=2ull;
    unsigned long long div;
    printf("2 ");
    //选择种子
    for (i=3ul; i<capacity; i+=2) {
        unsigned int k=getBit(i%each);
        if ((array[i/each]&k)!=0) {
//            cout<<i<<endl;
            sum+=i;
//            if (sum>=2000000) {
//                sum-=i;
//                break;
//            }
        }
        //种子即为所求的素数

        unsigned long long d=i*2;
        for (div=i*i; div<capacity; div+=d) {
            setBit(array[div/each],div%each,0);
        }
    }
    printf("sum=%I64u\n",sum);
//    printf("sum=%lu\n",sum);
}
unsigned int* primeUsingBit2(unsigned long long capacity) {
//    unsigned long long capacity=2000000ull;
    //使用int作为bit的容器,win32中位32位
    int each=8*sizeof(int);
//    in each=32;
//    cout<<"unit size="<<each<<endl;
    unsigned long long size=(capacity>>5)+1;
    unsigned int* array=new unsigned int[size];
//    cout<<"array size="<<size<<endl;
    unsigned long long i;
    for (i=0ull; i<size; i++) {
        //初始化为1，表示默认都是1
        array[i]=0x55555555;
//        array[i]=0xffffffff;
//        print(array[i]);
    }
    setBit(array[0],0,0);
    setBit(array[0],1,0);
    setBit(array[0],2,1);
//    print(array[0]);

//    cout<<"\ninitilize finished\n";

//    unsigned long long sum=2ull;
    unsigned long long div,d;
//    cout<<2<<endl;
    //选择种子
    for (i=3ull; i<capacity; i+=2)
        //种子即为所求的素数
        for (div=i*i,d=i*2; div<capacity; div+=d)
            setBit(array[div>>5],div%each,0);
//    for (i=2ull;i<capacity;i++) {
//        //必须有符号！！！
//        unsigned int k=getBit(i%each);
//        if((array[i/each]&k)!=0){
//            cout<<i<<endl;
//        }
//    }

    return array;
//    cout<<sum<<endl;

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
bool* primes(unsigned long long size) {
//    int size=200000;//素数最大值

    //默认值为0
    bool* array=new bool[size+1];
    array[0]=false;
    array[1]=false;
    array[2]=true;
    for (unsigned long long i=3ull; i<size; i+=2) {
        array[i]=true;
        array[i+1]=false;
    }

    //先单独把2筛出来
//    for (unsigned long long j=4;j<=size;j+=2) {
//        array[j]=false;
//    }
//    cout<<"first filter\n";
    for (unsigned long long i=3ull,d=i*2; i<=size; i+=2)
        for (unsigned long long j=i*i; j<=size; j+=d)
            array[j]=false;
//    cout<<"finished filter\n";
    return array;
}

bool isPrimeFilter(int n) {
    char* primes;
    int rsqrt;
    int i,j;
    char result;

    if(n<2)
        return false;
    if(2==n)
        return true;
    if(!(n%2))
        return false;

    primes=(char*)malloc((n+1)*sizeof(char));
    if(NULL==primes)
        exit(-1);
    memset(primes,1,(n+1)*sizeof(char));

    rsqrt= (int)sqrt(n);
    for (i = 3; i < rsqrt; i += 2)
        if (primes[i])
            for ( j = i; j <= n; j += i)
                primes[j] = 0;
    result=primes[n];
    free(primes);
    return result;
}

void testPrime() {
    int n=1997;
    printf("%d %d\n",n,isPrime(n));
    printf("%d %d\n",n,isPrime2(n));
    printf("%d %d\n",n,isPrime64(n));
    printf("%d %d\n",n,isPrimeFilter(n));
}

#include "random.h"

inline int bigrand() {
    return RAND_MAX*rand() + rand();
}

inline int randint(int l, int u) {
    return l + bigrand() % (u-l+1);
}
//[0,n-1]之间的k个不同的随机数
void createRandomKData(int* keys,int n,int k) {
    time_t seed;
    time(&seed);
    srand(seed);
    for(int i=0; i<n; ++i) {
        keys[i]=i;
    }
    //类似选择排序
    for(int i=0; i<k; ++i) {
        swap(keys,i,randint(i,n-1));
    }
}


//TODO 12
void genknuth(int m, int n) {
    for (int i = 0; i < n; i++)
        /* select m of remaining n-i */
        if ((bigrand() % (n-i)) < m) {
            printf("%d\n",i);
            m--;
        }
}

void gensets(unsigned int m, int n) {
    std::set<int> S;
    std::set<int>::iterator i;
    while (S.size() < m) {
        int t = bigrand() % n;
        S.insert(t);
    }
    for (i = S.begin(); i != S.end(); ++i)
        printf("%d\n",*i);
}

void genshuf(int m, int n) {
    int i, j;
    int *x = new int[n];
    for (i = 0; i < n; i++)
        x[i] = i;
    for (i = 0; i < m; i++) {
        j = randint(i, n-1);
        int t = x[i];
        x[i] = x[j];
        x[j] = t;
    }
    std::sort(x, x+m);
    for (i = 0; i < m; i++)
        printf("%d\n",x[i]);
}

void genfloyd(int m, int n) {
    std::set<int> S;
    std::set<int>::iterator i;
    for (int j = n-m; j < n; j++) {
        int t = bigrand() % (j+1);
        if (S.find(t) == S.end())
            S.insert(t); // t not in S
        else
            S.insert(j); // t in S
    }
    for (i = S.begin(); i != S.end(); ++i)
        printf("%d\n",*i);
}


int testRandomMain() {
    int n=10;
    int k=5;
    int* keys=new int[n];
    createRandomKData(keys,n,k);
    printArray(keys,k);
    delete[] keys;
//    cout << "Hello world!" << endl;
    return 0;
}

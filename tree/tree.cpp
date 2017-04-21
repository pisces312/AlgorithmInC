#include "tree.h"
#include "../common.h"
namespace UnionFind {

//////////////////////////
//Initialize
//The father is itself
void makeSet(int *f,int n) {
    for(int i=0; i<n; ++i) f[i]=i;
}

/////////////////////////
//Find - Get father
//It ends when the father is itself

//Basic, recursive
//No path compression, the tree may be very high
int findSet(int*f,int v) {
    if(f[v]==v) return v;
    return findSet(f,f[v]);
}

//Use path compression, recursive
int findSetByCompress(int*f,int v) {
    if(f[v]==v) return v;
    //Point to root directly
    f[v]= findSetByCompress(f,f[v]);
    return f[v];
}

//Non-recursive
int findSetNonRecursive(int*f,int v) {
    int t=v; //backup original v
    while(f[v]!=v) v=f[v];
    while(f[t]!=t) {
        t=f[t];
        f[t]=v;
    }
    return v;
}

typedef int(*FindSetFunc)(int*,int);
static int unionSet(FindSetFunc findSetFunc,int*f,int v,int u) {
    int s1=findSetFunc(f,v);
    int s2=findSetFunc(f,u);
    if(s1!=s2) {
        f[s2]=s1;
        return 1;
    }
    return 0;
}

///////////////////////////////
//Union

void unionSet(int*f,int v,int u) {
    int t1=findSetByCompress(f,v);
    int t2=findSetByCompress(f,u);
    if(t1!=t2) f[t2]=t1;
}

////////////////////////////////
//Count set number
int countSet(int* f,int n) {
    int c=0;
    for(int i=0; i<n; ++i)
        if(f[i]==i) ++c;
    return c;
}


///////////////////////////////////
//Optimized by rank

void makeSetWithRank(int *f,int n,int* rank) {
    for(int i=0; i<n; ++i) {
        f[i]=i;
        rank[i]=0;
    }
}
//Attach shorter tree as the child of taller one
void unionSetWithRank(int*f,int v,int u,int *rank) {
    int t1=findSet(f,v); //No need path compression
    int t2=findSet(f,u);
    if(t1==t2) return;
    if(rank[t1]>rank[t2])//t1's height is not changed
        f[t2]=t1; //t1 is root, attach t2
    else {
        f[t1]=t2;//t2 is root, attach t1
        if(rank[t1]==rank[t2]) //!Only if original height are the same
            ++rank[t2];//t2's height will be changed
    }
}

///////////////////////////////////////
//Optimized by number
//Don't need rank array

//The value for root is "-totalElementsNumberOfSet"
void makeSetWithNum(int *f,int n) {
    for(int i=0; i<n; ++i) f[i]=-1;
}
//With path compression
int findSetWithNum1(int *f,int v) {
    if(f[v] < 0) return v;
    f[v] = findSetWithNum1(f,f[v]);
    return f[v];
}
//With path compression
int findSetWithNum2(int*f,int v) {
    int t=v; //backup original v
    while(f[v]>=0) v=f[v];//Cannot be "while(f[v])" -1 is not false
    while(f[t]!=t) {
        t=f[t];
        f[t]=v;
    }
    return v;
}
//Consider element number
void unionSetWithNum(int*f,int v,int u) {
    int x=findSetWithNum1(f,v);
    int y=findSetWithNum1(f,u);
    if(x==y) return;
    if(f[x] < f[y]) {//set x has more elements
        f[x] += f[y];//update root's element
        f[y] = x;//attach y to x, f[y] is not root now
    } else {
        f[y] += f[x];
        f[x] = y;
    }
}
int countSetWithNum(int* f,int n) {
    int c=0;
    for(int i=0; i<n; ++i)
        if(f[i]<0) ++c;
    return c;
}



/**

0,1,2,3,4,5

6,7,8


**/
void testUnionFind() {
    const int m=9;
    const int n=9;
    //Tree edge
    int a[m][2]= {{0,1},{2,3},{4,1},{3,5},{1,5},{7,6},{8,6},{0,5},{1,3}};
    int f[n];
    int rank[n];
    int i,sum=0;

    makeSet(f,n);


    for(i=0; i<m; ++i)
        unionSet(f,a[i][0],a[i][1]);
    //Count the number of set
    sum=countSet(f,n);
    printf("sum=%d\n",sum);

    for(i=0; i<m; ++i)
        unionSet(findSet,f,a[i][0],a[i][1]);
    //Count the number of set
    sum=countSet(f,n);
    printf("sum=%d\n",sum);

    for(i=0; i<m; ++i)
        unionSet(findSetByCompress,f,a[i][0],a[i][1]);
    //Count the number of set
    sum=countSet(f,n);
    printf("sum=%d\n",sum);

    for(i=0; i<m; ++i)
        unionSet(findSetNonRecursive,f,a[i][0],a[i][1]);
    //Count the number of set
    sum=countSet(f,n);
    printf("sum=%d\n",sum);


    makeSetWithRank(f,n,rank);
    for(i=0; i<m; ++i)
        unionSetWithRank(f,a[i][0],a[i][1],rank);
    printArray(rank,n);
    //Count the number of set
    sum=countSet(f,n);
    printf("sum=%d\n",sum);



    int b[m][2]= {{0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{3,6},{7,8},{0,2}};
    makeSetWithRank(f,n,rank);
    for(i=0; i<m; ++i)
        unionSetWithRank(f,b[i][0],b[i][1],rank);
    printArray(f,n);
    printArray(rank,n);
    //Count the number of set
    sum=countSet(f,n);
    printf("sum=%d\n",sum);



    makeSetWithNum(f,n);
    for(i=0; i<m; ++i)
        unionSetWithNum(f,b[i][0],b[i][1]);
    printArray(f,n);
    //Count the number of set
    sum=countSetWithNum(f,n);
    printf("sum=%d\n",sum);
}
}

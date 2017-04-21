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
//Find
//It ends when the father is itself

//Basic, recursive
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



///////////////////////////////////
//Optimize by rank

void makeSetWithRank(int *f,int n,int* rank) {
    for(int i=0; i<n; ++i) {
        f[i]=i;
        rank[i]=0;
    }
}
//Attach shorter tree as the child of taller one
void unionSetWithRank(int*f,int v,int u,int *rank) {
    int t1=findSetByCompress(f,v);
    int t2=findSetByCompress(f,u);
    if(t1==t2) return;
    if(rank[t1]<rank[t2]) {
        f[t1]=t2;
        ++rank[t1];
    } else {
        f[t2]=t1;
        ++rank[t2];
    }

}

///////////////////////////////////////


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
    for(i=0,sum=0; i<n; ++i)
        if(f[i]==i) ++sum;
    printf("sum=%d\n",sum);

    for(i=0; i<m; ++i)
        unionSet(findSet,f,a[i][0],a[i][1]);
    //Count the number of set
    for(i=0,sum=0; i<n; ++i)
        if(f[i]==i) ++sum;
    printf("sum=%d\n",sum);

    for(i=0; i<m; ++i)
        unionSet(findSetByCompress,f,a[i][0],a[i][1]);
    //Count the number of set
    for(i=0,sum=0; i<n; ++i)
        if(f[i]==i) ++sum;
    printf("sum=%d\n",sum);

    for(i=0; i<m; ++i)
        unionSet(findSetNonRecursive,f,a[i][0],a[i][1]);
    //Count the number of set
    for(i=0,sum=0; i<n; ++i)
        if(f[i]==i) ++sum;
    printf("sum=%d\n",sum);


    makeSetWithRank(f,n,rank);
    for(i=0; i<m; ++i)
        unionSetWithRank(f,a[i][0],a[i][1],rank);
    for(i=0; i<n; ++i)
        printf("%d\n",rank[i]);
    //Count the number of set
    for(i=0,sum=0; i<n; ++i)
        if(f[i]==i) ++sum;
    printf("sum=%d\n",sum);
}
}

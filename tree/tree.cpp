#include "tree.h"

namespace UnionFind {

void init(int *f,int n) {
    int i;
    for(i=0; i<n; ++i)f[i]=i;//��ʼ�����нڵ�ĸ��ڵ㶼���Լ�
}

int getParent(int*f,int v) {
    if(f[v]==v) return v;
    f[v]=getParent(f,f[v]);
    return f[v];
}
int merge(int*f,int v,int u) {
    int t1=getParent(f,v);
    int t2=getParent(f,u);
    if(t1!=t2) {
        f[t2]=t1;
        return 1;
    }
    return 0;
}

void testUnionFind() {
    const int m=9;
    const int n=10;
    int a[m][2]= {{0,1},{2,3},{4,1},{3,5},{1,5},{7,6},{8,6},{0,5},{1,3}};
    int f[n];
    int i,sum=0;
    for(i=0; i<n; ++i)
        f[i]=i;//��ʼ�����нڵ�ĸ��ڵ㶼���Լ�
    for(i=0; i<m; ++i)
        merge(f,a[i][0],a[i][1]);
    for(i=0; i<n; ++i)
        if(f[i]==i) ++sum;

    printf("sum=%d\n",sum);
}
}

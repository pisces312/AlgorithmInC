#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
namespace UnionFind {
void makeSet(int *f,int n);
int findSet(int*f,int v);
void unionSet(int*f,int v,int u);
}

#endif // TREE_H_INCLUDED

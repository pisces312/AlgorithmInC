#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
namespace UnionFind {
void makeSet(int *f,int n);
int findSet(int*f,int v);
//Path compression recursive version
int findSetByCompress(int*f,int v);
//Path compression iteration version
int findSetNonRecursive(int*f,int v);
void unionSet(int*f,int v,int u);
int countSet(int* f,int n);
///////////////////////////////
void makeSetWithRank(int *f,int n,int* rank);
void unionSetWithRank(int*f,int v,int u,int *rank);

/////////////////////////////
void makeSetWithNum(int *f,int n);
int findSetWithNum1(int *f,int v);
int findSetWithNum2(int*f,int v);
void unionSetWithNum(int*f,int v,int u);
int countSetWithNum(int* f,int n);









}

#endif // TREE_H_INCLUDED

#include "graph.h"
#include "../sort/sort.h"
#include "../tree/tree.h"
#include "../common.h"


namespace graphmatrix {


GraphMatrix* emptyUnweightedGraph(const int verNum) {
    GraphMatrix* g=new GraphMatrix;
    g->n=verNum;
    g->arc=malloc_Array2D<int>(g->n,g->n);

    for(int i=0; i<g->n; ++i)
        for(int j=0; j<g->n; ++j)
            g->arc[i][j]=0;
//            if(i==j) g->arc[i][j]=0;
//            else g->arc[i][j]=INT_MAX;
    return g;
}

//arrSize is 2*arcNum
GraphMatrix* createUnweightedGraph(int vertNum, int* arcs,int arrSize,int directed=0) {
    GraphMatrix* g=emptyUnweightedGraph(vertNum);
    for(int i=0; i<arrSize; i+=2)
        g->arc[arcs[i]][arcs[i+1]]=1;
    if(!directed)
        for(int i=0; i<arrSize; i+=2)
            g->arc[arcs[i+1]][arcs[i]]=1;
    return g;
}


/*******************************************************************
For unweighted, acyclic/cyclic, directed/undirected, connected/unconnected graph
If i<->j, arc[i][j]=1, otherwise is 0
*/
static void dfsUnweightedCore(GraphMatrix* g,int cur,bool* visited) {
    printf("%d ",cur);
    visited[cur]=true;
    for(int i=0; i<g->n; ++i)
        //value!=0 means have an edge
        if(g->arc[cur][i]&&!visited[i])
            dfsUnweightedCore(g,i,visited);
}
void dfsOnlyConnected(GraphMatrix* g,int cur) {
    //Set flag to 0
    bool* visited=(bool*)calloc(g->n,sizeof(bool));
    //Start from cur
    dfsUnweightedCore(g,cur,visited);
    free(visited);
}
void dfs(GraphMatrix* g,int cur) {
    //Set flag to 0
    bool* visited=(bool*)calloc(g->n,sizeof(bool));
    //Start from cur
    dfsUnweightedCore(g,cur,visited);
    //!!Traverse unconnected parts.
    for(int i=0; i<g->n; ++i)
        if(!visited[i])
            dfsUnweightedCore(g,i,visited);
    free(visited);
}

/*******************************************************************/
//!TODO iteration version dfs



//bfs
void bfsOnlyConnected(GraphMatrix* g,int cur) {
    //Set flag to 0
    bool* visited=(bool*)calloc(g->n,sizeof(bool));
    //Start from cur
    std::queue<int> q;
    q.push(cur);
    visited[cur]=true;
    int i=0;
    while(!q.empty()) {
        cur=q.front();
        q.pop();
        printf("%d ",cur);
        for(i=0; i<g->n; ++i)
            if(g->arc[cur][i]&&!visited[i]) {
                visited[i]=true; //must set before push to queue
                q.push(i);
            }
    }
    free(visited);
}
//!
void bfsOnlyConnected2(GraphMatrix* g,int cur) {
    //Set flag to 0
    bool* visited=(bool*)calloc(g->n,sizeof(bool));
    int* q=(int*)malloc(g->n*sizeof(int));
    int front=0;
    int last=1;
    q[front]=cur;

    visited[cur]=true;
    int i=0;
    while(front<last) {
        cur=q[front++];
        printf("%d ",cur);
        for(i=0; i<g->n; ++i)
            if(g->arc[cur][i]&&!visited[i]) {
                visited[i]=true; //must set before push to queue
                q[last++]=i;
            }
    }
    free(visited);
}

void bfs(GraphMatrix* g,int cur) {
    //Set flag to 0
    bool* visited=(bool*)calloc(g->n,sizeof(bool));
    //Start from cur
    std::queue<int> q;
    q.push(cur);
    visited[cur]=true;
    int i=0;
    while(true) {
        while(!q.empty()) {
            cur=q.front();
            q.pop();
            printf("%d ",cur);
            for(i=0; i<g->n; ++i)
                if(g->arc[cur][i]&&!visited[i]) {
                    visited[i]=true;
                    q.push(i);
                }
        }
        //For unconnected parts
        //Every time, push one element
        for(i=0; i<g->n; ++i)
            if(!visited[i]) {
                visited[i]=true;
                q.push(i);
                break;
            }
        if(i==g->n)//All visited
            break;
    }
}





//////////////////////////////////////
//Test

/**
Connected, undirected, unweighted, acyclic graph

0____
|\   \
1 2---4
|
3

**/
GraphMatrix* testGraph1() {
    int arcs[]= {0,1,0,2,0,4,1,3,2,4};
    return createUnweightedGraph(5,arcs,sizeof(arcs)/sizeof(int));
}
/**
Connected, unweighted, acyclic graph
    0
   / \
  1   2
 / \  | \
3  4  5  6
 \  \/  /
  --7---

{0,1,0,2,1,3,1,4,2,5,2,6,3,7,4,7,5,7,6,7}

DFS
0 1 3 7 4 5 2 6
1 0 2 5 7 3 4 6
2 0 1 3 7 4 5 6
3 1 0 2 5 7 4 6
4 1 0 2 5 7 3 6
5 2 0 1 3 7 4 6
6 2 0 1 3 7 4 5
7 3 1 0 2 5 6 4
**/
GraphMatrix* testGraph2() {
    int arcs[]= {0,1,0,2,1,3,1,4,2,5,2,6,3,7,4,7,5,7,6,7};
    return createUnweightedGraph(8,arcs,sizeof(arcs)/sizeof(int));
}



/**
Unconnected, unweighted, acyclic graph
      0
      |
  1   2
 / \  | \
3   4 5--6
 \ /
  7

{0,2,1,3,1,4,2,5,2,6,3,7,4,7,5,6}

DFS
0 1 3 7 4 5 2 6
1 0 2 5 7 3 4 6
2 0 1 3 7 4 5 6
3 1 0 2 5 7 4 6
4 1 0 2 5 7 3 6
5 2 0 1 3 7 4 6
6 2 0 1 3 7 4 5
7 3 1 0 2 5 6 4
**/
GraphMatrix* testGraph3() {
    int arcs[]= {0,2,1,3,1,4,2,5,2,6,3,7,4,7,5,6};
    return createUnweightedGraph(8,arcs,sizeof(arcs)/sizeof(int));
}

///////////////////////////
typedef void(*GraphMatrixTraverseFunc)(GraphMatrix*,int);

//test the traverse which starts from every nodes
#define printGraphTraverse(G,F) { \
    printf("\n<%s>\n", (#F)); \
    for(int i=0; i<g->n; ++i) { \
        F((G),i); \
        printf("\n--------------------------\n"); \
    } }
//Add alg
void testDFSDriver(GraphMatrix* g) {
    printGraphTraverse(g,dfsOnlyConnected);
    printGraphTraverse(g,dfs);
    printGraphTraverse(g,bfsOnlyConnected);
    printGraphTraverse(g,bfs);
    printGraphTraverse(g,bfsOnlyConnected2);
}
//Add input
void testDFS() {
    GraphMatrix* g=NULL;

    testDFSDriver(testGraph1());
    testDFSDriver(testGraph2());
    testDFSDriver(testGraph3());

}

}
////////////////////////////////////////////




namespace simplegraph {

//Edge and actual number of vertex
int n,e[100][100];
//Flag
int visited[100];

static void dfs(int cur) {
    printf("%d ",cur);
    visited[cur]=1;
    for(int i=0; i<n; ++i)
        if(e[cur][i]&&!visited[i])
            dfs(i);
}

void testDFSGraph() {
    n=5;
    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            e[i][j]=0;
    e[0][1]=1;
    e[0][2]=1;
    e[0][4]=1;
    e[1][3]=1;
    e[2][4]=1;
    dfs(0);
}


////////////////////////////////////
void bfsGraph() {
    const int MAX_MATRIC_SIZE=50;
    int e[MAX_MATRIC_SIZE][MAX_MATRIC_SIZE]= {{0}};
    int book[MAX_MATRIC_SIZE]= {0};
    int q[MAX_MATRIC_SIZE*MAX_MATRIC_SIZE];
    int head=0,tail=0;
    int cur=0;
    int i;
    int n=5;

    e[0][1]=1;
    e[0][2]=1;
    e[0][4]=1;
    e[1][3]=1;
    e[2][4]=1;

    q[tail++]=cur;
    book[cur]=1;
    while(head<tail&&tail<n)
        for(i=0,  cur=q[head++]; i<n; ++i)
            if(e[cur][i]==1&&book[i]==0) {
                book[i]=1;
                q[tail++]=i;
                if(tail==n)
                    break;
            }
//    printf("%d ",cur);
//    while(head<tail&&tail<n) {
//        cur=q[head];
//        for(i=0; i<n; ++i)
//            if(e[cur][i]==1&&book[i]==0) {
//                book[i]=1;
//                printf("%d ",i);
//                q[tail++]=i;
//                if(tail==n)
//                    break;
//            }
//        ++head;//pop
//    }
//    printf("\n");

    for(i=0; i<n; ++i) //Queue stores visit sequence
        printf("%d ",q[i]);
    printf("\n");
}

void swapEdge(struct edge* x,struct edge* y) {
    struct edge t=*x;
    *x=*y;
    *y=t;
}
//TODO
static void buildLinkGraph(const int n,const int m, struct edge* e,int* first, int *next) {
    int i;
    for(i=0; i<n; ++i) //Vertex, initial first
        first[i]=-1;
    for(i=0; i<m; ++i) { //Edge, update first and next
        next[i]=first[e[i].u];
        first[e[i].u]=i;
    }
    printf("first:");
    for(i=0; i<n; ++i)
        printf("%d ",first[i]);
    printf("\nnext:");
    for(i=0; i<m; ++i)
        printf("%d ",next[i]);
    printf("\n");
}
void printLinkedGraph(int n,int*first,int*next,struct edge* e) {
    int i,t;
    for(i=0; i<n; ++i) {
        printf("%d:",i);
        t=first[i];
        while(t!=-1) {
            printf("%d(%d) ",e[t].v,e[t].w);
            t=next[t];
        }
        printf("\n");
    }
}



void quickSortForEdge(struct edge* x,int l,int u) {
    if(l >= u)  return;
    int pivot = x[l].w;
    int i = l;
    int j = u+1;
    while(true) {
        do i++;
        while(i <= u && x[i].w < pivot);
        do j--;
        //don't need check j>=l, because x[l]=pivot
        while(x[j].w > pivot);
        if(i >= j)
            break;
        swapEdge(&x[i], &x[j]);
    }
    if(l!=j)//can not use i here, because i may equal to u
        swapEdge(&x[l], &x[j]);
    quickSortForEdge(x,l, j-1);
    quickSortForEdge(x,j+1, u);
}


////////////////////////////////////////////////////////////
void mstByKruskal() {
    struct edge e[9]= {
        {1,3,11},
        {2,4,13},
        {3,5,3},
        {4,5,4},
        {1,2,6},
        {3,4,7},
        {0,1,1},
        {2,3,9},
        {0,2,2}
    };
    const int n=6,m=9;
    int f[n];
    int i,c=0,sum=0;
    int t1,t2;
    quickSortForEdge(e,0,m-1);
//    for(i=0; i<m; ++i) {
//        printf("%d,%d,%d\n",e[i].u,e[i].v,e[i].w);
//    }


    for(i=0; i<n; ++i)f[i]=i;
    for(i=0; i<m&&c<n-1; ++i) {
        t1=UnionFind::getParent(f,e[i].u);
        t2=UnionFind::getParent(f,e[i].v);
        if(t1!=t2) {
            f[t2]=t1;
            ++c;
            sum+=e[i].w;
            printf("add edge <%d,%d>\n",e[i].u,e[i].v);
        }
    }

    printf("sum=%d\n",sum);
}

void mstByPrim() {
    const int n=6;
    int e[n][n],dis[n],book[n]= {0};
    int count=0,sum=0;
    int minValue;
    int i,j,k;
    int start=0;

    for(i=0; i<n; ++i)
        for(j=0; j<n; ++j)
            if(i==j) e[i][j]=0;
            else e[i][j]=INT_MAX;


    e[1][3]=11;
    e[2][4]=13;
    e[3][5]=3;
    e[4][5]=4;
    e[1][2]=6;
    e[3][4]=7;
    e[0][1]=1;
    e[2][3]=9;
    e[0][2]=2;

    e[3][1]=11;
    e[4][2]=13;
    e[5][3]=3;
    e[5][4]=4;
    e[2][1]=6;
    e[4][3]=7;
    e[1][0]=1;
    e[3][2]=9;
    e[2][0]=2;

    for(i=0; i<n; ++i)
        dis[i]=e[start][i];

    book[start]=1;
    ++count;
    printf("add node %d\n",start);
    while(count<n) {
        minValue=INT_MAX;
        for(i=0; i<n; ++i) {
            if(book[i]==0&&dis[i]<minValue) {
                minValue=dis[i];
                j=i;
            }
        }
        book[j]=1;
        printf("add node %d with weight %d\n",j,minValue);
        ++count;
        sum+=dis[j];
        for(k=0; k<n; ++k) //Update dis according to new added node
            if(book[k]==0&&dis[k]>e[j][k])
                dis[k]=e[j][k];
    }
    printf("sum=%d\n",sum);

}

}


////////////////////////////////////////////////////////////




namespace Cutpoint {
//void dfs(int cur, int** e,int* book,int n,int* sum) {
//    int i;
//    printf("%d ",cur);
//    if(++(*sum)==n) return;
//    for(i=0; i<n; ++i)
//        if(e[cur][i]==1&&book[i]==0) {
//            book[i]=1;
//            dfs(i,e,book,n,sum);
//        }
//}

void dfs(int cur, edge* e,int* book,int n,int* sum,int* first,int*next) {
    int t;
    book[cur]=1;
    if(++(*sum)==n) return;
    t=first[cur];
    while(t!=-1) {
        if(book[e[t].v]==0)
            dfs(e[t].v,e,book,n,sum,first,next);
        t=next[t];
    }
}
int isCutpoint(int cur, int n, edge*e, int*first, int*next) {
    int* book=(int*)calloc(n,sizeof(int));
    int sum=1;
    int start,i;

    book[cur]=1;
    for(i=0; i<n; ++i)
        if(cur!=i) {
            start=i;
            break;
        }

    dfs(start,e,book,n,&sum,first,next);

    delete book;
    return (sum!=n);

}
void testCutpoint() {
    int n=6,m=7*2,flag,i;

    int* first=(int*)calloc(n,sizeof(int));
    int* next=(int*)calloc(n,sizeof(int));

    edge e[]= {
        {0,3,1},
        {0,2,1},
        {3,1,1},
        {2,1,1},
        {1,4,1},
        {1,5,1},
        {4,5,1},
        //
        {3,0,1},
        {2,0,1},
        {1,3,1},
        {1,2,1},
        {4,1,1},
        {5,1,1},
        {5,4,1}
    };
    simplegraph::buildLinkGraph(n,m,e,first,next);
    simplegraph::printLinkedGraph(n,first,next,e);
    for(i=0; i<n; ++i) {
        flag=isCutpoint(i,n,e,first,next);
        printf("%d: %d\n",i,flag);
    }
}
}

namespace Cutpoint2 {
int index,root;
int n,m, *first,*next;
edge* e;
int* flags,*low,*num;

int min(int a,int b) {
    return a<b?a:b;
}

//����n-1����
void cutpointDFS(int u,int parent) {
    int t;
    int i,old;
    int child=0;//��¼���Ķ��ӣ���ͼ��δ���ʵĽڵ�
    ++index;
    low[u]=index;//�����Ǵ�parent��
    num[u]=index;


    printf("visit %d, index %d, n %d\n",u,index,n);

    t=first[u];
    while(t!=-1) {
        if(num[e[t].v]==0) {

            cutpointDFS(e[t].v,u);
            old=low[u];

            low[u]=min(low[u],low[e[t].v]);
            //
            //
            printf("low[%d]=min(low[%d](%d),low[%d](%d)=%d\n",u,u,old,e[t].v,low[e[t].v],low[u]);
            printf("low:");
            for(i=0; i<n; ++i)
                printf("%d ",low[i]);
            printf("\nnum:");
            for(i=0; i<n; ++i)
                printf("%d ",num[i]);
            printf("\n");
            //
            //
            //

            ++child;
            if(u!=root&&low[e[t].v]>=num[u]) {
                printf("low[%d](%d)>=num[%d](%d)\n",e[t].v,low[e[t].v],u,num[u]);

                flags[u]=1;
                printf("found %d\n",u);
            } else if(u==root&&child==2)
                flags[u]=1;








        } else if(e[t].v!=parent) { //�������ʹ��ķǸ��ڵ�ҲҪ����
            old=low[u];
            low[u]=min(low[u],num[e[t].v]);
            //
            //
            printf("low[%d]=min(low[%d](%d),num[%d](%d)=%d\n",u,u,old,e[t].v,num[e[t].v],low[u]);
            printf("low:");
            for(i=0; i<n; ++i)
                printf("%d ",low[i]);
            printf("\nnum:");
            for(i=0; i<n; ++i)
                printf("%d ",num[i]);
            printf("\n");
            //
            //
        }
        t=next[t];
    }
}
void testCutpoint() {
    int i;
    n=6;
    flags=(int*)calloc(n,sizeof(int));
    low=(int*)calloc(n,sizeof(int));
    num=(int*)calloc(n,sizeof(int));
    first=(int*)calloc(n,sizeof(int));
    next=(int*)calloc(m,sizeof(int));

    edge e2[]= {
        {0,3,1},
        {0,2,1},
        {3,1,1},
        {2,1,1},
        {1,4,1},
        {1,5,1},
        {4,5,1},
        //
        {3,0,1},
        {2,0,1},
        {1,3,1},
        {1,2,1},
        {4,1,1},
        {5,1,1},
        {5,4,1}
    };




    m=sizeof(e2)/sizeof(edge);
    e=e2;

    simplegraph::buildLinkGraph(n,m,e,first,next);
    simplegraph::printLinkedGraph(n,first,next,e);


    index=0;
    root=0;
    cutpointDFS(0,root);

    printf("low:");
    for(i=0; i<n; ++i)
        printf("%d ",low[i]);
    printf("\nnum:");
    for(i=0; i<n; ++i)
        printf("%d ",num[i]);
    printf("\n");
    //
    for(i=0; i<n; ++i)
        if(flags[i])
            printf("(%d)\n",i);
}
}




namespace Cutedge {
int index,root;
int n,m, *first,*next;
edge* e;
int* flags,*low,*num;

int min(int a,int b) {
    return a<b?a:b;
}

//����n-1����
void cutedgeDFS(int u,int parent) {
    int t;
    ++index;
    low[u]=index;//�����Ǵ�parent��
    num[u]=index;

    t=first[u];
    while(t!=-1) {
        if(num[e[t].v]==0) {
            cutedgeDFS(e[t].v,u);
            low[u]=min(low[u],low[e[t].v]);

            if(low[e[t].v]==num[e[t].v])
//            if(low[e[t].v]>num[u])
                flags[t]=1;//edge flag
        } else if(e[t].v!=parent) //�������ʹ��ķǸ��ڵ�ҲҪ����
            low[u]=min(low[u],num[e[t].v]);
        t=next[t];
    }
}
void testCutedge() {
    int i;
    n=6;

    low=(int*)calloc(n,sizeof(int));
    num=(int*)calloc(n,sizeof(int));
    first=(int*)calloc(n,sizeof(int));
    next=(int*)calloc(m,sizeof(int));

    edge e2[]= {
        {0,3,1},
        {0,2,1},
        {3,1,1},
        {2,1,1},
        {1,4,1},
        {1,5,1},
        //
        {3,0,1},
        {2,0,1},
        {1,3,1},
        {1,2,1},
        {4,1,1},
        {5,1,1}
    };




    m=sizeof(e2)/sizeof(edge);
    flags=(int*)calloc(m,sizeof(int));
    e=e2;

    simplegraph::buildLinkGraph(n,m,e,first,next);
    simplegraph::printLinkedGraph(n,first,next,e);


    index=0;
    root=0;
    cutedgeDFS(0,root);

    printf("low:");
    for(i=0; i<n; ++i)
        printf("%d ",low[i]);
    printf("\nnum:");
    for(i=0; i<n; ++i)
        printf("%d ",num[i]);
    printf("\n");
    //
    for(i=0; i<n; ++i)
        if(flags[i])
            printf("%d-%d\n",e[i].u,e[i].v);
}
}


#include "graph.h"
namespace ShortestPathByDFS {
static const int MAX_DIS=INT_MAX;
static int e[100][100];//Store distance
static int book[100];
static int src,dest;
static int minDis=MAX_DIS,n;
static void dfs(int cur, int dis) {
    int i;
    if(dis>minDis)
        return;
    if(cur==dest) {//Reach destination
        if(dis<minDis)
            minDis=dis;
        return;
    }
    for(i=0; i<n; ++i)
        if(e[cur][i]!=MAX_DIS&&book[i]==0) {
            book[i]=1;
            dfs(i,dis+e[cur][i]);
            book[i]=0;
        }
}
void shortestPathByDFS() {//Shortest path from cur to
    int i,j;
    n=5;
    src=0,dest=4;
    for(i=0; i<n; ++i)
        for(j=0; j<n; ++j)
            if(i==j) e[i][j]=0;
            else e[i][j]=MAX_DIS;

    e[0][1]=2;
    e[0][4]=10;
    e[1][2]=3;
    e[1][4]=7;
    e[2][0]=4;
    e[2][3]=4;
    e[3][4]=5;
    e[4][2]=3;

    book[src]=1;
    dfs(src,0);
    printf("%d\n",minDis);
}
}
////////////////////////////////////////////
void shortestPathByFloydWarshall() {
    static const int MAX_DIS=999;
    static int e[100][100],i,j,k,n=5;

    for(i=0; i<n; ++i)
        for(j=0; j<n; ++j)
            if(i==j) e[i][j]=0;
            else e[i][j]=MAX_DIS;
    e[0][1]=2;
    e[0][2]=6;
    e[0][3]=4;
    e[1][2]=3;
    e[2][0]=7;
    e[2][3]=1;
    e[3][0]=5;
    e[3][2]=12;

    for(k=0; k<n; ++k)
        for(i=0; i<n; ++i)
            for(j=0; j<n; ++j)
                if(e[i][k]<MAX_DIS&&e[k][j]<MAX_DIS&& e[i][j]>e[i][k]+e[k][j])
                    e[i][j]=e[i][k]+e[k][j];


    for(i=0; i<n; ++i) {
        for(j=0; j<n; ++j)
            printf("%3d ",e[i][j]);
        printf("\n");
    }

}


void shortestPathByDijkstra() {
    static const int MAX_DIS=999;
    static int e[10][10],book[10],dis[10];
    int i,j,u,v,minDis,n=6;
    int src=0;//Specify any node

    for(i=0; i<n; ++i)
        for(j=0; j<n; ++j)
            if(i==j) e[i][j]=0;
            else e[i][j]=MAX_DIS;

    //Init data
    e[0][1]=1;
    e[0][2]=12;
    e[1][2]=9;
    e[1][3]=3;
    e[2][4]=5;
    e[3][2]=4;
    e[3][4]=13;
    e[3][5]=15;
    e[4][5]=4;


    for(i=0; i<n; ++i)
        dis[i]=e[src][i];

    for(i=0; i<n; ++i)
        book[i]=0;
    book[src]=1;//Add src to set P

    for(i=0; i<n-1; ++i) {
        minDis=MAX_DIS;
        for(j=0; j<n; ++j)
            if(book[j]==0&&dis[j]<minDis) {
                minDis=dis[j];//Find u with min dis
                u=j;
            }
        book[u]=1;//Add to set P
        for(v=0; v<n; ++v)
            if(e[u][v]<MAX_DIS&&dis[v]>dis[u]+e[u][v])
                dis[v]=dis[u]+e[u][v];
    }

    for(i=0; i<n; ++i)//Result
        printf("%d ",dis[i]);
    printf("\n");

}

/////////////////////////////////////////////////////////////////////////////////////

static void buildLinkGraph(const int n, const int m, int* u,int* first, int *next) {
    int i;
    for(i=0; i<n; ++i) //Vertex, initial first
        first[i]=-1;
    for(i=0; i<m; ++i) { //Edge, update first and next
        next[i]=first[u[i]];
        first[u[i]]=i;
    }
    printf("first:");
    for(i=0; i<n; ++i)
        printf("%d ",first[i]);
    printf("\nnext:");
    for(i=0; i<m; ++i)
        printf("%d ",next[i]);
    printf("\n");
}
void printLinkedGraph(int n,int*first,int*next,int*v,int*w) {
    int i,t;
    for(i=0; i<n; ++i) {
        printf("%d:",i);
        t=first[i];
        while(t!=-1) {
            printf("%d(%d) ",v[t],w[t]);
            t=next[t];
        }
        printf("\n");
    }
}

static void graph1(int*n,int*m,int**u,int**v,int**w,int**first,int**next) {
    *n=4;
    *m=5;
    *first=(int*)malloc(*n*sizeof(int));//store edge index
    *next=(int*)malloc(*m*sizeof(int));
    *u=(int*)malloc(*m*sizeof(int));
    *v=(int*)malloc(*m*sizeof(int));
    *w=(int*)malloc(*m*sizeof(int));
    (*u)[0]=0,(*u)[1]=1,(*u)[2]=0,(*u)[3]=3,(*u)[4]=0;
    (*v)[0]=3,(*v)[1]=3,(*v)[2]=1,(*v)[3]=2,(*v)[4]=2;
    (*w)[0]=9,(*w)[1]=6,(*w)[2]=5,(*w)[3]=8,(*w)[4]=7;
}

static void graphWithCircle(int*n,int*m,int**u,int**v,int**w,int**first,int**next) {
    *n=4;
    *m=6;
    *first=(int*)malloc(*n*sizeof(int));//store edge index
    *next=(int*)malloc(*m*sizeof(int));
    *u=(int*)malloc(*m*sizeof(int));
    *v=(int*)malloc(*m*sizeof(int));
    *w=(int*)malloc(*m*sizeof(int));
    (*u)[0]=0,(*u)[1]=1,(*u)[2]=0,(*u)[3]=3,(*u)[4]=0,(*u)[5]=2;
    (*v)[0]=3,(*v)[1]=3,(*v)[2]=1,(*v)[3]=2,(*v)[4]=2,(*v)[5]=0;
    (*w)[0]=9,(*w)[1]=6,(*w)[2]=5,(*w)[3]=8,(*w)[4]=7,(*w)[5]=-23;
}

void testLinkGraph() {
    int n,m,*u,*v,*w,*first,*next;
    graph1(&n,&m,&u,&v,&w,&first,&next);
    buildLinkGraph(n,m,u,first,next);
    printLinkedGraph(n,first,next,v,w);

}


void shortestPathByDijkstraLinkedGraph() {
    static const int MAX_DIS=999;
    int i,j,t,minDis;
    int src=0, uMin;//Specify any node

    int n=6;
    int m=9;
    int *book=(int*)calloc(n,sizeof(int));
    int *dis=(int*)malloc(n*sizeof(int));
    int *u=(int*)malloc(m*sizeof(int));
    int *v=(int*)malloc(m*sizeof(int));
    int *w=(int*)malloc(m*sizeof(int));
    int *first=(int*)malloc(n*sizeof(int));//store edge index
    int *next=(int*)malloc(m*sizeof(int));
    u[0]=0,u[1]=0,u[2]=1,u[3]=1,u[4]=2,u[5]=3,u[6]=3,u[7]=3,u[8]=4;
    v[0]=1,v[1]=2,v[2]=2,v[3]=3,v[4]=4,v[5]=2,v[6]=4,v[7]=5,v[8]=5;
    w[0]=1,w[1]=12,w[2]=9,w[3]=3,w[4]=5,w[5]=4,w[6]=13,w[7]=15,w[8]=4;

    buildLinkGraph(n,m,u,first,next);
    printLinkedGraph(n,first,next,v,w);

    //Set dis
    for(i=0; i<n; ++i)
        dis[i]=MAX_DIS;
    dis[src]=0;
    t=first[src];
    while(t!=-1) {
        dis[v[t]]=w[t];
        t=next[t];
    }

    book[src]=1;//Add src to set P
    for(i=0; i<n-1; ++i) {
        minDis=MAX_DIS;
        for(j=0; j<n; ++j)//Find the min dis from current table
            if(book[j]==0&&dis[j]<minDis) {
                minDis=dis[j];//Find u with min dis
                uMin=j;
            }
        book[uMin]=1;//Add to set P
        t=first[uMin];
        while(t!=-1) {//Enhanced by linked graph
            if(w[t]<MAX_DIS&&dis[v[t]]>dis[uMin]+w[t])
                dis[v[t]]=dis[uMin]+w[t];
            t=next[t];
        }
    }
    for(i=0; i<n; ++i)//Result
        printf("%d ",dis[i]);
    printf("\n");

}

void shortestPathByBellmanFoard() {
    static const int MAX_DIS=999;
    int i,k,t;
    int src=0, flag;//Specify any node

//    int n=6;
//    int m=9;
//    int *dis=(int*)malloc(n*sizeof(int));
//    int *u=(int*)malloc(m*sizeof(int));
//    int *v=(int*)malloc(m*sizeof(int));
//    int *w=(int*)malloc(m*sizeof(int));
//    int *first=(int*)malloc(n*sizeof(int));//store edge index
//    int *next=(int*)malloc(m*sizeof(int));
//    u[0]=0,u[1]=0,u[2]=1,u[3]=1,u[4]=2,u[5]=3,u[6]=3,u[7]=3,u[8]=4;
//    v[0]=1,v[1]=2,v[2]=2,v[3]=3,v[4]=4,v[5]=2,v[6]=4,v[7]=5,v[8]=5;
//    w[0]=1,w[1]=12,w[2]=9,w[3]=3,w[4]=5,w[5]=4,w[6]=13,w[7]=15,w[8]=4;


//With negative weight
    int n=5;
    int m=5;
    int *dis=(int*)malloc(n*sizeof(int));
    int *u=(int*)malloc(m*sizeof(int));
    int *v=(int*)malloc(m*sizeof(int));
    int *w=(int*)malloc(m*sizeof(int));
    int *first=(int*)malloc(n*sizeof(int));//store edge index
    int *next=(int*)malloc(m*sizeof(int));
    u[0]=1,u[1]=0,u[2]=0,u[3]=3,u[4]=2;
    v[0]=2,v[1]=1,v[2]=4,v[3]=4,v[4]=3;
    w[0]=2,w[1]=-3,w[2]=5,w[3]=2,w[4]=3;



    buildLinkGraph(n,m,u,first,next);
    printLinkedGraph(n,first,next,v,w);

    //Set dis
    for(i=0; i<n; ++i)
        dis[i]=MAX_DIS;
    dis[src]=0;
    t=first[src];
    while(t!=-1) {
        dis[v[t]]=w[t];
        t=next[t];
    }


    for(k=0; k<n-1; ++k) {
        flag=0;
        for(i=0; i<m; ++i)
            if(dis[v[i]]>dis[u[i]]+w[i]) {
                dis[v[i]]=dis[u[i]]+w[i];
                flag=1;
            }
        if(flag==0)
            break;
    }
    printf("Relax finished on %d/%d round\n",k+1,n-1);
    //Check negative ring
    for(i=0; i<m; ++i)
        if(dis[v[i]]>dis[u[i]]+w[i]) {
            printf("Found negative ring");
            break;
        }

    for(i=0; i<n; ++i)//Result
        printf("%d ",dis[i]);
    printf("\n");

}




void shortestPathByBellmanFoardUsingQueue() {
    static const int MAX_DIS=999;
    int i,t;
    int src=0;//Specify any node
    int *qFlags;
    int head=0,tail=0,*q;


    int n=6;
    int m=9;
    int *dis=(int*)malloc(n*sizeof(int));
    int *u=(int*)malloc(m*sizeof(int));
    int *v=(int*)malloc(m*sizeof(int));
    int *w=(int*)malloc(m*sizeof(int));
    int *first=(int*)malloc(n*sizeof(int));//store edge index
    int *next=(int*)malloc(m*sizeof(int));
    u[0]=0,u[1]=0,u[2]=1,u[3]=1,u[4]=2,u[5]=3,u[6]=3,u[7]=3,u[8]=4;
    v[0]=1,v[1]=2,v[2]=2,v[3]=3,v[4]=4,v[5]=2,v[6]=4,v[7]=5,v[8]=5;
    w[0]=1,w[1]=12,w[2]=9,w[3]=3,w[4]=5,w[5]=4,w[6]=13,w[7]=15,w[8]=4;


//With negative weight
//    int n=5;
//    int m=5;
//    int *dis=(int*)malloc(n*sizeof(int));
//    int *u=(int*)malloc(m*sizeof(int));
//    int *v=(int*)malloc(m*sizeof(int));
//    int *w=(int*)malloc(m*sizeof(int));
//    int *first=(int*)malloc(n*sizeof(int));//store edge index
//    int *next=(int*)malloc(m*sizeof(int));
//    u[0]=1,u[1]=0,u[2]=0,u[3]=3,u[4]=2;
//    v[0]=2,v[1]=1,v[2]=4,v[3]=4,v[4]=3;
//    w[0]=2,w[1]=-3,w[2]=5,w[3]=2,w[4]=3;




    buildLinkGraph(n,m,u,first,next);
    printLinkedGraph(n,first,next,v,w);

    qFlags=(int*)calloc(n,sizeof(int));//标记是否在队列中
    //??size, one vertex may be added more than once
    q=(int*)malloc(n*(n-1)*sizeof(int));

    //Set dis
    for(i=0; i<n; ++i)
        dis[i]=MAX_DIS;
    dis[src]=0;

    q[tail++]=src;
    qFlags[src]=1;
    while(head<tail) {
        t=first[q[head]];
        while(t!=-1) {
            if(dis[u[t]]<MAX_DIS&&dis[v[t]]>dis[u[t]]+w[t]) {
                dis[v[t]]=dis[u[t]]+w[t];
                if(qFlags[v[t]]==0) {
                    q[tail++]=v[t];
                    qFlags[v[t]]=1;
                }
            }
            t=next[t];
        }
        qFlags[q[head]]=0;
        ++head;
    }


    for(i=0; i<n; ++i)//Result
        printf("%d ",dis[i]);
    printf("\n");

}



void shortestPathByBellmanFoardCheckingNegativeCircle() {
    static const int MAX_DIS=9999;
    int i,t;
    int src=0;//Specify any node
    int *qFlags;
    int head=0,tail=0,*q;
    int *count;

    int n,m,*u,*v,*w,*first,*next;
    graphWithCircle(&n,&m,&u,&v,&w,&first,&next);
    buildLinkGraph(n,m,u,first,next);
    printLinkedGraph(n,first,next,v,w);

    count=(int*)calloc(n,sizeof(int));

    int *dis=(int*)malloc(n*sizeof(int));
    qFlags=(int*)calloc(n,sizeof(int));//标记是否在队列中
    //??size, one vertex may be added more than once
    q=(int*)malloc(n*(n+1)*sizeof(int));

    //Set dis
    for(i=0; i<n; ++i)
        dis[i]=MAX_DIS;
    dis[src]=0;

    q[tail++]=src;
    qFlags[src]=1;
    while(head<tail) {
        t=first[q[head]];
        if(++count[t]>n) {
            printf("Has negative circle\n");
            break;
        }
        while(t!=-1) {
            if(dis[u[t]]<MAX_DIS&&dis[v[t]]>dis[u[t]]+w[t]) {
                dis[v[t]]=dis[u[t]]+w[t];
                if(qFlags[v[t]]==0) {
                    q[tail++]=v[t];
                    qFlags[v[t]]=1;
                }
            }
            t=next[t];
        }
        qFlags[q[head]]=0;
        ++head;
    }


    for(i=0; i<n; ++i)//Result
        printf("%d ",dis[i]);
    printf("\n");

}

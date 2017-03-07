#include "search.h"
/**
Find a minimum way to a point in a maze
0: empty
1: barrier
**/
static int n;//max row
static int m;//max column
static int px;//
static int py;
static int minStep=9999999;
static int a[50][50],book[50][50];
static void dfs(int x,int y,int step) {
    static const int next[4][2]= {
        {0,1},
        {1,0},
        {0,-1},
        {-1,0}
    };
    int tx,ty,i;
    if(x==px&&y==py) {
        if(step<minStep)
            minStep=step;
        return;
    }

    for(i=0; i<4; ++i) { //4 way to go
        tx=x+next[i][0];//Calc for next step point
        ty=y+next[i][1];
        if(tx<0||tx>=n||ty<0||ty>=m)
            continue;
        if(a[tx][ty]==0&&book[tx][ty]==0) { //empty and not visted
            book[tx][ty]=1;
            dfs(tx,ty,step+1);//try next
            book[tx][ty]=0;
        }
    }
}
void mazebyDFS() {
    a[0][2]=1;
    a[2][2]=1;
    a[3][1]=1;
    a[4][3]=1;

    n=5,m=4;
    px=3,py=2;
    dfs(0,0,0);
    printf("minStep=%d\n",minStep);
}

///////////////////////////////////////////

struct Point {
    int x;
    int y;
    int parent;//index in queue
    int step;
};
void mazebyBFS() {
    const int MAX_MAP_SIZE=50;
    struct Point q[MAX_MAP_SIZE*MAX_MAP_SIZE];
    int head,tail;//For queue
    int a[MAX_MAP_SIZE][MAX_MAP_SIZE]= {0};
    int book[MAX_MAP_SIZE][MAX_MAP_SIZE]= {0};
    static const int next[4][2]= {
        {0,1},
        {1,0},
        {0,-1},
        {-1,0}
    };
    int found=0;
    int i,startx,starty,px,py,tx,ty;

    a[0][2]=1;
    a[2][2]=1;
    a[3][1]=1;
    a[4][3]=1;
    n=5,m=4;
    px=3,py=2;
    startx=0,starty=0;

    head=0,tail=0;//Initial queue
    q[tail].x=startx;//Maze entry
    q[tail].y=starty;
    q[tail].parent=0;
    q[tail].step=0;
    ++tail;
    book[startx][starty]=1;

    while(head<tail&&!found) { //queue is not empty
        for (i=0; i<4; ++i) {
            tx=q[head].x+next[i][0];
            ty=q[head].y+next[i][1];
            if(tx<0||tx>=n||ty<0||ty>=m)
                continue;
            if(a[tx][ty]==0&&book[tx][ty]==0) { //empty and not visted
                book[tx][ty]=1;
                q[tail].x=tx;
                q[tail].y=ty;
                q[tail].parent=head;
                q[tail].step=q[head].step+1;
                ++tail;
            }
            if(tx==px&&ty==py) {
                found=1;
                break;
            }
        }
        ++head;//pop
    }

    printf("%d\n",q[tail-1].step);

}


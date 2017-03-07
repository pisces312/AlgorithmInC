#include "search.h"
static int a[10];//Supported max digit num is 9
static int book[10];//flags, default values are 0
static int n;//digit number, 1~9
static void dfs(int step) {
    int i;
    if(step==n+1) {//Print
        for(i=1; i<=n; ++i)
            printf("%d",a[i]);
        printf("\n");
        return;
    }
    for(i=1; i<=n; ++i)
        if(book[i]==0) {
            a[step]=i;
            book[i]=1;
            dfs(step+1);
            book[i]=0;
        }
}
void permutationByDFS() {
    n=5;
    dfs(1);
}

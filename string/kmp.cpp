#include "../common.h"

void compute_prefix(int *next, char *p) {
    int     i, n, k;
    n = strlen(p);
    next[1] = next[0] = 0;
    k = next[1];
    for(i = 2; i <= n; i++) { //Start from len=2
        //k表示next[i-1]的值
        while(k != 0 && p[k] != p[i-1])
            k = next[k];
        if(p[k] == p[i-1])
            k++;
        next[i] = k;//计算出next[i]
    }
}

int kmp_match(char *text, char *p, int *next) {
    int     m, n, s, q;
    m = strlen(p);
    n = strlen(text);
    q = s = 0;  /* q表示上一次迭代匹配了多少个字符，
                   s表示这次迭代从text的哪个字符开始比较 */
    while(s < n) {
        for(q = next[q]; q < m && p[q] == text[s]; q++, s++);
        if(q == 0) s++;
        else if(q == m)
            return s-m;
    }
    return -1;
}

void testKMP() {
    int     next[101];
    char    p[] = "cca";
    char    text[] = "cacca";

    compute_prefix(next, p);
    int idx=kmp_match(text, p, next);
    printf("pattern occurs with shift %d\n", idx);
}

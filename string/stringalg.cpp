#include "../common.h"

//O(n^2)
bool containRotatedStr1(char* src, char* rs) {
    int len=strlen(src);

    //Not affect source
    char* s=new char[len+1];
    strncpy(s,src,len);

    for(int i=0; i<len; ++i) {
        char t=s[0];
        for(int j=0; j<len-1; ++j)
            s[j]=s[j+1];
        s[len-1]=t;
        if(strstr(s,rs))
            return true;
    }
    return false;
}

bool containRotatedStr2(char* s, char* rs) {
    int len=strlen(s);
    char* s2=new char[2*len+1];
    strncpy(s2,s,len);//Not set NULL implicitly
    strncpy(s2+len,s,len+1);
    bool flag=strstr(s2,rs);
//    printf("%s\n",s2);
    delete[] s2;
    return flag;
}

void testContainRotatedStr1() {
    char s[]="aabbcd";
    char rs[]="cdaa";
    bool flag=false;
    flag=containRotatedStr1(s,rs);
    printf("%d\n",flag);

    flag=containRotatedStr2(s,rs);
    printf("%d\n",flag);
}

void testStringAlg() {
    testContainRotatedStr1();
}

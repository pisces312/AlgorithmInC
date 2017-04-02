#include "max_seq_sum.h"
#include "../common.h"


/**
Find the max value of continuous subsequence

s[i]=max{s[i-1]+a[i],a[i]}

http://blog.csdn.net/qiaoruozhuo/article/details/65630389

**/

//ʹ�ñ���¼����Ķ�̬�滮�㷨
int maxSeqSum1(int* a,int n, int* outputLeft, int* outputRight) {
    //S[i]�����洢��A[i]��β���������������֮��
    int* s=(int*)calloc(n,sizeof(int));
    s[0]=a[0];
    //�洢�����������е�����
    for(int i=1; i<n; ++i)
        if(s[i-1]<0) //"<" and "<=" are the same actually
            s[i]=a[i];
        else
            s[i]=s[i-1]+a[i];

    //Find max value and right border
    int right=0;
    for(int i=1; i<n; ++i)
        if(s[i]>s[right])
            right=i;

//[Optional]Find left border

//Way 1
//    int left=0;
//    for(int i=right-1; i>=0; --i)
//        //If "=", the sequence may contain less elements
//        //will become shorter with same max value
//        if(s[i]<0) {
////        if(s[i]<=0) {
//            left=i+1;
//            break;
//        }

//Way 2
    int left = right; //Ѱ����߽�
    while(left > 0 && s[left-1] > 0)
        --left;

    //Set result
    *outputLeft=left;
    *outputRight=right;

    return s[right];
}

int maxSeqSum2(int* a,int n, int* outputLeft, int* outputRight) {
    //S[i]�����洢��A[i]��β���������������֮��
    int* s=(int*)calloc(n,sizeof(int));
    s[0]=a[0];
    int max=s[0];
    int left=0;
    int right=0;
    //�洢�����������е�����
    for(int i=1; i<n; ++i) {
        if(s[i-1]<0) {
            s[i]=a[i];
            if(s[i]>max) {
                max=s[i];
                left=i;
                right=i;
            }
        } else {
            s[i]=s[i-1]+a[i];
            if(s[i]>max) {
                max=s[i];
                right=i;
            }
        }
    }

    //Set result
    *outputLeft=left;
    *outputRight=right;

    return max;
}

//When use only one variable to store state
//have to record borders
int maxSeqSum3(int* a,int n, int* outputLeft, int* outputRight) {
    //S[i]�����洢��A[i]��β���������������֮��
    int s=a[0];
    int max=s;
    int left=0;
    int right=0;
    //�洢�����������е�����
    for(int i=1; i<n; ++i) {
        if(s<0) {
            s=a[i];
            if(s>max) {
                max=s;
                left=i;
                right=i;
            }
        } else {
            s+=a[i];
            if(s>max) {
                max=s;
                right=i;
            }
        }
    }

    //Set result
    *outputLeft=left;
    *outputRight=right;

    return max;
}

//////////////////////////////////////////////

int maxOf3(int a, int b, int c) {
    if(a >= b && a >= c)
        return a;
    if(b >= a && b >= c)
        return b;
//    if(c >= a && c >= b)
    return c;
}


//Divide and conquer
int MaxSubSum(int* A, int left, int right) {
    int maxLeftSum, maxRightSum;
    int maxLeftBorderSum, maxRightBorderSum;
    int leftBorderSum, rightBorderSum;
    int mid, i;

    if(left == right)
        return (A[left] > 0) ? A[left] : 0;

    mid = (left + right) / 2;
    maxLeftSum = MaxSubSum(A, left, mid); //�ݹ������벿����������
    maxRightSum = MaxSubSum(A, mid+1, right);//�ݹ�����Ұ벿����������

    maxLeftBorderSum = leftBorderSum = 0;
    for(i=mid; i>=left; i--) { //���м俪ʼ����������A[mid]�����е�����
        leftBorderSum += A[i];
        if(leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }

    maxRightBorderSum = rightBorderSum = 0;
    for(i=mid+1; i<=right; i++) {  //���м俪ʼ���Ҽ���A[mid+1]�����е�����
        rightBorderSum += A[i];
        if(rightBorderSum > maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }

    return maxOf3(maxLeftSum, maxRightSum, maxLeftBorderSum+maxRightBorderSum);
}

int maxSeqSum4(int* x, int n) { //�����㷨
    return MaxSubSum(x, 0, n-1);
}

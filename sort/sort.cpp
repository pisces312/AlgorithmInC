#include "sort.h"
#include "../common.h"
#include "../random/random.h"


//最简单的插入排序
/* Simplest insertion sort */
void insertSort(int* x,int n) {
    int i, j;
    for(i = 1; i < n; i++)
        for(j = i; j > 0 && x[j-1] > x[j]; j--)
            swap(x,j-1, j);
}
// Write swap function inline
//void insertSort2(int* x,int n) {
//    int i, j;
//    int t;
//    for(i = 1; i < n; i++)
//        for(j = i; j > 0 && x[j-1] > x[j]; j--) {
//            t = x[j];
//            x[j] = x[j-1];
//            x[j-1] = t;
//        }
//}
//
// Move assignments to and from t out of loop
// Remove swap
void insertSort2(int* x,int n) {
    int i, j;
    int t;
    for(i = 1; i < n; i++) {
        //method2
        t = x[i];
        for(j = i; j > 0 && x[j-1] > t; j--)
            x[j] = x[j-1];
        x[j] = t;
        //
        //method1
//        j=i;
//        while(j>0&&x[i]<x[j-1]) {
//            x[j]=x[j-1];
//            --j;
//        }
//        x[j]=x[i];
    }

}
int binarySearchForInsert(int* keys, int b,int e,const int key) {
    if(key<keys[b]) {
        return -1;
    }
    if(keys[e]<key) {
        return e+1;
    }
    --b;
    ++e;
    int m;
    while(b+1!=e) {
        m=b+((e-b)>>1);
        if(keys[m]<key) {
            b=m;
        } else {
            e=m;

        }
    }
    return e;
}
//改进：使用二分搜索找到插入的位置
void insertSortWithBisearch(int* x,int n) {
    int i, j;
    int t,p;
    for(i = 1; i < n; i++) {
        t=x[i];
        p=binarySearchForInsert(x,0,i-1,t);
        if(p<0) {
            p=0;
        }
        for(j = i; j >p; j--)
            x[j] = x[j-1];
        x[j] = t;
    }

}




////////////////////////////////////////////
/*
QUICKSORTS
快速排序
*/

//Simplest version, Lomuto partitioning
//!By default stack size, n>=50000 will lead stackoverflow
//Set "-Wl,--stack,268435456" to "Other linker setting" of build option
void qsortLomuto(int* x,int l, int u) {
    if(l >= u)
        return;
    //m stands for the index that <= pivot
    int m=l;
    //Use the lowest index as pivot
    for(int i = l+1; i <= u; i++)
        if(x[l] > x[i])
            swap(x,++m, i);
    swap(x,l, m);
    qsortLomuto(x,l, m-1);
    qsortLomuto(x,m+1, u);
}
void quickSortLomuto(int* x,int n) {
    qsortLomuto(x,0,n-1);
}



void qsortLomuto2(int* x,const int l, const int u) {
    if(l >= u)
        return;
    int p=l;
    int pivot=x[p];
    for(int i = l+1; i <= u; i++)
        if(pivot > x[i]) {
            swap(x,p, i);
            ++p;
        }
    x[p]=pivot;

    //Print the result of current iteration
    for(int i = l; i < p; i++) {
        printf("%d ",x[i]);
    }
    printf("[%d] ",x[p]);
    for(int i = p+1; i <=u; i++) {
        printf("%d ",x[i]);
    }
    printf("\n");

    qsortLomuto2(x,l, p-1);
    qsortLomuto2(x,p+1, u);
}

void quickSortLomuto2(int* x,const int n) {
    qsortLomuto2(x,0,n-1);
}

//!TODO incorrect
void qsortForDup(int* x,int l,int u) {
    if(l>=u)
        return;

    int m=u+1;//for --
    int n=m;
    int pivot = x[l];
    for(int i=u; i>=l; i--) {
        while(x[i]<pivot) i--;
        if(x[i]==pivot)
            swap(x, --m,i);
        else { //a[i]>pivot
            swap(x,--n,i);
            swap(x,--m,i);
        }
    }

    //Print the result of current iteration
    for(int i = l; i < m; i++) {
        printf("%d ",x[i]);
    }
    printf("[");
    for(int i = m; i < n; i++) {
        printf("%d ",x[i]);
    }
    printf("]");
    for(int i = n; i <=u; i++) {
        printf("%d ",x[i]);
    }
    printf("\n");

    qsortForDup(x,l,m-1);
    qsortForDup(x,n,u);
}

void quickSortForDup(int* a,int n) {
    qsortForDup(a,0,n-1);
}


//Sedgewick's version of Lomuto, with sentinel
void qsortSedgewick(int* x,int l, int u) {
    if(l >= u)
        return;
    int i, m;
    m = i = u+1; //sentinel
    do {
        do i--;
        while(x[i] < x[l]);
        swap(x,--m, i);
    } while(i > l);
    qsortSedgewick(x,l, m-1);
    qsortSedgewick(x,m+1, u);
}
void quickSortSedgewick(int* x,int n) {
    qsortSedgewick(x,0,n-1);
}
/* Two-way partitioning */
void qsortTwoWayPartition(int* x,const int l, const int u) {
    int mid=partition(x,l,u);
    if(mid<0) return;
//    printf("partition = %d\n",mid);
    qsortTwoWayPartition(x,l, mid-1);
    qsortTwoWayPartition(x,mid+1, u);
}
void quickSortTwoWayPartition(int* x,int n) {
    qsortTwoWayPartition(x,0,n-1);
}


//Randomly choose pivot
//not found or no need to swap, return -1
int partitionFinal(int*x,const int l,const int u) {
    if(l >= u)
        return -1;
    swap(x,l, randint(l, u));//optimize
    int pivot = x[l]; //l stands for pivot's index
    int i = l;
    int j = u+1; //Reduce compare operation in the loop
    while(true) {
//Must do i++ before while. So even all values are the same,
//it will choose a middle place for partition
        do i++; //i must >= l+1
        while(i <= u && x[i] < pivot);
        //i may > u after loop, so the final pivot place cannot use i

        //no need check left border j>=l, because x[l]=pivot as guard
        do j--;
        while(x[j] > pivot);
        if(i >= j)  //The minimal j=l, and now x[j]==pivot; so j==l<i
            break;
        swap(x,i, j);
    }
//Place pivot to the write place
//if j==l, no need to swap, pivot is already in the correct place
    if(l!=j)
        swap(x,l, j);
    return j;
}

/* qsort3 + randomization + isort small subarrays + swap inline */

void qsortFinal(int* x,int l, int u) {
    static const int cutoff=50;
    if(u - l < cutoff) //小于时直接退出！！
        return;
    int mid=partitionFinal(x,l,u);
    qsortFinal(x,l, mid-1);
    qsortFinal(x,mid+1, u);
}
void _fastcall quickSortFinal(int* x,int n) {
    //小于时直接退出！！
    qsortFinal(x,0,n-1);
    //小于一定数量时，使用插入排序
    insertSort2(x,n);
}




//not found or no need to swap, return -1
int partition(int*x,const int l,const int u) {
    if(l >= u)
        return -1;
    int pivot = x[l]; //l stands for pivot's index
    int i = l;
    int j = u+1; //Reduce compare operation in the loop
    while(true) {
//Must do i++ before while. So even all values are the same,
//it will choose a middle place for partition
        do i++;
        while(i <= u && x[i] < pivot);
        //no need to check left border j>=l, because x[l]=pivot
        do j--;
        while(x[j] > pivot);
        if(i >= j)
            break;
        swap(x,i, j);
    }
//Place pivot to the write place
//if j==l, no need to swap, pivot is already in the correct place
    if(l!=j)
        swap(x,l, j);
    return j;
}

//Not use swap func, but use x[i] as dynamic tmp var
//not found or no need to swap, return -1
int partition3(int*x,const int l,const int u) {
    if(l >= u)
        return -1;
    const int pivot = x[l]; //l stands for pivot's index
    int i = l;
    int j = u+1;
    while(true) {
        do j--;
        while(x[j] > pivot);
        //Must check
        if(i>=j)
            break;
        x[i]=x[j];

        //Must check i<=u
        do i++;
        while(i <= u && x[i] < pivot);
        if(i>=j)
            break;
        x[j]=x[i];
    }
//Place pivot to the right place
    x[j]=pivot;
    return j;
}

void qsortTwoWayPartition3(int* x,const int l, const int u) {
    int p=partition3(x,l,u);
    if(p<0)
        return;
    printf("partition = %d\n",p);
    qsortTwoWayPartition3(x,l, p-1);
    qsortTwoWayPartition3(x,p+1, u);
}
void quickSortTwoWayPartition3(int* x,int n) {
    qsortTwoWayPartition3(x,0,n-1);
}

//!Easy to understand and implement
//not found or no need to swap, return -1
int partition2(int*x,int low,int high) {
    if(low >= high)
        return -1;
//Backup first x[low]
    int pivot = x[low];
    while(low < high) {
//1) Must consider right pointer first
//
//2) "=" will cause bad partition (worst case: all values are the same),
//but still have to use it.
//If only "<", right pointer will not move when
//the first value equals to pivot (worst case: all values are the same),
//so the "while(low<hight)" loop cannot exit
        while(low < high && pivot <= x[high]) --high;
//As tmp variable, x[low] stores current element which <=pivot
//worst case, high=low
        x[low] = x[high];
//Have to use "=". Same reason
//worst case, high=low, the loop will not be executed
        while(low < high && x[low] <= pivot) ++low;
//As tmp, x[high] stores current element which >=pivot
        x[high] = x[low];
    }
//Place pivot to correct place
    x[low] = pivot;
    return low;
}


void qsortTwoWayPartition2(int* x,const int l, const int u) {
    int p=partition2(x,l,u);
    if(p<0)
        return;
    printf("partition = %d\n",p);
    qsortTwoWayPartition2(x,l, p-1);
    qsortTwoWayPartition2(x,p+1, u);
}
void quickSortTwoWayPartition2(int* x,int n) {
    qsortTwoWayPartition2(x,0,n-1);
}


//worst case, need 2*(n-1) partitions
void quickSortNonRecursive(int*x,int n) {
//    int c=2;
    //
    int tail=0;

//int st[30000];
    int *st=(int*)malloc(2*(n-1)*sizeof(int));


    int low,high,mid;
    st[tail++]=0;
    st[tail++]=n-1;
    while(0<tail) {
        high=st[--tail];
        low=st[--tail];
//        printf("pop low=%d,high=%d\n",low,high);
        mid=partition(x,low,high);
        if(low<mid-1) {
//                c+=2;
//            printf("push low=%d,high=%d\n",low,mid-1);
            st[tail++]=low;
            st[tail++]=mid-1;
        }
        if(mid+1<high) {
//                c+=2;
//            printf("push low=%d,high=%d\n",mid+1,high);
            st[tail++]=mid+1;
            st[tail++]=high;
        }
    }
    free(st);


//    printf("%d\n",c);
}

void quickSortNonRecursive2(int*x,int n) {
    int tail=0;
    int *st=(int*)malloc(2*(n-1)*sizeof(int)); //最多划分个数n-1，即最差情况
    int low,high;
    int i,j,pivot;
    st[tail++]=0;
    st[tail++]=n-1;
    while(0<tail) {
        high=st[--tail];
        low=st[--tail];
        if(low<high) {
            swap(x,low, randint(low, high));
            pivot = x[low];
            i = low;
            j = high+1;
            while(true) {
                do i++;
                while(i <= high && x[i] < pivot);
                do j--;
                //don't need check j>=l, because x[l]=pivot
                while(x[j] > pivot);
                if(i >= j)
                    break;
                swap(x,i, j);
            }
            if(low!=j)//can not use i here, because i may equal to u
                swap(x,low, j);
            if(low<j-1) {
                st[tail++]=low;
                st[tail++]=j-1;
            }
            if(j+1<high) {
                st[tail++]=j+1;
                st[tail++]=high;
            }
        }
    }
    free(st);
}

/* selection 选择排序*/
void selectSort(int* x,int n) {
    int i, j, m;
    for(i = 0; i < n; i++) {
        m=i;
        for(j = i+1; j < n; j++)
            if(x[j] < x[m])
                m=j;
        if(i!=m)
            swap(x,i, m);
    }
}

void selectSortMinMax(int *r,int n) {
    int i,j, minIdx,maxIdx;
    for(i=0 ; i <n/2; i++) {
        minIdx = i;
        maxIdx = i;
        for(j= i+1; j< n-i; j++) {
            if(r[j] > r[maxIdx]) {
                maxIdx = j ;
            }  else if(r[j]< r[minIdx]) {
                minIdx = j ;
            }
        }
//        printf("i=%d,min=%d,max=%d\n",i,minIdx,maxIdx);

        if(minIdx!=i) {
            swap(r,minIdx,i);
            //The first swap may affect the second swap
            if(maxIdx==i) {
                maxIdx=minIdx;
            }
        }
//        printArray(r,n);

        if(maxIdx!=(n-i-1)) {
            swap(r,maxIdx,n-i-1);
        }
//        printArray(r,n);
    }
}

/*希尔排序*/
void shellSort(int* x,int n) {
    int i, j, h;
//找到合适的初始步长
    for(h = 1; h < n; h = 3*h + 1)
        ;
    //
    for(;;) {
        h /= 3;
        if(h < 1) break;
        for(i = h; i < n; i++) {
            for(j = i; j >= h; j -= h) {
                if(x[j-h] < x[j]) break;
                swap(x,j-h, j);
            }
        }
    }
}

void shellSort2(int* x,int n) {
    int i, j, d;
//calc max delta
    for(d = 1; d < n; d *=2);

    do { //i starts from delta(d)
        for(i = d; i < n; i++)
            for(j = i; j >= d&&x[j-d] > x[j]; j -= d)  //j-d, so j>=d
                swap(x,j-d, j);
        d/=2;
    } while(d>0);
}

void shellSort3(int* x,int n) {
    int i, j, d, t;
    for(d = 1; d < n; d *=2);
    do {
        for(i = d; i < n; i++) {
            for(j = i,t = x[i];  j>=d&&x[j-d]>t;  j-=d)
                x[j]=x[j-d];
            x[j]=t;
        }
        d/=2;
    } while(d>0);
}

void shellSort4(int* x,int n) {
    int i, j, d,t;
    for(d = n/2; d >0; d /=2)
        for(i=d; i<n; ++i) {
            for(j=i,t=x[i]; j>=d&&x[j-d]>t; j-=d)
                x[j]=x[j-d];
            x[j]=t;
        }
}

/*
HEAP SORTS

*/

//Top down
//index starts from 0
//2*i+1, 2*i+2
//n is total nodes of current heap
void siftdown(int* x,int i, int n) {
    int c=2*i+1; //left child
    while(c<n) {
        if(c+1 <n && x[c+1] > x[c])//Find the larger one of children
            c++;
        if(x[i] > x[c]) //如果大于大的也退出
            break;
        swap(x,i, c);
        i = c;
        c = 2*i+1;
    }
}
void siftdownMin(int* x,int i, int n) {
    int c=2*i+1; //left child
    while(c<n) {
        if(c+1 <n && x[c+1] < x[c])
            c++;
        if(x[i] < x[c])
            break;
        swap(x,i, c);
        i = c;
        c = 2*i+1;
    }
}
//Place max value as the last element of current heap
void siftdown2(int a[], int i, int n) {
    int temp = a[i];
    int j = 2 * i + 1;
    while(j < n) {
        if(j + 1 < n && a[j + 1] > a[j])
            j++;

        if(a[j] <= temp)
            break;

        a[i] = a[j];     //把较小的子结点往上移动,替换它的父结点
        i = j;
        j = 2 * i + 1;
    }
    a[i] = temp; //move to final place
}
void heapSort(int* x,int n) {
    int i;
    for(i = n/2-1; i >= 0; i--)
        siftdown(x,i, n); //Top down, not consider leaf, faster
    for(i = n-1; i >= 1; i--) { //current heap nodes to adjust
        swap(x,0,i); //swap with first element in array
        siftdown(x,0,i);
    }
}

void heapSort2(int* x,int n) {
    int i;
    for(i = n/2-1; i >= 0; i--)
        siftdown2(x,i, n); //Top down, not consider leaf, faster
    for(i = n-1; i >= 1; i--) { //current heap nodes to adjust
        swap(x,0,i); //swap with first element in array
        siftdown2(x,0,i);
    }
}






////////////////////////////////////////
//Bottom up
//void siftupIdxFromOne(int* x,int u) {
//    int i=u, p;
//    for(;;) {
//        if(i == 1) //1表示根，浪费一个0位置的元素
//            break;
//        p = i / 2;
//        if(x[p] >= x[i])
//            break;
//        swap(x,p, i);
//        i = p;
//    }
//}
void siftdownIdxFromOne2(int* x,int l, int u) { /* More C-ish version of 1 */
    int i, c;
    for(i = l; (c = 2*i) <= u; i = c) {
        if(c+1 <= u && x[c+1] > x[c])
            c++;
        if(x[i] > x[c])
            break;
        swap(x,i, c);
    }
}
//Top down
//index starts from 1
//2*i, 2*i+1
//r is rightmost index
void siftdownIdxFromOne(int* x,int i, int n) {
    int c=2*i; //left child
    while(c<=n) {
//        printf("<%d> has left child <%d>\n",i,c);
        if(c+1 <= n && x[c+1] > x[c]) {//Find the larger one of children
//            printf("<%d> is larger than <%d>\n",c+1,c);
            c++;
        }
        if(x[i] > x[c]) //如果大于大的也退出
            break;
//        printf("Swap <%d> with <%d>\n",i,c);
        swap(x,i, c);
//        printArray(x,n+1);
        i = c;
        c = 2*i;
    }
}

//!TODO Not pass testSortMain
//void heapSortIdxFromOne2(int* x,int n) {
//    int i;
//    for(i = 2; i <= n; i++)
//        siftupIdxFromOne(x,i);
//    for(i = n; i >= 2; i--) {
//        swap(x,1, i);
//        siftdownIdxFromOne(x,1, i);
//    }
//}
//index starts from 1, so x-- first
void heapSortIdxFromOne(int* x,int n) {
    int i;
    --x;
    //Top down, not consider leaf, faster
    for(i = n/2; i >= 1; i--)
        siftdownIdxFromOne(x,i, n);
    for(i = n; i >= 2; i--) {
        swap(x,1, i);
        siftdownIdxFromOne(x,1, i-1);
    }
    ++x;
}
void siftdown4(int* x,int l, int u) { /* replace swap with assignments */
    int i, c, p;
    int t;
    t = x[l];
    i = l;
    for(;;) {
        c = 2*i;
        if(c > u)
            break;
        if(c+1 <= u && x[c+1] > x[c])
            c++;
        x[i] = x[c];
        i = c;
    }
    x[i] = t;
    for(;;) {
        p = i/2;
        if(p < l)
            break;
        if(x[p] > x[i])
            break;
        t=x[i];
        x[i]=x[p];
        x[p]=t;
        i = p;
    }
}
///////////////////////////////////////

void siftdown3(int* x,int l, int u) { /* push to bottom, then back up */
    int i=l, c, p;
    for(;;) {
        c = 2*i;
        if(c > u)
            break;
        if(c+1 <= u && x[c+1] > x[c])
            c++;
        //省略,在后面从下到上过程中纠正，这样提高速度
//              if (x[i] > x[c])
//          break;
        swap(x,i, c);
        i = c;
    }
    //?????
    for(;;) {
        p = i/2;
        if(p < l)
            break;
        if(x[p] > x[i])
            break;
        swap(x,p, i);
        i = p;
    }
}

void heapSort3(int* x,int n) {
    int i;
    x--;
    for(i = n/2; i >= 1; i--)
        siftdown3(x,i, n);
    for(i = n; i >= 2; i--) {
        swap(x,1, i);
        siftdown3(x,1, i-1);
    }
    x++;
}


void heapSort4(int* x,int n) {
    int i;
    x--;
    for(i = n/2; i >= 1; i--)
        siftdown4(x,i, n);
    for(i = n; i >= 2; i--) {
        swap(x,1, i);
        siftdown4(x,1, i-1);
    }
    x++;
}

//////////////////////////////////////////////////////////////////////////
//冒泡排序，稳定
void bubbleSort1(int* x,int n) {
    for(int i=n-1; i>0; --i) { //n-1次迭代
        for(int j=0; j<i; ++j) {
            if(x[j]>x[j+1]) {
                swap(x,j,j+1);
            }
        }
    }
}
//使用标记改进
//!慢于普通情况
void bubbleSortWithFlag(int* x,int n) {
    bool isChanged=true;
    for(int i=n-1; i>0&&isChanged; --i) { //n-1次迭代
        isChanged=false;
        for(int j=0; j<i; ++j) {
            if(x[j]>x[j+1]) {
                isChanged=true;
                swap(x,j,j+1);
            }
        }
    }
}
void bubbleSortWithPos(int r[], int n) {
    int i= n-1;  //初始时,最后位置保持不变
    while(i>0) {
        int pos=0; //每趟开始时,无记录交换
        for(int j=0; j<i; j++)
            if(r[j]> r[j+1]) {
                pos= j; //记录交换的位置
                swap(r,j,j+1);
            }
        i= pos; //为下一趟排序作准备
    }
}
void bubbleSortWithTwoDirs(int r[], int n) {
    int low = 0;
    int high= n-1;
    int i;
    while(low < high) {
        for(i=low; i< high; ++i)  //正向冒泡,找到最大者
            if(r[i]> r[i+1])
                swap(r,i,i+1);
        --high;                 //Modify right border
        for(i=high; i>low; --i)  //反向冒泡,找到最小者
            if(r[i]<r[i-1])
                swap(r,i,i-1);
        ++low;                  //Modify left border
    }
}
void bubbleSortWithTwoDirsAndPos(int r[], int n) {
    int low = 0;
    int high= n-1;
    int i,lPos,rPos;
    while(low < high) {
        rPos=0;
//        rPos=high-1; //make sure it will move
        for(i=low; i< high; ++i)  //正向冒泡,找到最大者
            if(r[i]> r[i+1]) {
                rPos=i;
                swap(r,i,i+1);
            }
        high=rPos; //Modify right border
        lPos=n-1;
//        lPos=low+1; //make sure it will move
        for(i=high; i>low; --i)  //反向冒泡,找到最小者
            if(r[i]<r[i-1]) {
                lPos=i;
                swap(r,i,i-1);
            }
        low=lPos; //Modify left border
//        printf("low=%d,high=%d\n",low,high);
    }
}

/**
归并排序
**/
void mergeSortedArray(int* a, int first, int mid, int last, int* tmp) {
    int i = first; // i是第一段序列的下标
    int j = mid + 1; // j是第二段序列的下标
    int k = first; // k是临时存放合并序列的下标
    // 扫描第一段和第二段序列，直到有一个扫描结束
    while(i <= mid && j <= last)
        // 判断第一段和第二段取出的数哪个更小，将其存入合并序列，并继续向下扫描
        if(a[i] <= a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];

    // 若第一段序列还没扫描完，将其全部复制到合并序列
    while(i <= mid) tmp[k++] = a[i++];

    // 若第二段序列还没扫描完，将其全部复制到合并序列
    while(j <= last) tmp[k++] = a[j++];

    // 将合并序列复制到原始序列中
    for(k = first; k<= last; k++)
        a[k] = tmp[k];

//    printArray(array,last-first+1);
}

//Bottom up, from 1 to n/2
void mergeBottomUp(int* a, int gap, int length, int* tmp) {
    int i = 0;
    // 归并gap长度的两个相邻子表
    for(i = 0; i + 2 * gap - 1 < length; i += 2 * gap)
        mergeSortedArray(a, i, i + gap - 1, i + 2 * gap - 1, tmp);

    // 余下的两个子表，其中一个长度小于gap
    if(i + gap - 1 < length)
        mergeSortedArray(a, i, i + gap - 1, length - 1, tmp);
}

void mergeSortBottomUp(int* a,int n) {
    int* result=(int*)calloc(n,sizeof(int));
    for(int gap = 1; gap < n; gap = 2 * gap)
        mergeBottomUp(a, gap, n, result);
    free(result);
}

//Top down, recursive
//From n/2 to 1
void mergeSortTopDownCore(int a[], int first, int last, int temp[]) {
    if(first < last) {
        int mid = (first + last) / 2;
        mergeSortTopDownCore(a, first, mid, temp);    //左边有序
        mergeSortTopDownCore(a, mid + 1, last, temp); //右边有序
        mergeSortedArray(a, first, mid, last, temp); //再将二个有序数列合并
    }
}

void mergeSortTopDown(int* a, int n) {
    int *p = new int[n];
    mergeSortTopDownCore(a, 0, n - 1, p);
    delete[] p;
}

//将有序数组a[]和b[]合并到c[]中
//O(n)
void mergeSortedArray2(int a[], int n, int b[], int m, int c[]) {
    int i, j, k;
    i = j = k = 0;
    while(i < n && j < m)
        if(a[i] < b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    while(i < n)
        c[k++] = a[i++];
    while(j < m)
        c[k++] = b[j++];
}



/**
位图排序
用于非负、非重复整数，分布广，数量大的情况
每个整数只出现一次的情况
**/
//#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
inline void set(int*a,int i) {
    a[i>>SHIFT] |= (1<<(i & MASK));
}
inline void clr(int*a,int i) {
    a[i>>SHIFT] &= ~(1<<(i & MASK));
}
inline int  test(int*a,int i) {
    return a[i>>SHIFT] & (1<<(i & MASK));
}
//max为最大的正整数
void bitSortNoDuplicatePositiveInteger(int *x,int n,int max) {
    int* a=(int*)calloc((1+(max>>SHIFT)),sizeof(int));
    //数组结合的大小
    for(int i = 0; i < n; i++)
        set(a,x[i]);
    int j=0;
    for(int i = 0; i <=max; i++)
        if(test(a,i)) {
            x[j++]=i;
        }

}
//TODO 每个整数出现多次的情况，用多位表示
/**
基数排序
m:整数最大的数字数
**/
void radixSortForPositiveInteger(int* x,int n,int m,int d) {
    typedef std::list<int> Bucket;
    typedef std::vector<Bucket*> Queue;
    int i,j,k;
    Bucket::iterator itr;
    Queue q(d);
    for(i=0; i<d; ++i)
        q[i]=new Bucket;
    int* w=new int[m];
    w[0]=1;
    for(i=1; i<m; ++i)
        w[i]=w[i-1]*d;
    for(i=0; i<m; ++i) {
        //清空每个桶
        for(j=0; j<d; ++j)
            q[j]->clear();
        for(j=0; j<n; ++j)
            q[(x[j]/w[i])%d]->push_back(x[j]);
        for(j=0,k=0; j<d; ++j)
            for(itr=q[j]->begin(); itr!=q[j]->end(); ++itr)
                x[k++]=*itr;
    }
/////////////////////////////////////
    for(int i=0; i<d; ++i)
        delete q[i];
    delete[] w;
}


/////////////////////////////////////////////



class radixNode {
public:
    radixNode *pre;
    radixNode *next;
    int data;
    radixNode():pre(NULL),next(NULL),data(0) {
    }
    radixNode(int d):pre(NULL),next(NULL),data(d) {
    }
};



void radixPass(radixNode* a[],int size,int count) {
    int i=0,j=0;
    std::queue<radixNode*> q[10];
    for(i=0; i<size; i++) {
        int temp=a[i]->data;
        for(j=0; j<count; j++)
            temp/=10;
        temp%=10;
        q[temp].push(a[i]);
    }
    i=0;
    while(q[i].empty()) i++;
    radixNode *root=q[i].front();
    q[i].pop();
    radixNode* p=root;
    i=0;
    j=0;
    a[j++]=root;
    while(i<10) {
        while(!q[i].empty()) {
            p->next=q[i].front();
            a[j++]=q[i].front();
            q[i].pop();
            p=p->next;
        }
        i++;
    }
}
void radixSort(radixNode* a[],int size) {
    int i=0,sum=1;
    for(i=0; i<size; i++) {
        int t=a[i]->data,p=0;
        while(t!=0) {
            p++;
            t/=10;
        }
        if(p>sum) sum=p;
    }
    for(i=0; i<sum; i++)
        radixPass(a,size,i);
}


//////////////////////////////////////////
//Show details
void createHeap(int* a,int n,int h,int &compare,int &move) {
    int i=h,j=2*h+1;
    int temp=a[h];
    move+=2;
    while(j<n) {
        if(j<n-1&&a[j]<a[j+1]) {
            compare++;
            j++;
        }
        if(temp>=a[j]) {
            compare++;
            break;
        } else {
            move++;
            a[i]=a[j];
            i=j;
            j=2*j+1;
        }
    }
    a[i]=temp;
}
void heapSortShowingDetail(int * table, int n) {
    int compare=0,move=0,i;
    for(i=(n-1)/2; i>=0; i--)
        createHeap(table,n,i,compare,move);
    for(i=n-1; i>0; i--) {
        swap(table,0,i);
        move+=3;
        createHeap(table,i,0,compare,move);
    }
    std::cout<<"  堆排序的比较次数为:"<<std::setw(5)<<compare<<"    移动次数为:"<<std::setw(5)<<move<<std::endl;
    printArray(table,n);
}


void quickSortPass(int *a,const int low,const int high,int &compare,int &move) {
    int i=low,j=high;
    int temp;

    if(i>=j) {
        return;
    }
    temp=a[low];
    while(i<j) {
        while(i<j&&temp<a[j]) {
            j--;
            compare++;
        }
        if(i<j) {
            move++;
            a[i]=a[j];
            i++;
        }
        while(i<j&&a[i]<temp) {
            i++;
            compare++;
        }
        if(i<j) {
            move++;
            a[j]=a[i];
            j--;
        }
    }
    a[i]=temp;
    move++;
    quickSortPass(a,low,i-1,compare,move);
    quickSortPass(a,i+1,high,compare,move);
}
void quickSortShowingDetail(int * table, int n) {
    int compare=0,move=0;
    quickSortPass(table,0,n-1,compare,move);
    std::cout<<"快速排序的比较次数为:"<<std::setw(5)<<compare<<"    移动次数为:"<<std::setw(5)<<move<<"     "<<std::setw(5)<<compare+move<<std::endl;
//    display(table,n);
}
void bubbleSortShowingDetail(int * table, int n) {
    int compare=0,move=0,i,j;
    for(i=0; i<n-1; i++)
        for(j=0; j<n-1-i; j++) {
            compare++;
            if(table[j]>table[j+1]) {
                swap(table,j,j+1);
                move+=3;
            }
        }
    std::cout<<"冒泡排序的比较次数为:"<<std::setw(5)<<compare<<"    移动次数为:"<<std::setw(5)<<move<<"     "<<std::setw(5)<<compare+move<<std::endl;
//    display(table,n);
}

void selectSortShowingDetail(int * table, int n) {
    int compare=0,move=0,i,j;
    for(i=0; i<n-1; i++) {
        int minIdx=i;
        for(j=i; j<n; j++) {
            compare++;
            if(table[j]<table[minIdx])
                minIdx=j;
        }
        if(i!=minIdx) {
            swap(table,i,minIdx);
            move+=3;
        }
    }
    std::cout<<"选择排序的比较次数为:"<<std::setw(5)<<compare<<"    移动次数为:"<<std::setw(5)<<move<<"     "<<std::setw(5)<<compare+move<<std::endl;
//    display(table,n);
}

void shellSortShowingDetail(int* table, int n) {
    int compare=0,move=0,i;

    int j,m,k,span,numOfd=0,nt=n;
    int *d=new int[n/2];
    while(nt>1) {
        nt/=2;
        d[numOfd++]=nt;
    }
    int temp;
    for(m=0; m<numOfd; m++) {
        span=d[m];
        for(k=0; k<span; k++) {
            for(i=k; i<n-span; i+=span) {
                temp=table[i+span];
                j=i;
                while(j>-1&&temp<=table[j]) {
                    compare++;
                    move++;
                    table[j+span]=table[j];
                    j-=span;
                }
                table[j+span]=temp;
                move+=2;
            }
        }
    }
//    std::cout<<"希尔排序的比较次数为:"<<compare<<"    移动次数为:"<<std::setw(5)<<move<<"     "<<std::setw(5)<<compare+move<<std::endl;
    std::cout<<"希尔排序的比较次数为:"<<std::setw(5)<<compare<<"    移动次数为:"<<std::setw(5)<<move<<"     "<<std::setw(5)<<compare+move<<std::endl;
//    display(table,n);
}


void insertSortShowingDetail(int *table, int n) {
    int compare=0,move=0,i,j;

    int temp;
    for(i=0; i<n-1; i++) {
        temp=table[i+1];
        j=i;
        compare++;//在while中必有一次比较
        while(j>=0&&table[j]>temp) {
            compare++;
            move++;
            table[j+1]=table[j];
            j--;
        }
        table[j+1]=temp;
        move+=2;
    }
    std::cout<<"插入排序的比较次数为:"<<std::setw(5)<<compare<<"    移动次数为:"<<std::setw(5)<<move<<"     "<<std::setw(5)<<compare+move<<std::endl;
//    display(table,n);
}

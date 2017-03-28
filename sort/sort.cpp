#include "sort.h"
#include "../random/random.h"


//最简单的插入排序
/* Simplest insertion sort */
void insertSort1(int* x,int n) {
    int i, j;
    for (i = 1; i < n; i++)
        for (j = i; j > 0 && x[j-1] > x[j]; j--)
            swap(x,j-1, j);
}
/* Write swap function inline */
void insertSort2(int* x,int n) {
    int i, j;
    int t;
    for (i = 1; i < n; i++)
        for (j = i; j > 0 && x[j-1] > x[j]; j--) {
            t = x[j];
            x[j] = x[j-1];
            x[j-1] = t;
        }
}
//去除交换
/* Move assignments to and from t out of loop */
void insertSort3(int* x,int n) {
    int i, j;
    int t;
    for (i = 1; i < n; i++) {
        //method2
        t = x[i];
        for (j = i; j > 0 && x[j-1] > t; j--)
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
    for (i = 1; i < n; i++) {
        t=x[i];
        p=binarySearchForInsert(x,0,i-1,t);
        if(p<0) {
            p=0;
        }
        for (j = i; j >p; j--)
            x[j] = x[j-1];
        x[j] = t;
    }

}




////////////////////////////////////////////
/*
QUICKSORTS
快速排序
*/

/* Simplest version, Lomuto partitioning
递归
分治策略
*/
void qsortLomuto(int* x,int l, int u) {
    if (l >= u)
        return;
    //m stands for the index that <= pivot
    int m=l;
    //Use the lowest index as pivot
    for (int i = l+1; i <= u; i++)
        if (x[l] > x[i])
            swap(x,++m, i);
    swap(x,l, m);
    qsortLomuto(x,l, m-1);
    qsortLomuto(x,m+1, u);
}
void quickSortLomuto(int* x,int n) {
    qsortLomuto(x,0,n-1);
}



void qsortLomuto2(int* x,const int l, const int u) {
    if (l >= u)
        return;
    int p=l;
    int pivot=x[p];
    for (int i = l+1; i <= u; i++)
        if (pivot > x[i]) {
            swap(x,p, i);
            ++p;
        }
    x[p]=pivot;

    //Print the result of current iteration
    for (int i = l; i < p; i++) {
        printf("%d ",x[i]);
    }
    printf("[%d] ",x[p]);
    for (int i = p+1; i <=u; i++) {
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
    for (int i = l; i < m; i++) {
        printf("%d ",x[i]);
    }
    printf("[");
    for (int i = m; i < n; i++) {
        printf("%d ",x[i]);
    }
    printf("]");
    for (int i = n; i <=u; i++) {
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
    if (l >= u)
        return;
    int i, m;
    m = i = u+1; //sentinel
    do {
        do i--;
        while (x[i] < x[l]);
        swap(x,--m, i);
    } while (i > l);
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
    printf("partition = %d\n",mid);
    qsortTwoWayPartition(x,l, mid-1);
    qsortTwoWayPartition(x,mid+1, u);
}
void quickSortTwoWayPartition(int* x,int n) {
    qsortTwoWayPartition(x,0,n-1);
}


//Randomly choose pivot
int partitionFinal(int*x,const int l,const int u) {
    if (l >= u)
        return -1;
    swap(x,l, randint(l, u));//optimize
    int pivot = x[l]; //l stands for pivot's index
    int i = l;
    int j = u+1; //Reduce compare operation in the loop
    while (true) {
//Must do i++ before while. So even all values are the same,
//it will choose a middle place for partition
        do i++; //i must >= l+1
        while (i <= u && x[i] < pivot);
        //i may > u after loop, so the final pivot place cannot use i

        //no need check left border j>=l, because x[l]=pivot as guard
        do j--;
        while (x[j] > pivot);
        if (i >= j) //The minimal j=l, and now x[j]==pivot; so j==l<i
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
    if (u - l < cutoff)//小于时直接退出！！
        return;
    int mid=partitionFinal(x,l,u);
    qsortFinal(x,l, mid-1);
    qsortFinal(x,mid+1, u);
}
void _fastcall quickSortFinal(int* x,int n) {
    //小于时直接退出！！
    qsortFinal(x,0,n-1);
    //小于一定数量时，使用插入排序
    insertSort3(x,n);
}





int partition(int*x,const int l,const int u) {
    if (l >= u)
        return -1;
    int pivot = x[l]; //l stands for pivot's index
    int i = l;
    int j = u+1; //Reduce compare operation in the loop
    while (true) {
//Must do i++ before while. So even all values are the same,
//it will choose a middle place for partition
        do i++;
        while (i <= u && x[i] < pivot);
        //no need to check left border j>=l, because x[l]=pivot
        do j--;
        while (x[j] > pivot);
        if (i >= j)
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
int partition3(int*x,const int l,const int u) {
    if (l >= u)
        return -1;
    const int pivot = x[l]; //l stands for pivot's index
    int i = l;
    int j = u+1;
    while (true) {
        do j--;
        while (x[j] > pivot);
        //Must check
        if(i>=j)
            break;
        x[i]=x[j];

        //Must check i<=u
        do i++;
        while (i <= u && x[i] < pivot);
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


int partition2(int*x,int low,int high) {
    if (low >= high)
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
        while(low < high && pivot <= x[high]) {
            --high;
        }
//As tmp variable, x[low] stores current element which <=pivot
//worst case, high=low
        x[low] = x[high];
//Have to use "=". Same reason
//worst case, high=low, the loop will not be executed
        while(low < high && x[low] <= pivot) {
            ++low;
        }
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
            while (true) {
                do i++;
                while (i <= high && x[i] < pivot);
                do j--;
                //don't need check j>=l, because x[l]=pivot
                while (x[j] > pivot);
                if (i >= j)
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
    for (i = 0; i < n; i++) {
        m=i;
        for (j = i+1; j < n; j++)
            if (x[j] < x[m])
                m=j;
        if(i!=m)
            swap(x,i, m);
    }
}


/*希尔排序*/
void shellSort(int* x,int n) {
    int i, j, h;
//找到合适的初始步长
    for (h = 1; h < n; h = 3*h + 1)
        ;
    //
    for (;;) {
        h /= 3;
        if (h < 1) break;
        for (i = h; i < n; i++) {
            for (j = i; j >= h; j -= h) {
                if (x[j-h] < x[j]) break;
                swap(x,j-h, j);
            }
        }
    }
}

void shellSort2(int* x,int n) {
    int i, j, d;
//calc max delta
    for (d = 1; d < n; d *=2);

    do { //i starts from delta(d)
       for (i = d; i < n; i++)
            for (j = i; j >= d&&x[j-d] > x[j]; j -= d) //j-d, so j>=d
                    swap(x,j-d, j);
        d/=2;
    }while(d>0);
}

void shellSort3(int* x,int n) {
    int i, j, d, t;
    for (d = 1; d < n; d *=2);
    do {
       for (i = d; i < n; i++) {
            for (j = i,t = x[i];  j>=d&&x[j-d]>t;  j-=d)
                x[j]=x[j-d];
            x[j]=t;
        }
        d/=2;
    }while(d>0);
}

/*
HEAP SORTS

*/
//自底向上
void siftup(int* x,int u) {
    int i=u, p;
    for (;;) {
        if (i == 1)//1表示根，浪费一个0位置的元素
            break;
        p = i / 2;
        if (x[p] >= x[i])
            break;
        swap(x,p, i);
        i = p;
    }
}
//自顶向下
void siftdown1(int* x,int l, int u) {
    int i=l, c;
    for (;;) {
        c = 2*i;
        if (c > u)//没有子节点
            break;
        if (c+1 <= u && x[c+1] > x[c])//找出两个孩子中大的
            c++;
        if (x[i] > x[c])//如果大于大的也退出
            break;
        //
        swap(x,i, c);
        i = c;
    }
}

void siftdown1b(int* x,int l, int u) { /* More C-ish version of 1 */
    int i, c;
    for (i = l; (c = 2*i) <= u; i = c) {
        if (c+1 <= u && x[c+1] > x[c])
            c++;
        if (x[i] > x[c])
            break;
        swap(x,i, c);
    }
}

void heapSort1(int* x,int n) {
    int i;
    x--;//!使得x'[1]=x[0]，节省了一个空间
    //自底向上建堆
    for (i = 2; i <= n; i++)
        siftup(x,i);
    //
    for (i = n; i >= 2; i--) {
        swap(x,1, i);
        siftdown1(x,1, i-1);
    }
    x++;
}

void heapSort2(int* x,int n) {
    int i;
    x--;
    //自顶向下建堆，不考虑叶节点，速度更快！！
    for (i = n/2; i >= 1; i--)
        siftdown1(x,i, n);
    for (i = n; i >= 2; i--) {
        swap(x,1, i);
        siftdown1(x,1, i-1);
    }
    x++;
}
///////////////////////////////////////

void siftdown3(int* x,int l, int u) { /* push to bottom, then back up */
    int i=l, c, p;
    for (;;) {
        c = 2*i;
        if (c > u)
            break;
        if (c+1 <= u && x[c+1] > x[c])
            c++;
        //省略,在后面从下到上过程中纠正，这样提高速度
//				if (x[i] > x[c])
//			break;
        swap(x,i, c);
        i = c;
    }
    //?????
    for (;;) {
        p = i/2;
        if (p < l)
            break;
        if (x[p] > x[i])
            break;
        swap(x,p, i);
        i = p;
    }
}

void heapSort3(int* x,int n) {
    int i;
    x--;
    for (i = n/2; i >= 1; i--)
        siftdown3(x,i, n);
    for (i = n; i >= 2; i--) {
        swap(x,1, i);
        siftdown3(x,1, i-1);
    }
    x++;
}

void siftdown4(int* x,int l, int u) { /* replace swap with assignments */
    int i, c, p;
    int t;
    t = x[l];
    i = l;
    for (;;) {
        c = 2*i;
        if (c > u)
            break;
        if (c+1 <= u && x[c+1] > x[c])
            c++;
        x[i] = x[c];
        i = c;
    }
    x[i] = t;
    for (;;) {
        p = i/2;
        if (p < l)
            break;
        if (x[p] > x[i])
            break;
        t=x[i];
        x[i]=x[p];
        x[p]=t;
        i = p;
    }
}

void heapSort4(int* x,int n) {
    int i;
    x--;
    for (i = n/2; i >= 1; i--)
        siftdown4(x,i, n);
    for (i = n; i >= 2; i--) {
        swap(x,1, i);
        siftdown4(x,1, i-1);
    }
    x++;
}


//////////////////////////////////////////////////////////////////////////
//
// Heap Sort, start from index 0
void siftdownMinHeap(int *h,int i,int n) {
    int t;
    while(i*2+1<n) {
        if(h[i]>h[i*2+1])//choose the min of parent and left child
            t=i*2+1;
        else
            t=i;
        if(i*2+2<n&&h[t]>h[i*2+2])
            t=i*2+2;
        if(t!=i) {
            swapInt(&h[t],&h[i]);
            i=t;
        } else break;
    }
}
void siftupMinHeap(int*h,int i) { //bottom-up, only compare with parent
    while(i)
        if(h[i]<h[(i-1)/2]) {
            swapInt(&h[i],&h[(i-1)/2]);
            i=(i-1)/2;
        } else
            break;
}

void siftdownMaxHeap(int *h,int i,int n) {
    int t;
    while(i*2+1<n) {
        if(h[i]<h[i*2+1])//choose the min of parent and left child
            t=i*2+1;
        else
            t=i;
        if(i*2+2<n&&h[t]<h[i*2+2])
            t=i*2+2;
        if(t!=i) {
            swapInt(&h[t],&h[i]);
            i=t;
        } else break;
    }
}
void siftupMaxHeap(int*h,int i) { //bottom-up, only compare with parent
    while(i)
        if(h[i]>h[(i-1)/2]) {
            swapInt(&h[i],&h[(i-1)/2]);
            i=(i-1)/2;
        } else
            break;
}


int deletemax(int*h,int n) {
    int v=h[0];
    h[0]=h[n-1];
//    printf("[%d %d], ",v,h[0]);
    siftdownMinHeap(h,0,n-1);
    return v;
}
//void deletemax2(int*h,int n) {
//    swapInt(&h[0],&h[n-1]);
//    siftdown(h,0,--n);
//}
void heapSortByMinHeap(int*h,int n) {
    int i;
    for(i=n/2-1; i>=0; --i)
        siftdownMinHeap(h,i,n);
    for(i=n-1; i>=0; --i) {
        printf("%d ",h[0]);
        h[0]=h[i];
        siftdownMinHeap(h,0,i);
    }
//        printf("%d ",deletemax(h,i));
    printf("\n");
}
void heapSortByMaxHeap(int*h,int n) {
    int i;
    for(i=n/2-1; i>=0; --i)
        siftdownMaxHeap(h,i,n);
    while(n>1) {
        swapInt(&h[0],&h[n-1]);
        siftdownMaxHeap(h,0,--n);
    }
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
/**
归并排序
**/
void merge(int* array, int* array2, int low, int mid, int high) {
    int i = low; // i是第一段序列的下标
    int j = mid + 1; // j是第二段序列的下标
    int k = low; // k是临时存放合并序列的下标
    // 扫描第一段和第二段序列，直到有一个扫描结束
    while (i <= mid && j <= high)
        // 判断第一段和第二段取出的数哪个更小，将其存入合并序列，并继续向下扫描
        if (array[i] <= array[j])
            array2[k++] = array[i++];
        else
            array2[k++] = array[j++];

    // 若第一段序列还没扫描完，将其全部复制到合并序列
    while (i <= mid) array2[k++] = array[i++];

    // 若第二段序列还没扫描完，将其全部复制到合并序列
    while (j <= high) array2[k++] = array[j++];

    // 将合并序列复制到原始序列中
    for (k = low; k<= high; k++)
        array[k] = array2[k];

//    printArray(array,high-low+1);
}

void mergePass(int* array, int* array2, int gap, int length) {
    int i = 0;

    // 归并gap长度的两个相邻子表
    for (i = 0; i + 2 * gap - 1 < length; i = i + 2 * gap)
        merge(array,array2, i, i + gap - 1, i + 2 * gap - 1);

    // 余下两个子表，后者长度小于gap
    if (i + gap - 1 < length)
        merge(array,array2, i, i + gap - 1, length - 1);
}

void mergeSort(int* list,int n) {
    int* result=(int*)calloc(n,sizeof(int));
    for (int gap = 1; gap < n; gap = 2 * gap)
        mergePass(list,result, gap, n);
    free(result);
}

//void mergeSort2(int *x,int n) {
//    int* res=new int[n];
//    for(int len=1; len<=n; len<<=1) {
//        mergePass(x,res,n,len);
////        printArray(res,n);
//        len<<=1;
//        mergePass(res,x,n,len);
////        printArray(x,n);
//    }
//    delete[] res;
//}

//void mergeTwoSortedArray(int*x,int xn,int*y,int yn,int*res) {
//
//}
/**
位图排序
用于非负、非重复整数，分布广，数量大的情况
每个整数只出现一次的情况
**/
//#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
inline void set(int*a,int i) {
    a[i>>SHIFT] |=  (1<<(i & MASK));
}
inline void clr(int*a,int i) {
    a[i>>SHIFT] &= ~(1<<(i & MASK));
}
inline int  test(int*a,int i) {
    return a[i>>SHIFT] &   (1<<(i & MASK));
}
//max为最大的正整数
void bitSortNoDuplicatePositiveInteger(int *x,int n,int max) {
    int* a=(int*)calloc((1+(max>>SHIFT)),sizeof(int));
    //数组结合的大小
    for (int i = 0; i < n; i++)
        set(a,x[i]);
    int j=0;
    for (int i = 0; i <=max; i++)
        if (test(a,i)) {
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
    while(q[i].empty())	i++;
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

//2.10 Ѱ�������е����ֵ����Сֵ
//
//1�����Խ��߿����������������⡣
//����Ҫ�Ƚ�N�Σ���Ҫ�Ƚ�2*N�Ρ�
//
//2�����ǿ����������顣
//ÿһ���н�С�ķ���ߣ��ϴ���ұߡ� N/2�Ρ�
//����λ�Ƚ�N/2�Σ��ҵ���Сֵ��
//ż��λ�Ƚ�N/2�Σ��ҵ����ֵ��
//�ܵıȽϴ�����1.5N��
//ȱ�㣺�ƻ���ԭ���顣
//
//3��ά����������min��max��
//ȡ������������Ƚ�1�Ρ�
//��С�ĺ�min�Ƚϣ������Ƿ����min��
//ͬ������max��
//�ɼ��������������Ƚ�3�Ρ�
//�ܵıȽϴ�����1.5N
//�ŵ㣺�����ƻ�ԭ�������顣
//
//4������˼��
#include <iostream>
using namespace std;
//�ݹ�ʵ��
//����
void maxmin(int a[],int low,int high,int& max,int& min) { //������Ϊ������ǿ������
    int k, max1,min1,max2,min2;
    if(high-low==1||high-low==0) {
        a[low]>a[high]? (max = a[low], min = a[high]):(max = a[high], min = a[low]);
    } else {
        k=(high+low)/2;
        maxmin(a,low,k,max1,min1);
        maxmin(a,k+1,high,max2,min2);
        //һ��Ƚ�����
        max=max1>max2? max1:max2;
        min=min1<min2? min1:min2;
    }
}
void MaxMin2(int *a,int n,int& max,int& min) {
    max=min=a[n-1];
    if((n&0x1)!=0)
        --n;

    for(int i=0; i<n-1; i+=2)
        if(a[i]>a[i+1]) {
            max=a[i]>max?a[i]:max;
            min=a[i+1]<min?a[i+1]:min;
        } else {
            max=a[i+1]>max?a[i+1]:max;
            min=a[i]<min?a[i]:min;
        }

}
void testMaxInInArray() {
    int max,min;
    int data[]= {8,3,6,2,1,9,4,5,7};
    int num=sizeof(data)/sizeof(data[0]);
//    maxmin(data,0,num-1,max,min);
    MaxMin2(data,num,max,min);
    cout<<"���ֵ:"<<max<<endl;
    cout<<"��Сֵ:"<<min<<endl;
}
//
//���Ӷȷ�����
//
//f(2) = 1;
//f(n) = 2*f(n/2) + 2; (ע��һ����Ҫ�Ƚ�����)
//�����Ƴ�f(n) = 1.5*n -2;
//�ɼ��ܵıȽϴ�����Ȼû�м��١�

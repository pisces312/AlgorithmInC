#include<iostream>
#include<assert.h>
#include"LinearList.h"
using namespace std;
namespace LinearList {

int josephus(int n,int s,int d) {
    LinearList* ring=LinearList::create(n);
    cout<<"ring:\t";
    ring->output();
    int i=s-1,j,k=n;
    while(k>1) {
        j=0;
        for(; j<d;) {
            i=i%n+1;
            if(ring->get(i)!=0)
                j++;
        }
        cout<<ring->get(i)<<" is out.\n";
        ring->set(i,0);
        k--;
        cout<<"ring:\n";
        ring->output();
    }
    i=1;
    while(i<=n&&ring->get(i)==0) {
        i++;
    }
    return ring->get(i);

}
bool isCorrect(int n,int s,int d) {
    if(n>s&&s>0&&d>0) return true;
    return false;
}
int test() {
    cout<<"test\n";
    LinearList list1(10);
    list1.insert(1);
    list1.insert(30);
    list1.insert(10);
    list1.remove(30);
    list1.output();



    /////////////////////////////////////
    int n=10,s=1,d=3;
    cout<<"Josephus问题\n";
    //
//    cout<<"请分别输入\n人数,从第几个开始,每次数几个人:";
//    do {
//        cin>>n>>s>>d;
//    } while(!isCorrect(n,s,d));
    //
    int finalPerson=josephus(n,s,d);
    assert(finalPerson==4);
    cout<<"The final person is "<<finalPerson<<endl;
    return 0;
}
}

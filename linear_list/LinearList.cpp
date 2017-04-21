#include"LinearList.h"
#include<iostream>
#include<cstring>
//#include<stdlib.h>
#include<iomanip>
using namespace std;
namespace LinearList {
//[EFFC++]member initialization
LinearList::LinearList(int n):table(new int[n]),capacity(n),actualLen(0) {
}
LinearList::LinearList(const LinearList& list):table(new int[list.capacity]),capacity(list.capacity),actualLen(list.actualLen) {
    memcpy(table,list.table,actualLen*sizeof(int));
}
LinearList::~LinearList() {
    delete []table;
    table=NULL;
}
//
//
const LinearList& LinearList::operator=(const LinearList& list) {
    capacity=list.capacity;
    actualLen=list.actualLen;
    table=new int[list.capacity];
    memcpy(table,list.table,actualLen*sizeof(int));
    return *this;
}
bool LinearList::isEmpty() const {
    return actualLen==0;
}
bool LinearList::isFull() const {
    return actualLen>=capacity;
}
inline int LinearList::length() const {
    return actualLen;
}
//XXX, value itself may be -1
int LinearList::get(int i) const {
    if(i>0&&i<=actualLen)
        return table[i-1];
    return -1;
}
bool LinearList::set(int i,int k) {
    if(i>0&&i<=actualLen+1) {
        table[i-1]=k;
        if(actualLen==0) actualLen++;
        return true;
    }
    return false;
}
int LinearList::search(int k) {
    int i=1;
    while(i<=length()&&get(i)!=k)
        i++;
    if(i<=length())
        return i;
    return 0;
}
bool LinearList::insert(int i,int k) {
    if(isFull()) {
            return false;
//        if(capacity<=0) {
//            capacity=1;
//            actualLen=0;
//            table=new int[1];
//        } else {
//            capacity*=2;
//        }
    } else {
        if(i<=0) i=1;
        if(i>actualLen) i=actualLen+1;
        for(int j=actualLen-1; j>=i-1; j--)
            table[j+1]=table[j];
        table[i-1]=k;
        actualLen++;

        return true;
    }
}
bool LinearList::insert(int k) {
    return insert(length()+1,k);
}
bool LinearList::remove(int k) {
    if(!isEmpty()) {
        int i=search(k);
        for(int j=i; j<length(); j++)
            set(j,get(j+1));
        actualLen--;
        return true;
    }
    return false;
}
void LinearList::output() {
    int l=0;
    for(int i=0; i<actualLen; i++) {
        cout<<setw(4)<<table[i]<<" ";
        if(++l%10==0) cout<<endl;

    }
    cout<<endl;
}
//
//
LinearList* LinearList::create(int n) {
    LinearList* list=new LinearList(n);
    for(int i=1; i<=n; i++) {
        if(!list->insert(i))
            return NULL;
    }
    return list;
}
}

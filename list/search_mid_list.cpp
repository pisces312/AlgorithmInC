#include <iostream>
#include<list>
using namespace std;
void searchMidNode(list<int> *aList) {
    if (aList==NULL) {
        return;
    }
    if (aList->empty()) {
        return;
    }
    //��֤����һ��Ԫ��
    list<int>::iterator itr=aList->begin();
    //�����ٶ�
    list<int>::iterator itr2=aList->begin();
    while (itr2!=aList->end()) {

        itr2++;
        if (itr2!=aList->end()) {
            itr2++;
            itr++;
        } else {
            break;
        }

    }
//ż���������
    if ((aList->size()&0x1)==0) {
//        itr.
        itr--;
        cout<<*itr<<endl;
        itr++;
//        cout<<*(itr-1)<<endl;
    }

    cout<<*itr<<endl;

}
int testSearchMidList() {
    list<int> *aList=new list<int>;
    aList->push_back(3);
    aList->push_back(1);
    aList->push_back(5);
    aList->push_back(6);
    aList->push_back(2);
    aList->push_back(7);
    searchMidNode(aList);
//    cout << "Hello world!" << endl;
    return 0;
}

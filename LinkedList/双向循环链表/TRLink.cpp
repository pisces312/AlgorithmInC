#include"TRLink.h"
void main()
{
	TRLink list(10);
	list.insertafter(10,3);
	list.insertbefore(1,11);
	list.output();
	cout<<list.index(10)->data<<endl;
	list.remove(1);
	cout<<list.index(1)->data<<endl;
	cout<<list.index(2)->data<<endl;


	list.output(20);
	cout<<list.length()<<endl;
	list.reverseoutput();
	list.output(list.head);
	
}
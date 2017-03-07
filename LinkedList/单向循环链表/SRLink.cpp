#include"SRLink.h"
void main()
{
	SRLink list(5);
	cout<<list.get(3)<<endl;
	list.insertafter(5,6);
	list.remove(5);
	list.reverse();
	
	list.output();
	list.output(19);
}
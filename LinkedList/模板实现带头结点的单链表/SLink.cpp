#include"SLink.h"
void main()
{
	SLink<char> s(0);
	s.set(3,'1');
	cout<<s.length()<<endl;
	s.set(2,2);
	cout<<s.get(1)<<endl;
	s.output();
}
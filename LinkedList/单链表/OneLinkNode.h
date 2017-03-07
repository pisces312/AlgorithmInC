#include<iostream.h>
typedef char OneLinkDataType;
class OneLinkNode
{
public:
	OneLinkDataType data;
	OneLinkNode *next;
	OneLinkNode(OneLinkDataType n=' ')
	{
		data=n;
		next=NULL;
	}
};
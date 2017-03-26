#include <stdlib.h>
#include <memory.h>

#include "ListNode.h"
#include "ListNode.internal.h"

ListNode ListNode_Create(void* const data)
{
	ListNode self = calloc(1, sizeof(ListNodeStruct));
	if(NULL != self)
	{
		ListNodeStruct init = { data, NULL, NULL };
		memcpy(self, &init, sizeof(ListNodeStruct));
	}
	return self;
}

void ListNode_Destroy(ListNode self)
{
	free(self);
}

void* ListNode_Data(ListNode self)
{
	return self->data;
}

ListNode ListNode_Prev(ListNode self)
{
	if(NULL == self) return NULL;
	return self->parrent;
}

ListNode ListNode_Next(ListNode self)
{
	if(NULL == self) return NULL;
	return self->child;
}


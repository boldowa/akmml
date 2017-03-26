#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>

#include "List.h"
#include "ListNode.internal.h"

typedef struct ListStruct
{
	ListNode top;
	ListNode tail;
	size_t length;
} ListStruct;

List List_Create(void)
{
	List self = calloc(1, sizeof(ListStruct));
	if(NULL != self)
	{
		ListStruct init = { NULL, NULL, 0 };
		memcpy(self, &init, sizeof(ListStruct));
	}
	return self;
}

void List_Destroy(List self)
{
	ListNode node = self->top;
	ListNode next = NULL;

	/* delete list */
	while(node != NULL)
	{
		next = node->child;
		free(node->data);
		free(node);
		node = next;
	}

	/* delete object */
	free(self);
}

/**
 * Get list size
 */
const size_t List_GetLength(List self)
{
	return self->length;
}

/**
 * Add data to top of list
 */
bool List_PushFront(List self, void* const data)
{
	ListNode node;

	/* Create Node */
	node = ListNode_Create(data);
	if(NULL == node)
	{
		return false;
	}

	/* Update list */
	node->child = self->top;
	if(NULL != self->top) self->top->parrent = node;
	self->top = node;
	if(0 == self->length)
	{
		self->tail = self->top;
	}
	self->length++;
	return true;
}

/**
 * Add data to tail of list
 */
bool List_PushBack(List self, void* const data)
{
	ListNode node;

	/* Create Node */
	node = ListNode_Create(data);
	if(NULL == node)
	{
		return false;
	}

	/* Update list */
	node->parrent = self->tail;
	if(NULL != self->tail) self->tail->child = node;
	self->tail = node;
	if(0 == self->length)
	{
		self->top = self->tail;
	}
	self->length++;
	return true;
}

/**
 * Get data from top of list
 */
void* const List_PopFront(List self)
{
	ListNode node;
	void* data;

	if(NULL == self->top)
	{
		return NULL;
	}

	/* Get data */
	data = (void*)self->top->data;

	/* Destroy Node */
	node = self->top->child;
	ListNode_Destroy(self->top);

	/* Update list */
	if(NULL != node) node->parrent = NULL;
	self->top = node;
	self->length--;
	if(0 == self->length)
	{
		self->tail = self->top;
	}

	return data;
}

/**
 * Get data from tail of list
 */
void* const List_PopBack(List self)
{
	ListNode node;
	void* data;

	if(NULL == self->tail)
	{
		return NULL;
	}

	/* Get data */
	data = (void*)self->tail->data;

	/* Destroy Node */
	node = self->tail->parrent;
	ListNode_Destroy(self->tail);

	/* Update list */
	if(NULL != node) node->child = NULL;
	self->tail = node;
	self->length--;
	if(0 == self->length)
	{
		self->top = self->tail;
	}

	return data;
}

/**
 * Get data index
 */
void* const List_Index(List self, const size_t inx)
{
	ListNode node;
	size_t i;

	if(self->top == NULL)
	{
		return NULL;
	}
	if(0 > inx)
	{
		return NULL;
	}
	if(self->length <= inx)
	{
		return NULL;
	}

	/* Seek from top */
	if(self->length/2 > inx)
	{
		node = self->top;
		for(i=0; i != inx; i++)
		{
			node = node->child;
		}
		return node->data;
	}

	/* Seek from tail */
	node = self->tail;
	for(i=self->length-1; i != inx; i--)
	{
		node = node->parrent;
	}
	return node->data;

}

/**
 * Get top of List
 */
ListNode List_Begin(List self)
{
	if(NULL == self) return NULL;
	return self->top;
}

/**
 * Get tail of List
 */
ListNode List_End(List self)
{
	if(NULL == self) return NULL;
	return self->tail;
}


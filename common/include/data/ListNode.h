#pragma once

/**********************************************************************
 *
 * ListNode is responsible for ...
 *
 **********************************************************************/

typedef struct ListNodeStruct * ListNode;

ListNode ListNode_Create(void* const);
void ListNode_Destroy(ListNode);
void* ListNode_Data(ListNode);
ListNode ListNode_Prev(ListNode);
ListNode ListNode_Next(ListNode);


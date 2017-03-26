#pragma once

/**********************************************************************
 *
 * ListNode is responsible for ...
 *
 **********************************************************************/

typedef struct ListNodeStruct * ListNode;

ListNode ListNode_Create(void* const);
void ListNode_Destroy(ListNode);


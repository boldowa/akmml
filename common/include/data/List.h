#pragma once

#include "ListNode.h"

/**********************************************************************
 *
 * List is responsible for ...
 *
 **********************************************************************/

/**
 * Class object
 */
typedef struct ListStruct * List;

/**
 * Create list instance
 */
List List_Create(void);

/**
 * Delete list instance
 */
void List_Destroy(List);

/**
 * Get list size
 */
const size_t List_GetLength(List);

/**
 * Add data to top of list
 */
bool List_PushFront(List, void* const);

/**
 * Add data to tail of list
 */
bool List_PushBack(List, void* const);

/**
 * Get data from top of list
 */
void* const List_PopFront(List);

/**
 * Get data from tail of list
 */
void* const List_PopBack(List);

/**
 * Get data index
 */
void* const List_Index(List, const size_t);


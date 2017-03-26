extern "C"
{
#include "ListNode.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(ListNode)
{
	ListNode listNode;
	int* data;

	void setup()
	{
		data = (int*)calloc(1, sizeof(int));
		*data = 10;
		listNode = ListNode_Create(data);
	}

	void teardown()
	{
		free(data);
		ListNode_Destroy(listNode);
	}
};

TEST(ListNode, Create)
{
	/*-----------------------------------*/
	/* Nothing to do                     */
	/* This test checks only memory leak */
	/*-----------------------------------*/
}

TEST(ListNode, Data)
{
	int* d = (int*)ListNode_Data(listNode);
	LONGS_EQUAL(10, *d);
}

TEST(ListNode, Iterator)
{
	POINTERS_EQUAL(NULL, ListNode_Prev(listNode));
	POINTERS_EQUAL(NULL, ListNode_Next(listNode));

	POINTERS_EQUAL(NULL, ListNode_Prev(NULL));
	POINTERS_EQUAL(NULL, ListNode_Next(NULL));
}


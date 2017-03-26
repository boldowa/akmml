extern "C"
{
#include "List.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(List)
{
	List list;

	void setup()
	{
		list = List_Create();
	}

	void teardown()
	{
		/* Add some data */
		List_PushBack(list, calloc(1, sizeof(int)));
		List_PushBack(list, calloc(1, sizeof(int)));
		List_Destroy(list);
	}
};

TEST(List, Create)
{
	LONGS_EQUAL(0, List_GetLength(list));
}

TEST(List, PushFront)
{
	static const int Val1 = 5;
	static const int Val2 = 200;
	int* v;
	size_t len;

	/* get default status */
	len = List_GetLength(list);

	/* Push */
	v = (int*)calloc(1, sizeof(int));
	*v = Val1;
	CHECK(List_PushFront(list, v));
	LONGS_EQUAL(len+1, List_GetLength(list));

	/* Push */
	v = (int*)calloc(1, sizeof(int));
	*v = Val2;
	CHECK(List_PushFront(list, v));
	LONGS_EQUAL(len+2, List_GetLength(list));

	/* value(0) check */
	v = (int*)List_Index(list, 0);
	CHECK_FALSE(NULL == v);
	LONGS_EQUAL(Val2, *v);

	/* value(1) check */
	v = (int*)List_Index(list, 1);
	CHECK_FALSE(NULL == v);
	LONGS_EQUAL(Val1, *v);

	/* Pop */
	v = (int*)List_PopFront(list);
	LONGS_EQUAL(len+1, List_GetLength(list));
	CHECK_FALSE(NULL == v);
	LONGS_EQUAL(Val2, *v);
	free(v);

	/* Pop */
	v = (int*)List_PopFront(list);
	LONGS_EQUAL(len, List_GetLength(list));
	CHECK_FALSE(NULL == v);
	LONGS_EQUAL(Val1, *v);
	free(v);

	while(len != 0)
	{
		free(List_PopFront(list));
		len = List_GetLength(list);
	}

	/* check that can't pop from empty list */
	v = (int*)List_PopFront(list);
	POINTERS_EQUAL(NULL, v);
}

TEST(List, PushBack)
{
	static const int Val1 = 5;
	static const int Val2 = 200;
	int* v;
	size_t len;

	/* get default status */
	len = List_GetLength(list);

	/* Push */
	v = (int*)calloc(1, sizeof(int));
	*v = Val1;
	CHECK(List_PushBack(list, v));
	LONGS_EQUAL(len+1, List_GetLength(list));

	/* Push */
	v = (int*)calloc(1, sizeof(int));
	*v = Val2;
	CHECK(List_PushBack(list, v));
	LONGS_EQUAL(len+2, List_GetLength(list));

	/* value(0) check */
	v = (int*)List_Index(list, 0);
	CHECK_FALSE(NULL == v);
	LONGS_EQUAL(Val1, *v);

	/* value(1) check */
	v = (int*)List_Index(list, 1);
	CHECK_FALSE(NULL == v);
	LONGS_EQUAL(Val2, *v);

	/* Pop */
	v = (int*)List_PopBack(list);
	LONGS_EQUAL(len+1, List_GetLength(list));
	CHECK_FALSE(NULL == v);
	LONGS_EQUAL(Val2, *v);
	free(v);

	/* Pop */
	v = (int*)List_PopBack(list);
	LONGS_EQUAL(len, List_GetLength(list));
	CHECK_FALSE(NULL == v);
	LONGS_EQUAL(Val1, *v);
	free(v);

	while(len != 0)
	{
		free(List_PopBack(list));
		len = List_GetLength(list);
	}

	/* check that can't pop from empty list */
	v = (int*)List_PopBack(list);
	POINTERS_EQUAL(NULL, v);
}

TEST(List, Queue)
{
	static const int Val1 = 5;
	static const int Val2 = 200;
	int* v;
	size_t len;

	/* get default status */
	len = List_GetLength(list);

	/* Enqueue */
	v = (int*)calloc(1, sizeof(int));
	*v = Val1;
	CHECK(List_PushBack(list, v));
	LONGS_EQUAL(len+1, List_GetLength(list));

	/* Enqueue */
	v = (int*)calloc(1, sizeof(int));
	*v = Val2;
	CHECK(List_PushBack(list, v));
	LONGS_EQUAL(len+2, List_GetLength(list));

	/* Dequeue */
	v = (int*)List_PopFront(list);
	LONGS_EQUAL(len+1, List_GetLength(list));
	CHECK_FALSE(NULL == v);
	LONGS_EQUAL(Val1, *v);
	free(v);

	/* Pop */
	v = (int*)List_PopFront(list);
	LONGS_EQUAL(len, List_GetLength(list));
	CHECK_FALSE(NULL == v);
	LONGS_EQUAL(Val2, *v);
	free(v);

	while(len != 0)
	{
		free(List_PopBack(list));
		len = List_GetLength(list);
	}
}

TEST(List, Index)
{
	LONGS_EQUAL(0, List_GetLength(list));
	POINTERS_EQUAL(NULL, List_Index(list, 0));
	POINTERS_EQUAL(NULL, List_Index(list, 1));
	POINTERS_EQUAL(NULL, List_Index(list, -1));
}


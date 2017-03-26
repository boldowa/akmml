/**
 * List node internal 
 */

typedef struct ListNodeStruct
{
	void* const data;
	struct ListNodeStruct *parrent;
	struct ListNodeStruct *child;
} ListNodeStruct;


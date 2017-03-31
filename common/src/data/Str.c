#include <stdlib.h>
#include <string.h>

#include "Str.h"

char* Str_concat(const char* s1, const char* s2)
{
	char* con;
	char* top;

	if(NULL == s1 || NULL == s2) return NULL;

	/* Memory allocation */
	con = calloc(strlen(s1) + strlen(s2) + 1, sizeof(char));
	if(NULL == con)
	{
		return NULL;
	}
	top = con;
	
	/* Connect string */
	strcpy(con, s1);
	con += strlen(s1);
	strcpy(con, s2);

	return top;
}

char* Str_replace(const char* search, const char* replace, const char* target)
{
	char* work = NULL;
	char* top = NULL;
	char* tmp = NULL;
	char* tmp2 = NULL;
	char* find = NULL;
	char* result;

	if(NULL == search || NULL == replace || NULL == target) return NULL;

	/* Empty values fail */
	if(0 == strlen(search)) return NULL;

	/* Init result value(default is "") */
	result = calloc(1, sizeof(char));
	if(NULL == result)
	{
		return NULL;
	}

	/* Copy for work */
	work = calloc(strlen(target)+1, sizeof(char));
	if(NULL == work)
	{
		free(result);
		return NULL;
	}
	strcpy(work, target);
	top = work;
	
	/* Replacement loop */
	while(NULL != (find = strstr(work, search)))
	{
		/* Insert termination code on find point */
		*find = '\0';

		/* Replace 1 : connect with first half */
		tmp = Str_concat(work, replace);
		if(NULL == tmp)
		{
			free(top);
			free(result);
			return NULL;
		}
		work = find;
		work += strlen(search);

		/* Replace 2 : connect with second half */
		tmp2 = Str_concat(result, tmp);
		free(tmp);
		free(result);
		if(NULL == tmp2)
		{
			free(top);
			return NULL;
		}
		result = tmp2;
		tmp2 = NULL;
	}

	/* connect with remainder */
	tmp = Str_concat(result, work);

	/* clean */
	free(result);
	free(top);

	/* return result */
	return tmp;
}


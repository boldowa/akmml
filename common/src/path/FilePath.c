/**
 * File path module
 */
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <setjmp.h>

#include "FilePath.h"

#ifndef MAX_PATH
  #define MAX_PATH 260
#endif

/**
 * Class object
 */
typedef struct FilePathStruct
{
	int placeHolderForHiddenStructElements;
	/* File path */
	char *szPath;

	/* File directory */
	char *szDir;

	/* File name */
	char *szName;

	/* File etension */
	char *szExt;
} FilePathStruct;


/**
 * Create new module object
 */
FilePath FilePath_Create(const char* szPath)
{
	FilePath self = calloc(1, sizeof(FilePathStruct));
	if(NULL != self)
	{
		/* Init */
		self->szPath = self->szDir = self->szName = self->szExt = NULL;

		if(NULL != szPath)
		{
			FilePath_SetPath(self, szPath);
		}
	}
	return self;
}


/**
 * Clone module object
 */
FilePath FilePath_Clone(FilePath self)
{
	FilePath clone = FilePath_Create(self->szPath);
	return clone;
}


/**
 * Delete module object
 */
void FilePath_Destroy(FilePath self)
{
	/* Release string */
	free(self->szPath);
	free(self->szDir);
	free(self->szName);
	free(self->szExt);

	/* Release struct */
	free(self);
}


/**
 * Getters
 */
const char* FilePath_GetPath(FilePath self)
{
	return self->szPath;
}
const char* FilePath_GetDir(FilePath self)
{
	return self->szDir;
}
const char* FilePath_GetName(FilePath self)
{
	return self->szName;
}
const char* FilePath_GetExt(FilePath self)
{
	return self->szExt;
}

/**
 * Setters
 */
void _FilePath_Strcat(jmp_buf *e, char *s1, const char *s2, const int max)
{
	if(max < (strlen(s1)+strlen(s2)))
	{
		longjmp(*e, 1);
	}
	strcat(s1, s2);
}
bool _FilePath_SetPath(FilePath self, const char* szPath)
{
	char* tmp;
	tmp = calloc(strlen(szPath)+1, sizeof(char));
	if(NULL == tmp)
	{
		return false;

	}
	strcpy(tmp, szPath);

	if(NULL != self->szPath)
	{
		free(self->szPath);
	}
	self->szPath = tmp;

	return true;
}
bool FilePath_SetPath(FilePath self, const char* szPath)
{
	const char* dot_pos = NULL;
	const char* slash_pos = NULL;
	size_t len;
	bool isNoDir = false;

	if(MAX_PATH < strlen(szPath))
	{
		return false;
	}

	/* search slash */
	slash_pos = strrchr(szPath, '/');
#ifdef WIN32
	{
		char* bslash_pos = NULL;
		bslash_pos = strrchr(szPath, '\\');
		if((NULL != bslash_pos) && (slash_pos < bslash_pos))
		{
			slash_pos = bslash_pos;
		}
	}
#endif /* WIN32 */
	/* release directory */
	if(NULL != self->szDir)
	{
		free(self->szDir);
		self->szDir = NULL;
	}

	/* set directory */
	len = 0;
	if(NULL != slash_pos)
	{
		len = (size_t)(slash_pos - szPath)+1;
	}
	self->szDir = calloc(len+1, sizeof(char));
	if(NULL == self->szDir)
	{
		return false;

	}
	strncpy(self->szDir, szPath, len);

	if(NULL == slash_pos)
	{
		isNoDir = true;
		slash_pos = szPath;
	}

	/* search dot pos */
	dot_pos = strrchr(szPath, '.');
	if(NULL == dot_pos)
	{
		dot_pos = szPath + strlen(szPath);
	}

	/* release name */
	if(NULL != self->szName)
	{
		free(self->szName);
		self->szName = NULL;
	}

	/* set filename */
	len = (size_t)(dot_pos - slash_pos);
	if(true == isNoDir)
	{
		if(szPath != dot_pos)
		{
			len++;
		}
	}
	if(slash_pos != dot_pos)
	{
		len--;
	}
	self->szName = calloc(len+1, sizeof(char));
	if(NULL == self->szDir)
	{
		return false;
	}
	{
		const char* x = slash_pos;
		if(false == isNoDir)
		{
			x++;
		}
		strncpy(self->szName, x, len);
	}

	/* release extension */
	if(NULL != self->szExt)
	{
		free(self->szExt);
		self->szExt = NULL;
	}

	/* set extension */
	len = strlen(szPath) - (size_t)(dot_pos - szPath);
	if(slash_pos == dot_pos)
	{
		/* Non-extention */
		len = 0;
	}
	if(szPath == dot_pos)
	{
		/* szPath = ".xxx" */
		len = strlen(szPath);
	}
	self->szExt = calloc(len+1, sizeof(char));
	if(NULL == self->szExt)
	{
		return false;

	}
	strncpy(self->szExt, dot_pos, len);

	return _FilePath_SetPath(self, szPath);
}
bool _FilePath_SetPath3(FilePath self, const char* szDir, const char* szName, const char* szExt)
{
	char tmp[MAX_PATH+1];
	jmp_buf e;

	tmp[0] = '\0';

	if(0 == setjmp(e)) /* try */
	{
		_FilePath_Strcat(&e, tmp, szDir, MAX_PATH);
		_FilePath_Strcat(&e, tmp, szName, MAX_PATH);
		_FilePath_Strcat(&e, tmp, szExt, MAX_PATH);
	}
	else /* catch(Exception) */
	{
		return false;
	}

	return _FilePath_SetPath(self, tmp);
}
bool FilePath_SetDir(FilePath self, const char* szDir)
{
	char* tmp;

	tmp = calloc(strlen(szDir)+1, sizeof(char));
	if(NULL == tmp)
	{
		return false;
	}
	strcpy(tmp, szDir);

	if(false == _FilePath_SetPath3(self, tmp, self->szName, self->szExt))
	{
		free(tmp);
		return false;
	}

	if(NULL != self->szDir)
	{
		free(self->szDir);
	}
	self->szDir = tmp;

	return true;
}
bool FilePath_SetName(FilePath self, const char* szName)
{
	char* tmp;

	tmp = calloc(strlen(szName)+1, sizeof(char));
	if(NULL == tmp)
	{
		return false;
	}
	strcpy(tmp, szName);

	if(false == _FilePath_SetPath3(self, self->szDir, tmp, self->szExt))
	{
		free(tmp);
		return false;
	}

	if(NULL != self->szName)
	{
		free(self->szName);
	}
	self->szName = tmp;

	return true;
}
bool FilePath_SetExt(FilePath self, const char* szExt)
{
	char* tmp;

	tmp = calloc(strlen(szExt)+1, sizeof(char));
	if(NULL == tmp)
	{
		return false;
	}
	strcpy(tmp, szExt);

	if(false == _FilePath_SetPath3(self, self->szDir, self->szName, tmp))
	{
		free(tmp);
		return false;
	}

	if(NULL != self->szExt)
	{
		free(self->szExt);
	}
	self->szExt = tmp;

	return true;
}

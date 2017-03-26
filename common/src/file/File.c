#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "FilePath.h"
#include "File.h"
#include "File.protected.h"

File File_Create(const FilePath path)
{
	if(NULL == path)
	{
		return NULL;
	}

	File self = calloc(1, sizeof(FileStruct));
	if(NULL != self)
	{
		FileStruct init = { path, NULL, NULL, 0 };
		memcpy(self, &init, sizeof(FileStruct));
	}
	return self;
}

void File_Destroy(File self)
{
	/* delete member */
	FilePath_Destroy(self->path);
	if(NULL != self->fp) fclose(self->fp);
	free(self->mode);

	/* delete obj */
	free(self);
}

/**
 * Set file mode
 */
void File_SetMode(File self, const char* mode)
{
	if(NULL != self->mode)
	{
		free(self->mode);
	}
	self->mode = calloc(1, strlen(mode)+1);
	strcpy(self->mode, mode);
}

/**
 * Open file
 */
E_File_Open File_Open(File self)
{
	long end_pos;

	if(NULL != self->fp) return File_Open_AlreadyOpen;
	if(NULL == self->mode) return File_Open_NoMode;

	self->fp = fopen(FilePath_GetPath(self->path), self->mode);
	if(NULL == self->fp) return File_Open_CantOpen;

	fseek(self->fp, 0, SEEK_END);
	end_pos = self->size = ftell(self->fp);
	fseek(self->fp, 0, SEEK_SET);
	self->size = end_pos - ftell(self->fp);

	return File_Open_NoError;
}

/**
 * Close file
 */
void File_Close(File self)
{
	if(NULL != self->fp)
	{
		fclose(self->fp);
		self->fp = NULL;
	}
}

/**
 * Get file size
 */
long File_GetSize(File self)
{
	return self->size;
}


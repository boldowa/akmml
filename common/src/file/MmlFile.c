#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "FilePath.h"
#include "File.h"
#include "File.protected.h"
#include "MmlFile.h"

typedef struct MmlFileStruct
{
	File super;
} MmlFileStruct;

MmlFile MmlFile_Create(FilePath path)
{
	File super = NULL;
       
	super = File_Create(path);
	if(NULL == super)
	{
		return NULL;
	}

	MmlFile self = calloc(1, sizeof(MmlFileStruct));
	if(self != NULL)
	{
		File_SetMode(super, "r");
		MmlFileStruct init = { super };
		memcpy(self, &init, sizeof(MmlFileStruct));
	}
	return self;
}

void MmlFile_Destroy(MmlFile self)
{
	File_Destroy(self->super);
	free(self);
}


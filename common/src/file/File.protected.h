#pragma once

/**
 * Class object
 */
typedef struct FileStruct
{
	/* file path */
	const FilePath path;

	/* file pointer */
	FILE *fp;

	/* file mode */
	char* mode;

	/* file size */
	long size;
} FileStruct;

/**
 * Set file mode
 */
void File_SetMode(File, const char*);


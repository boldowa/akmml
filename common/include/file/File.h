#pragma once

/**********************************************************************
 *
 * File is responsible for ...
 *
 **********************************************************************/

/**
 * Class object
 */
typedef struct FileStruct * File;

typedef enum
{
	File_Open_NoError,
	File_Open_AlreadyOpen,
	File_Open_NoMode,
	File_Open_CantOpen,
} E_File_Open;

/**
 * Create file object 
 */
File File_Create(FilePath);
/**
 * Delete file object
 */
void File_Destroy(File);

/**
 * Open file
 */
E_File_Open File_Open(File);

/**
 * Close file
 */
void File_Close(File);

/**
 * Ger file size
 */
long File_GetSize(File);


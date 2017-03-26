#pragma once

/**********************************************************************
 *
 * MmlFile is responsible for ...
 *
 **********************************************************************/

/**
 * Class object
 */
typedef struct MmlFileStruct * MmlFile;

/* Inherit */
#define MmlFile_GetSize(obj) File_GetSize((File)*((unsigned long*)obj))
#define MmlFile_Open(obj) File_Open((File)*((unsigned long*)obj))
#define MmlFile_Close(obj) File_Close((File)*((unsigned long*)obj))

/**
 * Cleate instance
 */
MmlFile MmlFile_Create(FilePath);
/**
 * Delete instance
 */
void MmlFile_Destroy(MmlFile);


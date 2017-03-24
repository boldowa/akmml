/**
 * File path module
 */
#pragma once

/**********************************************************************
 *
 * FilePath is responsible for ...
 *
 **********************************************************************/

/**
 * Class object
 */
typedef struct FilePathStruct * FilePath;

/**
 * Create new module object
 */
FilePath FilePath_Create(const char*);
/**
 * Delete module object
 */
void FilePath_Destroy(FilePath);
/**
 * Clone module object
 */
FilePath FilePath_Clone(FilePath);

/**
 * Getters
 */
const char* FilePath_GetPath(FilePath);
const char* FilePath_GetDir(FilePath);
const char* FilePath_GetName(FilePath);
const char* FilePath_GetExt(FilePath);

/**
 * Setters
 */
bool FilePath_SetPath(FilePath, const char*);
bool FilePath_SetDir(FilePath, const char*);
bool FilePath_SetName(FilePath, const char*);
bool FilePath_SetExt(FilePath, const char*);


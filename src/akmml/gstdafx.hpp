/**
 * Pre compile Header for GCC
 *
 */

#ifndef _GSTDAFX_H
#define _GSTDAFX_H

#define AKMML_VERSION "0.01"

/**
 * Defines...
 *
 */

/* define bool */
#if !defined __cplusplus && !defined bool
 #ifdef _Bool
  typedef _Bool bool;
 #else
  typedef unsigned int bool;
 #endif

 #ifndef true
  #define true 1
 #endif

 #ifndef false
  #define false 0
 #endif
#endif
/* end define bool */

#ifndef MAX_PATH
  #define MAX_PATH 260
#endif

#define STR(var) #var


/**
 * Include files...
 *
 */
#include <cstdint>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <map>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>
#include <dirent.h>

/**
 * macros
 */
/* 通常出力用 */
extern bool vdebug;
#define putdebug(fmt, ...) if(vdebug) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#define putinfo(fmt, ...)             fprintf(stderr, "[INFO ] " fmt "\n", ##__VA_ARGS__)
#define putwarn(fmt, ...)             fprintf(stderr, "[WARN ] " fmt "\n", ##__VA_ARGS__)
#define puterror(fmt, ...)            fprintf(stderr, "[ERROR] " fmt "\n", ##__VA_ARGS__)
#define putfatal(fmt, ...)            fprintf(stderr, "[FATAL] " fmt "\n", ##__VA_ARGS__)
/* mmlエラー出力用 */
#define putmmldebug(date, fname, line, row, message)   if(vdebug) fprintf(stderr, "[DEBUG] %s %s(line=%d, col=%d): %s\n", date, fname, line, row, message)
#define putmmlinfo(date, fname, line, row, message)               fprintf(stderr, "[INFO ] %s %s(line=%d, col=%d): %s\n", date, fname, line, row, message)
#define putmmlwarn(date, fname, line, row, message)               fprintf(stderr, "[WARN ] %s %s(line=%d, col=%d): %s\n", date, fname, line, row, message)
#define putmmlerror(date, fname, line, row, message)              fprintf(stderr, "[ERROR] %s %s(line=%d, col=%d): %s\n", date, fname, line, row, message)
#define putmmlfatal(date, fname, line, row, message)              fprintf(stderr, "[FATAL] %s %s(line=%d, col=%d): %s\n", date, fname, line, row, message)
#define putmmlunknown(date, fname, line, row, message)            fprintf(stderr, "[?????] %s Unknown error code(in %s, %dL) : %s(line=%d, row=%d): %s\n", date, __FILE__, __LINE__, fname, line, row, message)

#define putexception(ec, em) fprintf(stderr, "  [CODE: 0x%8x] %s\n", ec, em);

#endif /* _GSTDAFX_H */


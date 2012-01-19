#ifndef _GZFILE_H
#define _GZFILE_H

/***************************************************************

Uncompress gz file

Input: string type file name, open mode

Output: FILE type File pointer

***************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
FILE *gzFile(const char filename[], const char rw[]);

#ifdef __cplusplus
}
#endif

#endif

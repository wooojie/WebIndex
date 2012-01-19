#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "gzFile.h"

//Uncompress and compress gz file
FILE *gzFile(const char filename[], const char rw[]) /* do not quit */
{
        int     len;
        FILE    *fp;

        if (!strcmp(rw, "r") || !strcmp(rw, "R"))
        {
                if (filename == NULL || !strcmp(filename, "-"))
                {
                        return stdin;
                }

                len = strlen(filename);
                // if (len < FILENAME_MAX - 6
                        // && ((len > 3 && filename[len-3] == '.'
                            // && filename[len-2] == 'g'
                            // && filename[len-1] == 'z')
                         // || (len > 2 && filename[len-2] == '.'
                            // && filename[len-1] == 'Z')))
                // {
                        char command[FILENAME_MAX];
                        sprintf(command, "zcat %s", filename);
                        fp = popen(command, "r");
                // }
                // else
                // {
                        // fp = fopen(filename, "r");
                // }
                if (fp == NULL && !strcmp(rw, "R"))
                {
                        fprintf(stderr, "cannot open file %s for read: %s\n",
                                filename, strerror(errno));
                }
        }
        else if (!strcmp(rw, "w") || !strcmp(rw, "W"))
        {
                if (filename == NULL || !strcmp(filename, "-"))
                {
                        return stdout;
                }
                len = strlen(filename);
                // if (len < FILENAME_MAX - 6
                        // && ((len > 3 && filename[len-3] == '.'
                            // && filename[len-2] == 'g'
                            // && filename[len-1] == 'z')
                         // || (len > 2 && filename[len-2] == '.'
                           // && filename[len-1] == 'Z')))
                // {
                        char command[FILENAME_MAX];
                        sprintf(command, "gzip > %s", filename);
                        fp = popen(command, "w");
                // }
                // else
                // {
                        // fp = fopen(filename, "w");
                // }
                if (fp == NULL && !strcmp(rw, "W"))
                {
                        fprintf(stderr, "cannot open file %s for write: %s\n",
                                filename, strerror(errno));
                }
        }
        else
        {
                fprintf(stderr,
                        "cannot open file %s for write: unknown mode %s\n",
                        filename, rw);
                return NULL;
        }

        return fp;
}

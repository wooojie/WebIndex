#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <iostream>

using namespace std;
/*===========================================================================*/
/* package 5: file and filename utilities.                                   */
/*===========================================================================*/
FILE *open_file(const char filename[], const char rw[]) /* do not quit */
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
                if (len < FILENAME_MAX - 6
                        && ((len > 3 && filename[len-3] == '.'
                            && filename[len-2] == 'g'
                            && filename[len-1] == 'z')
                         || (len > 2 && filename[len-2] == '.'
                            && filename[len-1] == 'Z')))
                {
                        char command[FILENAME_MAX];
                        sprintf(command, "zcat %s", filename);
                        fp = popen(command, "r");
                }
                else
                {
                        fp = fopen(filename, "r");
                }
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
                if (len < FILENAME_MAX - 6
                        && ((len > 3 && filename[len-3] == '.'
                            && filename[len-2] == 'g'
                            && filename[len-1] == 'z')
                         || (len > 2 && filename[len-2] == '.'
                           && filename[len-1] == 'Z')))
                {
                        char command[FILENAME_MAX];
                        sprintf(command, "gzip > %s", filename);
                        fp = popen(command, "w");
                }
                else
                {
                        fp = fopen(filename, "w");
                }
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

main ()
{	
	cout << "////////////////////////////////////////////////////////\n////////\t\tDELIMITER\t\t////////\n////////////////////////////////////////////////////////\n" << endl;

	
	//index reading
	FILE *pFileR = open_file("down1_1800_index.gz", "r");
	FILE *pFileW = fopen("1_800_index.txt", "w");


	size_t cut = 100;
	char * buffer;

	if(pFileW==NULL)

	{
		cout << "write failed" <<endl;
	}

	if (pFileR == NULL) perror ("Error opening file");

	else
 	{
		//fgets (buffer , 4536 , pFileR);
	 	//fputs (buffer , pFileW);
		//fputs (buffer , stdout);

	     	// allocate memory to contain the whole file:
  		buffer = (char*) malloc (cut);
  		if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

 		// copy the file into the buffer:
		fgets (buffer , 4536 , pFileR);

		fputs (buffer , pFileW);
		fputs (buffer , stdout);

	    	fclose (pFileR);
		fclose(pFileW);
   	}

	//data writing
	pFileR = open_file("down1_1800.gz", "r");
	pFileW = fopen("1_800.txt", "w");

	cut = 4536;
 	size_t result;

	if(pFileW==NULL)

	{
		cout << "write failed" <<endl;
	}

	if (pFileR == NULL) perror ("Error opening file");

	else
 	{
		//fgets (buffer , 4536 , pFileR);
	 	//fputs (buffer , pFileW);
		//fputs (buffer , stdout);

	     	// allocate memory to contain the whole file:
  		buffer = (char*) malloc (cut);
  		if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

 		 // copy the file into the buffer:
 		 result = fread (buffer,1,cut,pFileR);
  		if (result != cut) {fputs ("Reading error",stderr); exit (3);}

		fputs (buffer , pFileW);
		fputs (buffer , stdout);

	    	fclose (pFileR);
		fclose(pFileW);
   	}

}

#ifndef _PARSER_H
#define _PARSER_H

/***************************************************************

function to parse urls and pages into words

return value:
  a) >= 0, if success;
  b) -1, if buffer (for words) too small

arguments:
  1) url of page;
  2) page to be parsed;
  3) buffer to store parsed out words and their contexts;
     format: "<WORD> <CONTEXT>\n"
     <CONTEXT>: 'B', bold; 'H', head (h1-h6); 'I', italic;
                'P', plain; 'T', title; 'U', URL.
	4) length of buffer

***************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int parser(char* url, char* doc, char* buf, int blen);

#ifdef __cplusplus
}
#endif

#endif

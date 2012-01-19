#ifndef _JTOOLS_H
#define _JTOOLS_H
/*****************************

Contains some generic tools for character processing

1. split a given string by a specified delimiter 
into a vector containing all the content in original order

1. split a given string by specified delimiter array 
into a vector containing all the content in original order

******************************/
#include <vector>
#include <string.h>
#include <time.h>
#include <map>
#include <string>
#include <stdio.h>


//using namespace std;

/* devide string into pieces by specified delimiter */
int  string_split(const std::string& s, const char c,
	std::vector<std::string>& vs);

/* devide string into pieces by specified delimiter */
int  string_split(const std::string& s, const char c[],
	std::vector<std::string>& vs);

/* devide char arry into pieces by specified delimiter */
int  str_tok(char buff[], const char delm[], char *subs[], const int nsubs);

/* print multimap structure on to the console */
void printMap( std::multimap<std::string, std::string> & myMap );

/* print current time to console  */
void printTime();

#endif

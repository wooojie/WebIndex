#ifndef _JGZDATA_H
#define _JGZDATA_H
/*****************************

Process gz format Data files

1. constructor function manage data loading

2. get index information from JgzIndex, 
	
	unzip gz format Data file, parse the char* into words,
	
	maintain the data for indexing.

3. print out to console

******************************/
#include <string>
#include <map>
#include <vector>
#include "JDocID.h"
#include "JWordMap.h"

using namespace std;

class JgzData
{
private:
	FILE *m_pDataF;
	string m_gzFName;
	
	//filter rule: length >45 or = 1, have number, exlusive word list
	int wordFilter(char* wordpool, multimap<string, string> & htmlMap);

	/* if contains nonalpha character, return false */
	bool badword(const char* s);

	/* exlusive list of words */
	bool exlusiveWord(const char* word);

public:
	JgzData(const char * gzFName)
	:	m_gzFName(gzFName)
	{
		
	}
	
	//uncompress data from gz files, parse html page, filter words, generate ID, build index 
	void process(vector<string> & vIndex, map<string, long int> & mpIndex,JDocID & IDManager, JWordMap & WordMapManager);

	void print();

};
#endif

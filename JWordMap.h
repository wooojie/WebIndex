#ifndef _JWORDMAP_H
#define _JWORDMAP_H

/*****************************

Maintain Words Map in a global scope

1. maintain a map of word and doc ID list

2. implemented using multimap, one word is associate with multiple doc id

3. insertion is implemented by overriden for multiple function,
	single word insertion, a pile of words within single Doc insertion
	
4. query one word for a list of its containing Doc ID

******************************/
#include <map>
#include <string>
#include <vector>
using namespace std;

class JWordMap
{
private:
	//static undefinition bugs until the global variable
	//static multimap<string, long> m_WordMap;
	 multimap< string, string > *m_WordMap;


public:
	JWordMap()
	{
		m_WordMap = new multimap< string, string >;

	}
	
	~JWordMap()
	{
		delete m_WordMap;
	}
	
	//generate Index for word to a Doc
	long insrtHtmlMap(multimap<string, string> & htmlMap, long DocID);
	
	//merge two index together
	long mergeMap(multimap<string, string> & indexMap);

	//alphabetically split into submaps
	long splitMap(multimap<string, string> & subMap, const char* low, const char* up);

	//read index information from file
	long readWordMap(const char * LexFileName, const char * IndexFileName);
	
	//write index format into files
	void writeIndex(const char * LexFileName, const char * IndexFileName);

	//print out the member index on to the console
	void print();

	void clear(){delete m_WordMap;m_WordMap = new multimap< string, string >;}
	
	multimap<string, string> & getMap(){return *m_WordMap;}	
	
};
#endif

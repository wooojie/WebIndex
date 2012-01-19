#ifndef _JGZINDX_H
#define _JGZINDX_H
/*****************************

Process gz format Index files

1. constructor function manage data loading

2. provide index information to JgzData, 
	
	unzip gz format Index file, parse the char* into words,
	
	maintain the data for indexing.

3. print out to console

******************************/

#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class JgzIndx
{
private:
	FILE *m_pIndxF;
	string m_gzFName;
	
	vector<string> m_vIndx;
	map<string, long int> m_mpIndx;
	
	

public:
	JgzIndx(const char * gzFName)
	:	m_gzFName(gzFName)
	{
		m_vIndx.clear();
		initial();
		
	};
	
	/* read index information from example "down1_1800_index.gz" to the JgzIndx */
	void initial();

	/* print to cout */
	void print();
	
	/* write html map to customed file */
	int writeout(const char * filename);
	
	map<string, long int> & getIndexMp(){return m_mpIndx;}
	vector<string> & getIndex(){return m_vIndx;}
};
#endif

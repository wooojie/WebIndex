#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <time.h>
#include <cctype>
#include <cassert>
#include <map>
#include "JgzData.h"
#include "JTools.h"
#include "gzFile.h"
#include "parser.h"

using namespace std;

void JgzData::print()
{
	/* map<string, long int>::const_iterator map_it = m_mpIndxF.begin();
	while (map_it != m_mpIndxF.end())
	{
	cout << map_it->first << ":  " << map_it->second << endl;
	} */ 
}

//uncompress data from gz files, parse html page, filter words, generate ID, build index 
void JgzData::process(vector<string> & vIndex, map<string, long int> & mpIndex, JDocID & IDManager, JWordMap & WordMapManager)
{
	m_pDataF = gzFile(m_gzFName.c_str(), "r");


	for(size_t i=0; i<vIndex.size(); i++)
	{
		size_t cut = mpIndex[vIndex[i]];

		char* htmlCode;
		char* wordpool;
		size_t resultSize;
		size_t tmpcheck;
		
		if (m_pDataF == NULL) 
		perror ("Error opening file");
		else
		{
			/* allocate memory to contain the whole file: */
			htmlCode = (char*) malloc (cut);
			if (htmlCode == NULL) 
			{
				fputs ("Memory error\n",stderr); 
				exit (2);
			}

			/* copy the file into the htmlCode: */
			tmpcheck = fread (htmlCode, 1, cut, m_pDataF);
			if (tmpcheck <= 0) 
			{
				fputs ("Reading error \n",stderr);
				//exit (3);
			}

			wordpool = (char*) malloc (cut);
			if (wordpool == NULL) 
			{
				fputs ("Memory error\n",stderr); 
				exit (2);
			}

			char* tmp;
			tmp = new char[vIndex[i].length() + 1];
			strcpy(tmp, vIndex[i].c_str());
			resultSize = parser(tmp, htmlCode, wordpool, tmpcheck);
			
			multimap<string, string> *pMap = new multimap<string, string>;	
			multimap<string, string> htmlMap = *pMap;
			wordFilter(wordpool, htmlMap);

			
			long DocID = IDManager.generateID(vIndex[i]);
			WordMapManager.insrtHtmlMap(htmlMap, DocID);
			
			delete[] tmp;		
			delete pMap;		
		}
		free (htmlCode);
		free(wordpool);
	}
	fclose (m_pDataF);
}

/* if contains nonalpha character, return false */
bool JgzData::badword(const char* s)
{
	for (int i = 0; s[i]; i++) 
	{
		if (!isalpha(s[i]))
			return true;
	}

	return false;
}

/* building index from  parser words of one html page */
int JgzData::wordFilter(char* wordpool, multimap<string, string> & htmlMap)
{
	
	int count=0;
	int nSub;
	char* sub[20000];
	
	nSub = str_tok(wordpool, "\r\n", sub, 20000);
	if(nSub >= 19998)
		cout <<"nSub too small"<<endl;
	for(int i=0; i<nSub; i++)
	{
		int nSub1;
		char* sub1[250];
		nSub1 = str_tok(sub[i], " \t", sub1, 250);
		if(nSub1 >= 248)
		cout <<"nSub1 too small"<<endl;

		/* checking the bad word in the parser */
		if(!(nSub1!=2 || strlen(sub1[0]) > 45||strlen(sub1[0])==1|| badword(sub1[0])))
		{
			if(!exlusiveWord(sub1[0]))			
			{
				char buffer[200];
				sprintf(buffer, "%d %s", i+1, sub1[1]);
				htmlMap.insert(pair<string, string>(sub1[0], buffer));
			
				count++;
			}
		}		
	
	}

	return count;
}

/* exlusive list of words */
bool JgzData::exlusiveWord(const char* word)
{
	if(!strcmp("and", word))
		return true;
	if(!strcmp("the", word))
		return true;
	if(!strcmp("with", word))
		return true;
	if(!strcmp("for", word))
		return true;
	if(!strcmp("so", word))
		return true;
	if(!strcmp("then", word))
		return true;
	if(!strcmp("will", word))
		return true;
	if(!strcmp("via", word))
		return true;
	if(!strcmp("your", word))
		return true;
	if(!strcmp("you", word))
		return true;
	if(!strcmp("me", word))
		return true;
	if(!strcmp("after", word))
		return true;
	if(!strcmp("other", word))
		return true;
	if(!strcmp("about", word))
		return true;
	if(!strcmp("is", word))
		return true;
	if(!strcmp("are", word))
		return true;
	if(!strcmp("to", word))
		return true;
	if(!strcmp("of", word))
		return true;	
	if(!strcmp("in", word))
		return true;	
	if(!strcmp("on", word))
		return true;
	if(!strcmp("nbsp", word))
		return true;
	if(!strcmp("was", word))
		return true;
	if(!strcmp("www", word))
		return true;
	if(!strcmp("very", word))
		return true;
	if(!strcmp("that", word))
		return true;
	if(!strcmp("she", word))
		return true;
	if(!strcmp("or", word))
		return true;
	if(!strcmp("more", word))
		return true;
	if(!strcmp("just", word))
		return true;
	if(!strcmp("it", word))
		return true;
	if(!strcmp("as", word))
		return true;
	if(!strcmp("by", word))
		return true;
	if(!strcmp("from", word))
		return true;
	if(!strcmp("we", word))
		return true;
	if(!strcmp("us", word))
		return true;
	if(!strcmp("this", word))
		return true;
	if(!strcmp("our", word))
		return true;
	if(!strcmp("at", word))
		return true;
	if(!strcmp("be", word))
		return true;
	if(!strcmp("do", word))
		return true;
	if(!strcmp("all", word))
		return true;
	if(!strcmp("but", word))
		return true;
	if(!strcmp("if", word))
		return true;
	if(!strcmp("my", word))
		return true;
	if(!strcmp("they", word))
		return true;
	if(!strcmp("one", word))
		return true;
	if(!strcmp("an", word))
		return true;
	
	return false;
	
}


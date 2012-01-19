#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <stdlib.h>
#include "JWordMap.h"
#include "JTools.h"

//generate Index for word to a Doc
long JWordMap::insrtHtmlMap(multimap<string, string> & htmlMap, long DocID)
{
	long cn=0;
	multimap<string, string>::iterator map_it = htmlMap.begin();
	typedef multimap<string, string>::size_type sz_type;
	
	while(map_it !=htmlMap.end())
	{
		string word(map_it->first);
		int count = htmlMap.count(map_it->first);//get the frequency of the word
		stringstream sout;
		sout << DocID << " "<<count;
		
		for(int i=0; i!=count; i++)// loop freq times to write up the index format
		{
			sout << " "<<map_it->second;
				
			map_it++;
		}
		string str = sout.str();
		m_WordMap->insert(pair<string, string>(word, str));//hold it in the member variable
		cn++;
	}
	 return cn;
}

//merge two index together
long JWordMap::mergeMap(multimap<string, string> & indexMap)
{	
	long count=0;
	multimap<string, string>::iterator map_it = indexMap.begin();
	while(map_it != indexMap.end())
	{
		string word(map_it->first); 
		string index(map_it->second);
		m_WordMap->insert(pair<string, string>(word, index));
		count++;
		}
	return count;

}

//alphabetically split into submaps
long JWordMap::splitMap(multimap<string, string> & subMap, const char* low, const char* up)
{
	long count=0;
	multimap<string, string>::iterator itlow, itup, it;

	itlow = m_WordMap->lower_bound(low);
	itup = m_WordMap->lower_bound(up);
	for(it = itlow; it!=itup; it++)
	{	
		subMap.insert( pair<string, string>((*it).first, (*it).second) );
		count++;
	}

	return count;
}

//read index information from file
long JWordMap::readWordMap(const char * LexFileName, const char * IndexFileName)
{	
	unsigned long cn=0, uplen=0;
	string upword;
	fstream ifIndex, ifLex;
	ifIndex.open(IndexFileName, ios::binary|ios::in);//read inverted index
	ifLex.open(LexFileName, ios::binary|ios::in);//read lexicon instruction


	while((!ifLex.eof())&&(!ifIndex.eof()))
	{
		char word[100], pstart[240], pend[240];
		ifLex.getline(word, 100, ' ');//read lexicon, get word, start position, end position("hello 0 100")
		ifLex.getline(pstart, 240, ' ');
		ifLex.getline(pend, 240, '\n');
		
		char * buffer;
		int nSub;
	 	char* sub[189124];
		
		unsigned long len,lend,lstart;
		lend= atol(pend);
		lstart = atol(pstart);
		len=lend-lstart;
		if(len>uplen)
		{
			uplen=len;
			upword=word;
		}
		buffer = new char [len];
		ifIndex.read(buffer, len);//read inverted index according to the lexicon infor
		if(strlen(buffer)!=len)
		{	
			buffer[len-1]='\0';//if length is not right, set the last char '\0'
		}
		vector<string> vs;
		nSub = str_tok(buffer, " \n", sub, 189124);//cut the string into pieces
		
		if(nSub >= 189122)
		{
			cout <<"nSub too small"<<endl;
		}

		//regenerate the key(word) and value(Index) for the map, "DocID 2 0 U 1 P"(DocID freq pos context)
		for(int i =0; i<nSub-1;)//loop docid
		{
			string dstr(sub[i]);
			dstr.append(" ");
			dstr.append(sub[i+1]);
			int freq;
			freq = atoi(sub[i+1]);

			for(int j = i+2; j<i+2+freq*2; j++)//loop freq
			{
				dstr.append(" ");
				dstr.append(sub[j]);
			}
			m_WordMap->insert(pair<string, string>(word, dstr) );//insert pair into map member
			i+=(freq*2+2);
			cn++;
		}
		delete buffer;
	}

	ifIndex.close();
	ifLex.close();
	
	cout<<"upword:                                                  "<<upword<<" "<<uplen<<endl;
	return cn;
}

//write index format into files
void JWordMap::writeIndex(const char * LexFileName, const char * IndexFileName)
{
	int start, end;
	fstream ofIndex, ofLex;
	ofIndex.open(IndexFileName, ios::binary|ios::out);//write inverted index in binary mode
	ofLex.open(LexFileName, ios::binary|ios::out);//write lexicon instruction

	typedef multimap< string, string>::size_type sz_type;
	multimap<string, string>::iterator map_it = m_WordMap->begin();
	
	while(map_it != m_WordMap->end() )
	{
		start = ofIndex.tellg();//get the position of begin
		ofLex<< map_it->first<<" " << start;

		sz_type count = m_WordMap->count(map_it->first);//get the number of field for one word

		for(sz_type i=0; i!=count; i++)
		{
			ofIndex << map_it->second<< " ";
			map_it++;
		}

		ofIndex<<endl;
		end = ofIndex.tellg();//get the position of end
		ofLex<< " " << end <<endl;

	}

	ofIndex.close();
	ofLex.close();
}

//print out the member index on to the console
void JWordMap::print()
{
	multimap<string, string>::iterator map_it = m_WordMap->begin();
	typedef multimap<string, string>::size_type sz_type;
	while(map_it != m_WordMap->end())
	{
		cout << map_it->first << " ";
		sz_type count = m_WordMap->count(map_it->first);
		
		for(sz_type i=0; i!=count; i++)
		{
			cout <<map_it->second<<" ";
			
			map_it++;
		}

		cout<<endl;
		
	}
}

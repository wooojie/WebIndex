#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unistd.h>
#include <sys/stat.h>
#include <vector>
#include "gzFile.h"
#include "JgzIndx.h"
#include "JgzData.h"
#include "JDocID.h"
#include "JWordMap.h"
#include "JTools.h"

using namespace std;

void writeAlphIndex(JWordMap & wordMap, int mark, vector<string> & dirList);

int main ()
{	
	cout << "////////////////////////\tSTART HERE\t////////////////////////\n" << endl;
	
	printTime();

	JDocID IDManager;
	JWordMap WordMapManager;
	vector<string> dirList;
	
	/*	get the data file list	*/
	//system("ls ./datset/* > list.txt");											//data sample: smallest
	system("ls ./nz2_merged/*index ./nz2_merged/*data > list.txt");					//data sample: nz2
	//system("ls ./nz10_merged/*index ./nz10_merged/*data > list.txt");				//data sample: nz10

	string filedir;
	vector<string> vFileList;
	ifstream iFileList;
	iFileList.open("list.txt");
	if(iFileList.is_open())
	{
		while(!iFileList.eof())
		{
			getline(iFileList, filedir);
			if(filedir.find("_index")!=string::npos)
			{
				vFileList.push_back(filedir);
			}
		}
	}
	
	/*	process data into index, by the end of loop, every 10 files data processed into a directory
 		holding inverted index in alphabetic order, for example, nz2 data will be processed into the 
		folders ./J10 ./J20 ./J30 ... ./J80 ./J82, under each folder above, we have a_index, a_lex,
		b_index, b_lex, etc. They are holding inverted index and lexicon struction seperately	*/
	for(size_t i=0; i<vFileList.size();i++)
	{
		
		
		JgzIndx indx(vFileList[i].c_str());
		indx.writeout("writesout.txt");

		cout<<vFileList[i]<<endl;
		size_t found = vFileList[i].find("_index");
		//vFileList[i].erase(found, 6);												//data sample: smallest
		vFileList[i].replace(found, 6, "_data");									//data sample: nz2 or nz10
		JgzData data(vFileList[i].c_str());
		cout<<"Processing   "<< vFileList[i] <<endl;
		data.process(indx.getIndex(), indx.getIndexMp(), IDManager, WordMapManager);
		
		cout<<"Completed: Packge   "<<i+1<<endl;

		if(!((i+1) % 30)|| (i==vFileList.size()-1))//every 50 data files write into a folder alphabetically
		{
			char dir[12], dirCmd[12];
			sprintf(dir, "J%d", i+1);//here is debug trash
			sprintf(dirCmd, "mkdir J%d", i+1);
			system(dirCmd);
			writeAlphIndex(WordMapManager, i, dirList);//write the inverted index and lexicon into alphabetic pieces
			WordMapManager.clear();//clear the memory for memory efficiency
		}
	}
	printTime();

	/* merge subindex into final index, within alphabetic order, eg. get all the "a" from sub indexes, and merge to one index */
 	char alph='a';
	for(int i=0; i<26*2; i+=2)
	{
				
		for(size_t j=0; j < dirList.size(); j+=52)//start from a to z
		{
			cout<<"reading data from" << dirList[i+j] <<" "<<dirList[i+j+1] <<endl;
			WordMapManager.readWordMap(dirList[i+j].c_str(), dirList[i+j+1].c_str());
			
		}
		
		char dirL[24], dirI[24];
		sprintf(dirL, "./JData2/%c_lex", alph);										//data sample: nz2
		sprintf(dirI, "./JData2/%c_Index", alph);										//data sample: nz2
		//sprintf(dirL, "./JData10/%c_lex", alph);										//data sample: nz10	
		//sprintf(dirI, "./JData10/%c_Index", alph);										//data sample: nz10
		cout<<"Building Index To "<< dirL<< " "<<dirI<<endl;
		WordMapManager.writeIndex(dirL, dirI);
		WordMapManager.clear();
		alph++;
	}
	cout<<"Index Is Built Up!"<<endl;
	printTime();
}
//write the inverted index and lexicon into alphabetic pieces
void writeAlphIndex(JWordMap & wordMap, int mark, vector<string> & dirList)
{
	char low='a';
	char up;
	for(int i=0; i <26; i++, low++)//start from a to z
	{
		up=low+1;

		char aup[2] = {up, '\0'};
		char alow[2] = {low, '\0'};
		JWordMap subMap;
		wordMap.splitMap(subMap.getMap(),alow, aup);//get all the elements from a to b(not including b) into a subMap
		cout<<"Sub Index "<<low<<" is done"<<endl;
		
		char  lexF[24], IndexF[24];
		sprintf(lexF, "./J%d/%c_lex", mark+1, low);
		sprintf(IndexF, "./J%d/%c_Index", mark+1, low);
		subMap.writeIndex(lexF, IndexF);//write the subMap into lexicon file and index file
		dirList.push_back(lexF);
		dirList.push_back(IndexF);
		
	}
}


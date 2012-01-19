#ifndef _JDOCID_H
#define _JDOCID_H

/*****************************

Maintain Doc ID in a global scope

1. generate ID for url, and return ID

2. generate IDs for multiple Urls

3. query url by a given ID

******************************/
#include <map>
#include <string>
#include <vector>
using namespace std;

class JDocID
{
private:
	//static undefinition bugs until the global variable
	long m_DocID;
	map<long , string> *m_DocMap;

public:
	JDocID()
	{
		m_DocID=0;
		m_DocMap = new map<long, string>;
		
	}
	
	~JDocID()
	{
		delete m_DocMap;
	}

	//generate ID for Doc represented by url
	long  generateID(string urls);
	
	//generate a pile of Doc ID
	vector<long > generateMap(vector<string> v_urls);
	
	//get url from a Doc ID
	string getUrl(long DocID);
};
#endif

#include "JDocID.h"

//generate ID for Doc represented by url
long JDocID::generateID(string urls)
{
	long docID = JDocID::m_DocID;
	(*m_DocMap)[docID] = urls;
	m_DocID++;
	
	return docID;
}

//generate a pile of Doc ID
vector<long> JDocID::generateMap(vector<string> v_urls)
{
	vector<long> vs;
	for(size_t i=0; i<v_urls.size(); i++)
	{
		
		long docID = m_DocID;
		(*m_DocMap)[docID] = v_urls[i];
		m_DocID++;
		vs.push_back(docID);
	}
	
	return vs;
}

//get url from a DocID
string JDocID::getUrl(long DocID)
{
	map<long, string>::iterator map_it = m_DocMap->find(DocID);
	if(map_it != m_DocMap->end())
	return map_it->second;
	else
	return NULL;
}

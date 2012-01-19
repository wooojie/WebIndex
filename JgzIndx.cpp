#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include "JgzIndx.h"
#include "JTools.h"
#include "gzFile.h"

using namespace std;

/* print to cout */
void JgzIndx::print()
{
	map<string, long int>::const_iterator map_it = m_mpIndx.begin();
	while (map_it != m_mpIndx.end())
	{
		cout << map_it->first << ":  " << map_it->second << endl;
		map_it ++;
	}
}

/* write html map to customed file */
int JgzIndx::writeout(const char * filename)
{
	ofstream fOut;
	fOut.open(filename);
	int count=0;
	map<string, long int>::const_iterator map_it = m_mpIndx.begin();
	while (map_it != m_mpIndx.end())
	{
		fOut << map_it->first << "," << map_it->second<<endl;
		count++;
		map_it ++;
	}
	return count;

}

/* read index information from example "down1_1800_index.gz" to the JgzIndx */
void JgzIndx::initial()
{
	m_pIndxF = gzFile(m_gzFName.c_str(), "r");

	char line[1500];
	
	if (m_pIndxF == NULL) 
	perror ("Error opening file");
	else
	{
		while(!feof(m_pIndxF))
		{
			/* get one line of in gz index file */
			fgets (line , 1500, m_pIndxF);
			//fputs(line, stdout);
			
			/* get url and html size */
			vector<string> vs;
			string_split(line, ' ', vs);
			
			/* put url and size into a map(which is ordered immdiately) and keep a vector for all the url */
			int len = strlen(m_gzFName.c_str());
			if (len < FILENAME_MAX - 6
					&& ((len > 3 && m_gzFName[len-3] == '.'
							&& m_gzFName[len-2] == 'g'
							&& m_gzFName[len-1] == 'z')
						|| (len > 2 && m_gzFName[len-2] == '.'
							&& m_gzFName[len-1] == 'Z')))
			{
				
				m_mpIndx[vs[0]] = atol(vs[5].c_str());//if it is nz2 data
			}
			else
			{
				m_mpIndx[vs[0]] = atol(vs[3].c_str());//if it is nz10 data
			}
			
			
			m_vIndx.push_back(vs[0]);

		}	
		fclose (m_pIndxF);
	}
}


#include <iostream>
#include "JTools.h"

/* devide string into pieces by specified delimiter */
int string_split(const std::string& s, const char c,
	std::vector<std::string>& vs)
{
	std::string::size_type i = 0;
	std::string::size_type j = s.find_first_of(c);
	while (j != std::string::npos)
	{
		vs.push_back(s.substr(i, j-i));
		i = j+1;
		j = s.find_first_of(c, i);
	}
	vs.push_back(s.substr(i));
	return vs.size();
}

/* devide string into pieces by specified delimiter */
int string_split(const std::string& s, const char c[],
	std::vector<std::string>& vs)
{
	std::string::size_type i = 0;
	std::string::size_type j = s.find_first_of(c);
	while (j != std::string::npos) {
		vs.push_back(s.substr(i, j-i));
		i = j+1;
		j = s.find_first_of(c, i);
	}
	vs.push_back(s.substr(i));
	return vs.size();
}

/* devide string into pieces by specified delimiter */
int  str_tok(char buff[], const char delm[], char *subs[], const int nsubs)
{
        int     n = -1;
        char    *p;

        /* split the substrings and count them */
        subs[++n] = strtok_r(buff, delm, &p);
        while (subs[n] && n < nsubs-1)
        {
                subs[++n] = strtok_r(NULL, delm, &p);
        }
        if (!subs[n]) --n;
        return n+1;
}

/* print multimap structure on to the console */
void printMap(std::multimap<std::string, std::string> & myMap)
{
	std::multimap<std::string, std::string>::iterator map_it = myMap.begin();
	
	typedef std::multimap<std::string, std::string>::size_type sz_type;
	

	while(map_it!=myMap.end())
	{
		std::cout << map_it->first<< " ";
		sz_type wordcount = myMap.count(map_it->first);
		
		for (sz_type i =0; i != wordcount; ++i, ++map_it )
		{
			std::cout << map_it->second << " ";
		}	
		std::cout<< std::endl;
	}
}

/* print current time to console  */
void printTime()
{
	struct tm *current;
	time_t now;
	time(&now);
	current = localtime(&now);
	printf("time %i:%i:%i\n", current->tm_hour, current->tm_min, current->tm_sec);
}


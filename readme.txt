WebIndex 4.1 readme.txt ---by Jie Wu


WHAT CAN WE DO:

Generally speaking, "WebIndex" can process the given data into inverted index structure, which is a  part for the future search engine solution. It is the ninth version on its development, and it is the most stable version for either nz2 or nz10 data. It can build up an inverted index structure for search engine from these two web page data sources. The steps it gets through are Uncompress, Cut into html page, Parse out the word, Build up Lexicon and Index structure, write into sub indexes, merge into final index.

HOW TO RUN:

"WebIndex" is built under linux, using C++ language and g++ complier. It is only runnable for linux/Unix system. To run this program, firstly, you have to put the given data under its current directroy within the original folder, eg. "./nz10_merged" or "./nz2_merged", then double-click "WebIndex", it will be running on process. If there isn't WebIndex file, please complie it first.

The output of the program is a complete index struture, it will be under directory "JData2"(nz2) or "JData10"(nz10), The index is devided into 52 files by alphabetic classification. Every letter has two files, *_lex, *_index. *_lex file hold the lexicon structure, with format(word start end), *index_file hold inverted index structure, with format(docID freq position context...)

RESULT FACT:

For nz10 data(593.6MB), the costing time is 10min 33sec, the size of result index files is 423.5MB, the average RAM level is not stable, around 200MB to 400MB;
For nz2 data(126.2MB), the costing time is 1min 51sec, the size of result index files is 80.1MB. the average RAM level is very stable, about 89MB.

HOW IT WORKS:

The work flow of the program is as below:
main function get the list of data files, and go in to a loop of this file list, processing the data files by uncompressing, parsing and building index in JgzData::process(). The index is built into a JWordMap object's multimap member sorted eventually. Processed every 30 files, JWordMap will write into alphbetic sub indexes, and delete the memory and keep goinig on. When all the data files are processed completelly, main function will have a loop to get data from all the sub indexes by alphabetic order, and build into one final indexes in binary mode.

The major Class is JgzData and JWordMap, which is in charge of the most part of processing words. JgzData is in charge of uncompress and fetch data from given gz files, and commnicates with JgzIndex to make sure it is getting the right data from sources. It put the html page into parser, and get words from them. Then, JgzData filter the words out of bad word and numbers, and build up a html primitive structure for future process.

The second major class JWordMap, I think it is more important than JgzData. JwordMap holds up all the index struction. It provides really powerful member functions for project to deal with the index struction. I think this class is the best of this project, it can build up index from a html map(a primitive index), it can merge two indexes together, it can get one part of the index, lets say all the element from "a"to "az", it can read data from _index and _lex and build index struction, it can write and print the index into file or console. Read data is the most beautiful implementation of this project.

Other than above tow, I also have JTools, which is a very handful tool set, it has two string_split functions and str_tok, they can devide a string into pieces by specified delimiter. JDocID which can manage and generate unique ID from a url. JgzIndex is very similar to JgzData, read information is the most important function of itself. gzFile is a special function for uncompress and compress gz format. Parser is the function professor provided, it has a few bugs, but it generally works fine.

RESTRICTION:

There is not really much critical limitation of this program, it is very stable in Ubuntu system. But it deos has some limitations, it probably crashes when the available RAM is much lower than its average level. In Windows, the merge function is much slower than in Linux. Since lacking test on varied systems, different environment is expecting to be causing unknown errors. The temperary file generate during the process will be approximately similar size as the result data file. So you need double the result size as disk space expectation to get through the process. It cannot promise no data is missing in the process, I wildly guess that the last html page in every data sources is non-readable.



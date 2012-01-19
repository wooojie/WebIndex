CC = g++
#CFLAGS=-O4
CFLAGS=-Wall 

WebIndex: makefile main.o JTools.o gzFile.o parser.o JgzIndx.o JgzData.o JDocID.o JWordMap.o
	$(CC) $(CFLAGS) -o $@ main.o JTools.o gzFile.o parser.o JgzIndx.o JgzData.o JDocID.o JWordMap.o

main.o : main.cpp 
	$(CC) $(CFLAGS) -c main.cpp 
	
JTools.o: JTools.cpp JTools.h
	$(CC) $(CFLAGS) -c JTools.cpp
	
parser.o : parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c 
	
gzFile.o : gzFile.c gzFile.h
	$(CC) $(CFLAGS) -c gzFile.c 

JgzIndx.o: JgzIndx.cpp JgzIndx.h gzFile.h JTools.h
	$(CC) $(CFLAGS) -c JgzIndx.cpp
	
JgzData.o: JgzData.cpp JgzData.h gzFile.h JTools.h parser.h
	$(CC) $(CFLAGS) -c JgzData.cpp
	
JDocID.o: JDocID.cpp JDocID.h
	$(CC) $(CFLAGS) -c JDocID.cpp
	
JWordMap.o: JWordMap.cpp JWordMap.h
	$(CC) $(CFLAGS) -c JWordMap.cpp
	
cleanup:
	rm -f *.o
	rm -f WebIndex

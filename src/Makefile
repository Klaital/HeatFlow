CC=g++
CFLAGS=-std=c++11

all: HeatFlowProject.o MaterialsCollection.o Material.o

HeatFlowProject.o: MaterialsCollection.h HeatFlowProject.h HeatFlowProject.cc
	$(CC) HeatFlowProject.cc -c $(CFLAGS)

tinyxml.o: tinyxml2.h tinyxml2.cpp
	$(CC) tinyxml2.cpp -c $(CFLAGS)

MaterialsCollection.o: MaterialsCollection.h MaterialsCollection.cc tinyxml2.o
	$(CC) MaterialsCollection.cc -c $(CFLAGS)

Material.o: Material.h Material.cc
	$(CC) Material.cc -c $(CFLAGS)

clean: 
	rm ../bin/*.exe *.o *.stackdump ../test/*.o ../test/*.exe


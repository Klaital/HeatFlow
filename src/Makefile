all: HeatFlowProject.o MaterialsCollection.o Material.o

HeatFlowProject.o: MaterialsCollection.h HeatFlowProject.h HeatFlowProject.cc
	g++ HeatFlowProject.cc -c

MaterialsCollection.o: MaterialsCollection.h MaterialsCollection.cc
	g++ MaterialsCollection.cc -c

Material.o: Material.h Material.cc
	g++ Material.cc -c

clean: 
	rm ../bin/*.exe ../bin/TestField2D *.o *.stackdump ../test/*.o ../test/*.exe


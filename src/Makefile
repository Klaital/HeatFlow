
Field2D.o: Field2D.h Field2D.cc
	g++ Field2D.cc -c

HeatFlowProject.o: HeatFlowProject.h HeatFlowProject.cc
	g++ HeatFlowProject.cc -c

Test: TestField2D
	../bin/TestField2D

TestField2D: TestField2D.cc Field2D.o
	g++ TestField2D.cc -c 
	g++ TestField2D.o Field2D.o -o ../bin/TestField2D

clean: 
	rm ../bin/*.exe ../bin/TestField2D *.o *.stackdump ../test/*.o ../test/*.exe


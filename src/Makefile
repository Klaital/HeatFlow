
Field2D.o: Field2D.hpp Field2D.cpp
	g++ Field2D.cpp -c

HeatFlowProject.o: HeatFlowProject.hpp HeatFlowProject.cpp
	g++ HeatFlowProject.cpp -c

Test: TestField2D
	../bin/TestField2D

TestField2D: TestField2D.cpp Field2D.o
	g++ TestField2D.cpp -c 
	g++ TestField2D.o Field2D.o -o ../bin/TestField2D

clean: 
	rm ../bin/*.exe ../bin/TestField2D *.o *.stackdump ../test/*.o ../test/*.exe


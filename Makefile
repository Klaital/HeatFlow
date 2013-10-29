
Field2D.o: src/Field2D.hpp src/Field2D.cpp
	g++ src/Field2D.cpp -c

HeatFlowProject.o: src/HeatFlowProject.hpp src/HeatFlowProject.cpp
	g++ src/HeatFlowProject.cpp -c

Test: bin/TestField2D
	./TestField2D.exe

TestField2D: TestField2D.cpp Field2D.o
	g++ TestField2D.cpp -c 
	g++ TestField2D.o Field2D.o -o bin/TestField2D

clean: 
	rm bin/*.exe bin/TestField2D *.o *.stackdump 


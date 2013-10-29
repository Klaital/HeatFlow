
Field2D.o: Field2D.hpp Field2D.cpp
	g++ Field2D.cpp -c

HeatFlowProject.o: HeatFlowProject.hpp HeatFlowProject.cpp
	g++ HeatFlowProject.cpp -c

Test: TestField2D
	./TestField2D.exe

TestField2D: TestField2D.cpp Field2D.o
	g++ TestField2D.cpp -c 
	g++ TestField2D.o Field2D.o -o TestField2D.exe

clean: 
	rm TestField2D.exe *.o *.stackdump 


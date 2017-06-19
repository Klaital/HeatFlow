CC=g++
CPPFLAGS=-std=c++11
GTEST_DIR = ../../googletest/googletest

CPPFLAGS += -isystem $(GTEST_DIR)/include
# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = matrix_file_test utilities_test test_all heat_flow_project_test tinxyml2_test

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all: utilities.o HeatFlowProject.o MaterialsCollection.o Material.o $(TESTS)
clean: 
	rm -f ../bin/*.exe *.o *.a *.stackdump ../test/*.o ../test/*.exe $(TESTS) a.out

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^


# Actual Project libraries
utilities.o: utilities.h utilities.cc
	$(CC) utilities.cc -c $(CPPFLAGS) $(CXXFLAGS)

HeatFlowProject.o: HeatFlowProject.h HeatFlowProject.cc tinyxml2.o Material.o MatrixFile.h
	$(CC) HeatFlowProject.cc -c $(CPPFLAGS) $(CXXFLAGS)

tinyxml2.o: tinyxml2.h tinyxml2.cpp
	$(CC) tinyxml2.cpp -c $(CPPFLAGS) $(CXXFLAGS)

MaterialsCollection.o: MaterialsCollection.h MaterialsCollection.cc tinyxml2.o
	$(CC) MaterialsCollection.cc -c $(CPPFLAGS) $(CXXFLAGS)

Material.o: Material.h Material.cc configs.h
	$(CC) Material.cc -c $(CPPFLAGS) $(CXXFLAGS)

# Test suites
utilities_test.o: utilities.o utilities_test.cc $(GTEST_HEADERS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c utilities_test.cc

utilities_test: utilities_test.o utilities.o gtest_main.a
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@

matrix_file_test.o: MatrixFile.h matrix_file_test.cc $(GTEST_HEADERS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c matrix_file_test.cc

matrix_file_test: matrix_file_test.o utilities.o gtest_main.a
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@

heat_flow_project_test.o: Material.o MatrixFile.h tinyxml2.o HeatFlowProject.o heat_flow_project_test.cc $(GTEST_HEADERS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c heat_flow_project_test.cc

heat_flow_project_test: Material.o MatrixFile.h tinyxml2.o heat_flow_project_test.o gtest_main.a
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@

tinyxml2_test.o: tinyxml2.o tinyxml2_test.cc $(GTEST_HEADERS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c tinyxml2_test.cc

tinyxml2_test: tinyxml2.o tinyxml2_test.o gtest_main.a
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@

test_all.o: test_all.cc $(GTEST_HEADERS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c test_all.cc

test_all: tinyxml2_test.o heat_flow_project_test.o matrix_file_test.o utilities_test.o tinyxml2.o utilities.o HeatFlowProject.o Material.o test_all.o gtest_main.a
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@

test: test_all
	./test_all

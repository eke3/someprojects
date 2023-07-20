CXX = g++
CXXFLAGS = -Wall

test: art.o test.cpp
	$(CXX) $(CXXFLAGS) art.o test.cpp -o test

proj0: art.o mytest.cpp
	$(CXX) $(CXXFLAGS) art.o mytest.cpp -o proj0

art.o: art.h art.cpp
	$(CXX) $(CXXFLAGS) -c art.cpp

val:
	valgrind ./proj0

CXX = g++
CXXFLAGS = -Wall

driver: railroad.o driver.cpp
	$(CXX) $(CXXFLAGS) railroad.o driver.cpp -o proj1

proj1: railroad.o mytest.cpp
	$(CXX) $(CXXFLAGS) railroad.o mytest.cpp -o proj1

railroad.o: railroad.h railroad.cpp
	$(CXX) $(CXXFLAGS) -c railroad.cpp

val:
	valgrind --track-origins=yes ./proj1

run:
	./proj1

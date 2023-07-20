CXX = g++
CXXFLAGS = -Wall -g

driver: cache.o driver.cpp
	$(CXX) $(CXXFLAGS) cache.o driver.cpp -o driver

proj4: cache.o mytest.cpp
	$(CXX) $(CXXFLAGS) cache.o mytest.cpp -o proj4

cache.o: cache.h cache.cpp
	$(CXX) $(CXXFLAGS) -c cache.cpp

val:
	valgrind ./proj4
        #valgrind --track-origins=yes -s ./proj3
        #valgrind --leak-check=full -s ./proj3
        #valgrind -s ./proj3
run:
	./proj4

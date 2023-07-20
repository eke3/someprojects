CXX = g++
CXXFLAGS = -Wall -g

driver: streak.o driver.cpp
	$(CXX) $(CXXFLAGS) streak.o driver.cpp -o proj2

proj2: streak.o mytest.cpp
	$(CXX) $(CXXFLAGS) streak.o mytest.cpp -o proj2

streak.o: streak.h streak.cpp
	$(CXX) $(CXXFLAGS) -c streak.cpp

val:
	#valgrind --track-origins=yes -s ./proj2
	valgrind --leak-check=full -s ./proj2
	#valgrind -s ./proj2
run:
	./proj2

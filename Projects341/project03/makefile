CXX = g++
CXXFLAGS = -Wall -g

driver: iqueue.o driver.cpp
	$(CXX) $(CXXFLAGS) iqueue.o driver.cpp -o proj3

proj3: iqueue.o mytest.cpp
	$(CXX) $(CXXFLAGS) iqueue.o mytest.cpp -o proj3

iqueue.o: iqueue.h iqueue.cpp
	$(CXX) $(CXXFLAGS) -c iqueue.cpp

val:
	valgrind ./proj3
	#valgrind --track-origins=yes -s ./proj3
	#valgrind --leak-check=full -s ./proj3
	#valgrind -s ./proj3
run:
	./proj3

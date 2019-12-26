CXX = g++
CXXFLAGS = -Wall

Driver: JQueue.h JQueueTest.cpp JQueue.o
	$(CXX) $(CXXFLAGS) JQueue.h JQueue.cpp JQueueTest.cpp -o Driver

JQueue.o: JQueue.h JQueue.cpp
	$(CXX) $(CXXFLAGS) -c JQueue.cpp

run:
	./Driver
clean:
	rm *~
	rm *.o*

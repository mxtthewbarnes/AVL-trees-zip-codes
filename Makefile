CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

all: avl_map

avl_map: main.o avl_map.o
	$(CXX) $(CXXFLAGS) -o avl_map main.o avl_map.o

avl_map.o: avl_map.cpp avl_map.h
	$(CXX) $(CXXFLAGS) -c avl_map.cpp

main.o: main.cpp avl_map.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o avl_mape
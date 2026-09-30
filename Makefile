CXX = g++ # the lab requires g++, not gcc

CXXFLAGS = -Wall -Wextra -std=c++17

main: Lab5task1.cpp # target: what it depends on
	$(CXX) $(CXXFLAGS) Lab5task1.cpp -o main

clean:
	rm -f main

.PHONY: clean


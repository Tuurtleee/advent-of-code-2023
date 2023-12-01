CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -O2 -std=c++17 -Iinclude -I/usr/local/include

part1: src/part1.cpp
	$(CXX) $(CXXFLAGS) -o part1.out src/part1.cpp && ./part1.out

part2: src/part2.cpp
	$(CXX) $(CXXFLAGS) -o part2.out src/part2.cpp && ./part2.out

clean:
	rm -f part1.out part2.out
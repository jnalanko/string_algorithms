sources = SA.cpp KMP.cpp rabin_karp.cpp tests.cpp
cppFlags = -std=c++11 -O3 -g

all:
	$(CXX) $(sources) $(cppFlags) -o tests

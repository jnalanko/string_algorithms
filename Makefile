sources = SA.cpp KMP.cpp rabin_karp.cpp
headers = string_algorithms.hh
objects = $(patsubst %.cpp,build/%.o,$(sources))
cppFlags = -std=c++11 -O3 -g -MMD

all: library tests

# Include header dependencies
-include $(objects:%.o=%.d)

build/%.o : %.cpp build
	$(CXX) -c $< $(cppFlags) -o $@
	
build:
	@mkdir $@ -p

library: $(objects)
	mkdir lib -p
	mkdir include -p
	ar rcs lib/libstringalg.a $(objects)
	cp $(headers) include

tests: $(objects)
	$(CXX) $(objects) tests.cpp $(cppFlags) -o tests
	
clean:
	rm build/*
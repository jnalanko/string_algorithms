sources = SA.cpp KMP.cpp rabin_karp.cpp
headers = string_algorithms.hh
cppFlags = -std=c++11 -O3 -g -MMD

# Substitute .cpp with .o
objects = $(patsubst %.cpp,build/%.o,$(sources)) 


all: library tests

# Include header dependencies
-include $(objects:%.o=%.d)

# Map object files to source files. " | build " is an order-only prerequisite meaning
# that the build directory must exist before building objects, but
# the objects should must not be rebuilt if the timestamp of the build
# directory changes, which happens every time a file is modified in the directory.
build/%.o : %.cpp | build
	$(CXX) -c $< $(cppFlags) -o $@

# A target to guarantee that the build directory exists
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
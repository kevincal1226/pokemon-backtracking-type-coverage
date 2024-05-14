EXECUTABLE  = pokemon

PROJECTFILE = $(or $(wildcard project*.cpp $(EXECUTABLE).cpp), main.cpp)

# enables c++17 on CAEN or 281 autograder
PATH := /usr/um/gcc-11.3.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-11.3.0/lib64
LD_RUN_PATH := /usr/um/gcc-11.3.0/lib64

# disable built-in rules
.SUFFIXES:

# designate which compiler to use
CXX         = g++

# rule for creating objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp

# list of test drivers (with main()) for development

# list of sources used in project
SOURCES     = $(wildcard *.cpp)
# list of objects used in project
OBJECTS     = $(SOURCES:%.cpp=%.o)

# Default Flags
CXXFLAGS = -std=c++23 -Wconversion -Wall -Werror -Wextra -pedantic

# make debug - will compile sources with $(CXXFLAGS) -g3 and -fsanitize
#              flags also defines DEBUG and _GLIBCXX_DEBUG
debug: CXXFLAGS += -g3 -DDEBUG -fsanitize=address -fsanitize=undefined
debug:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)_debug
.PHONY: debug

# make release - will compile sources with $(CXXFLAGS) and the -O3 flag also
#                defines NDEBUG so that asserts will not check
release: CXXFLAGS += -O3 -DNDEBUG
release: $(EXECUTABLE)
.PHONY: release

$(EXECUTABLE): $(OBJECTS)
ifneq ($(EXECUTABLE), executable)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)
else
	@echo Edit EXECUTABLE variable in Makefile.
	@echo Using default a.out.
	$(CXX) $(CXXFLAGS) $(OBJECTS)
endif

# make clean - remove .o files, executables, tarball
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE)_debug
.PHONY: clean
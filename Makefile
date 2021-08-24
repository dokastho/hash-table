CXX         = g++
CXXFLAGS = -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic 
SOURCES     = $(wildcard *.cpp)
SOURCES     := $(filter-out $(TESTSOURCES), $(SOURCES))
PERF_FILE = perf.data*
PATH := /usr/um/gcc-6.2.0/bin:$(PATH)
WRAP = wrap.tar.gz
EXECUTABLE = hash

WRAPFILES=$(filter-out $(TESTSOURCES), \
                   $(wildcard Makefile *.h *.hpp *.cpp test*.txt))

release: CXXFLAGS += -O3 -DNDEBUG
release: 
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)
debug: CXXFLAGS += -g3 -DDEBUG
debug:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)_debug
all: release debug profile

$(EXECUTABLE): $(OBJECTS)
ifeq ($(EXECUTABLE), executable)
	@echo Edit EXECUTABLE variable in Makefile.
	@echo Using default a.out.
	$(CXX) $(CXXFLAGS) $(OBJECTS)
else
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)
endif
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE)_debug $(EXECUTABLE)_profile \
      $(TESTS) $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE) $(PERF_FILE) \
      $(UNGRADED_SUBMITFILE)
	rm -Rf *.dSYM
$(WRAP): $(WRAPFILES)
	rm -f $(WRAPFILES)
CXX      ?= g++
CXXFLAGS ?= -std=c++20


OBJECTS = main.o
SOURCES = main.cpp
EXEC     = main
LDFLAGS ?= 
LDLIBS  ?= 

all: $(EXEC)


$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(EXEC) *.dat *.exe

distclean: clean
	$(RM) $(EXEC) $(EXEC_MUPARSER)
	$(RM) *~

CXX      ?= g++
CXXFLAGS ?= -std=c++20


SRC_DIR  = src
OBJ_DIR  = obj
SOURCES  = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS  = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

EXEC     = main
LDFLAGS ?= 
LDLIBS  ?= 

all: $(EXEC)

$(EXEC): $(OBJECTS) | $(OBJ_DIR)
	$(CXX) $(OBJECTS) -o $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	$(RM) *.o $(EXEC) *.dat *.exe

distclean: clean
	$(RM) -r $(OBJ_DIR) $(EXEC)
	$(RM) $(EXEC) $(EXEC_MUPARSER)
	$(RM) *~

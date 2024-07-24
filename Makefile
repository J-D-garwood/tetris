all:
	g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

#resources:
#    @echo "Resource path: $(RES_DIR)"
#
## Compiler and flags
#CXX = g++
#CXXFLAGS = -std=c++11 -Wall -I src/include
#LDFLAGS = -L src/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
#
## Paths
#SRC_DIR = src
#OBJ_DIR = obj
#RES_DIR = resources
#
## Source files and objects
#SRCS = $(wildcard $(SRC_DIR)/*.cpp)
#OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
#
## Executable name
#EXEC = main.exe
#
## Default target
#all: $(EXEC)
#
## Build executable
#$(EXEC): $(OBJS)
#    $(CXX) $^ -o $@ $(LDFLAGS)
#
## Compile source files into objects
#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
#    @mkdir -p $(OBJ_DIR)
#    $(CXX) $(CXXFLAGS) -c $< -o $@
#
## Clean target
#clean:
#    rm -rf $(OBJ_DIR) $(EXEC)
#
## Additional commands to include resource path
#resources:
#    @echo "Resource path: $(RES_DIR)"
#
## Build command with resource path
#.PHONY: build
#build:
#    $(CXX) $(CXXFLAGS) -I $(RES_DIR) -o $(EXEC) main.cpp $(LDFLAGS)
#
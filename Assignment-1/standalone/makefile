# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -Wall -I../common

# Source files
SRCS = $(wildcard ../common/**/*.cpp) $(wildcard ../common/*.cpp) $(wildcard *.cpp) $(wildcard /**/*.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = main.exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	rm -f $(OBJS) $(EXEC)

run: all
	./$(EXEC)

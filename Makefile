CXX = clang++

# Compiler flags
CXXFLAGS = -w -I./include/asio-1.28.0/asio/include -I./src -std=c++20 -pthread

# Source files
COMMON_SRCS = $(wildcard ./src/common/**/*.cpp) $(wildcard ./src/common/*.cpp)
COMMON_CLIENT_SERVER_SRCS = $(wildcard ./src/client-server/common.cpp)
CLIENT_SRCS = $(COMMON_SRCS) $(wildcard ./src/client-server/client.cpp) $(COMMON_CLIENT_SERVER_SRCS)
SERVER_SRCS = $(COMMON_SRCS) $(wildcard ./src/client-server/server.cpp) $(COMMON_CLIENT_SERVER_SRCS)
STANDALONE_SRCS = $(COMMON_SRCS) $(wildcard ./src/standalone/*.cpp)

# Object files
SERVER_OBJS = $(SERVER_SRCS:.cpp=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.cpp=.o)
STANDALONE_OBJS = $(STANDALONE_SRCS:.cpp=.o)

# Executable names
STANDALONE_EXEC = standalone.exe
SERVER_EXEC = server.exe
CLIENT_EXEC = client.exe

# All task
all: $(SERVER_EXEC) $(CLIENT_EXEC) $(STANDALONE_EXEC)

$(STANDALONE_EXEC): $(STANDALONE_OBJS)
	$(CXX) $(CXXFLAGS) -o $(STANDALONE_EXEC) $(STANDALONE_OBJS)

$(SERVER_EXEC): $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) -o $(SERVER_EXEC) $(SERVER_OBJS)

$(CLIENT_EXEC): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_EXEC) $(CLIENT_OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

# More Tasks
standalone: $(STANDALONE_EXEC)

server: $(SERVER_EXEC)

client: $(CLIENT_EXEC)

clean:
	rm -f $(STANDALONE_OBJS) $(SERVER_OBJS) $(CLIENT_OBJS) $(STANDALONE_EXEC) $(SERVER_EXEC) $(CLIENT_EXEC) 

run_standalone: $(STANDALONE_EXEC)
	./$(STANDALONE_EXEC)

run_server: $(SERVER_EXEC)
	./$(SERVER_EXEC)

run_client: $(CLIENT_EXEC)
	./$(CLIENT_EXEC)

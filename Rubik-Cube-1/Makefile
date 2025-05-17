# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(INCLUDE_DIR) -IC:/vcpkg/installed/x64-windows/include

# Linker flags (include winsock)
LDFLAGS = -lws2_32 -lmswsock -L"C:/vcpkg/installed/x64-windows/lib"

# Source and include directories
SRC_DIR = src
INCLUDE_DIR = include

# All source files (make sure to include both CubeBackend.cpp and CubeSolver.cpp)
SRCS = $(SRC_DIR)/CubeBackend.cpp $(SRC_DIR)/CubeSolver.cpp $(SRC_DIR)/Cube.cpp $(SRC_DIR)/CoordCube.cpp $(SRC_DIR)/FaceCube.cpp $(SRC_DIR)/MoveTable.cpp $(SRC_DIR)/pruneTable.cpp $(SRC_DIR)/Search.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = cube_backend.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist "$(SRC_DIR)\*.o" del /Q "$(SRC_DIR)\*.o"
	@if exist "$(TARGET)" del /Q "$(TARGET)"

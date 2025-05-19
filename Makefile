# Source and include directories
SRC_DIR := src
INCLUDE_DIR := include

# Detect OS and set platform-specific flags
ifeq ($(OS),Windows_NT)
  EXT        := .exe
  RM         := del /Q
  INCLUDES   := -I$(INCLUDE_DIR) -IC:/vcpkg/installed/x64-windows/include
  LDFLAGS_OS := -lws2_32 -lmswsock -L"C:/vcpkg/installed/x64-windows/lib"
else
  EXT        :=
  RM         := rm -f
  INCLUDES   := -I$(INCLUDE_DIR)
  LDFLAGS_OS :=
endif

# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall $(INCLUDES)

# Source files and objects
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)

# Output target
TARGET := cube_backend$(EXT)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS_OS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)

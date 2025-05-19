# Detect OS
ifeq ($(OS),Windows_NT)
  EXT         := .exe
  RM          := del /Q
  INCLUDES    := -I$(INCLUDE_DIR) -IC:/vcpkg/installed/x64-windows/include
  LDFLAGS_OS  := -lws2_32 -lmswsock -L"C:/vcpkg/installed/x64-windows/lib"
else
  UNAME_S     := $(shell uname -s)
  EXT         :=            # no .exe on Linux/macOS
  RM          := rm -f
  INCLUDES    := -I$(INCLUDE_DIR)
  LDFLAGS_OS  :=             # add Linux-specific libs here if needed
endif

# Compiler and flags
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall $(INCLUDES)

# Source layout
SRC_DIR   := src
INCLUDE_DIR := include
SRCS      := $(wildcard $(SRC_DIR)/*.cpp)
OBJS      := $(SRCS:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)

# Final target
TARGET    := cube_backend$(EXT)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS_OS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)

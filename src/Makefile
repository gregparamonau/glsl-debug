# Define the compiler
CXX = g++

# Define compiler flags (C++17 standard, enable warnings)
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Define the target executable name
TARGET = glsl_debug

# Target to compile the executable
all: $(TARGET)

# Added lexer.cpp to the dependencies and compile command below
$(TARGET): main.cpp lexer.cpp
	$(CXX) $(CXXFLAGS) main.cpp lexer.cpp -o $(TARGET)

# Clean up built files
clean:
	rm -f $(TARGET)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I include/
TARGET = glsl_debug

SRCS = $(wildcard src/*.cpp)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
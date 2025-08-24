# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = memocli

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

clean:
	rm -f $(TARGET)

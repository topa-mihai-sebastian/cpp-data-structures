CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++17

TARGET = app

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)

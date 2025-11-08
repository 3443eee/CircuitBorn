# Automatically use all CPU cores for parallel builds
MAKEFLAGS += -j$(shell nproc)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I/home/a/libs/
LIBS = -lraylib -ldl -lm -lpthread -lGL -lrt -lX11

TARGET = CircuitBorn
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: clean

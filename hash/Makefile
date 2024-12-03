CXX = g++
CXXFLAGS = -std=c++11 -I/usr/include -lcryptopp

SRC = hash.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = hash_prog

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

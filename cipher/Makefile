CXX = g++                
CXXFLAGS = -std=c++17 -g -Wall   
LDFLAGS = -lcryptopp      

SRC = main.cpp cipher.cpp  
OBJ = $(SRC:.cpp=.o)       
EXEC = cipher_prog      

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $(EXEC) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

test: $(EXEC)
	./$(EXEC)

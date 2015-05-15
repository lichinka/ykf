CXX      = g++
#CXXFLAGS = -O0 -g -std=c++11 -Wall
CXXFLAGS = -O3 -DNDEBUG -Wall -std=c++11
INC		 = -I./include -I/usr/include/SDL2 
LDFLAGS  = -lm -lstdc++ -lSDL2 -lSDL2_image -lglfw
OBJS     = main.o
BIN 	 = ykf

all : $(BIN)

$(BIN) : $(OBJS)
	$(CXX) $(CFLAGS) $(LDFLAGS) $< -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@ $(LDFLAGS) 

clean :
	rm -rf *.o $(BIN)

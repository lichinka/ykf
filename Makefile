CXX      = g++
CXXFLAGS = -g -O0 -std=c++11 -Wall
INC		 = -I./include -I/usr/include/SDL2 
LDFLAGS  = -lm -lstdc++ -lSDL2 -lSDL2_image
OBJS     = main.o
BIN 	 = ykf

all : $(BIN)

$(BIN) : $(OBJS)
	$(CXX) $(CFLAGS) $(LDFLAGS) $< -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@ $(LDFLAGS) 

clean :
	rm -rf *.o $(BIN)

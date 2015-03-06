CXX      = g++
CXXFLAGS = -std=c++11 -Wall
INC		 = -I./include -I/usr/include/SDL2 
LDFLAGS  = -lstdc++ -lSDL2 -lSDL2_image
OBJS     = main.o
BIN 	 = ykf

all : $(BIN)

$(BIN) : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

%.o : %.cpp
	$(CC) $(CXXFLAGS) $(INC) -c $< -o $@ $(LDFLAGS) 

clean :
	rm -rf *.o $(BIN)

VERSION= c++17
SUBSYSTEM= windows
OBJ= test.o glad.o gefx_debug.o 
OPTIMIZATION=0
SRC= ../src
EXT_SRC= ../extrsc
FLAGS= -Wall -Wextra -O$(OPTIMIZATION) -std=$(VERSION) -m$(SUBSYSTEM) -I$(EXT_SRC)/include -L$(EXT_SRC)/src -lglfw3



build: $(OBJ)
	g++ -o app.exe $(OBJ) $(FLAGS)
	./app.exe
lib: $(OBJ)
	g++ -o gefx.lib $(OBJ) $(FLAGS)
test.o: $(SRC)/test.cpp $(SRC)/*.h
	g++ -c $(SRC)/test.cpp $(FLAGS)
glad.o: $(SRC)/glad.c 
	g++ -c $(SRC)/glad.c $(FLAGS)

gefx_debug.o: $(SRC)/gefx_debug.cpp $(SRC)/gefx_debug.h
	g++ -c $(SRC)/gefx_debug.cpp $(FLAGS)
CC=g++
INCLUDES=include/
CFLAGS=-Wall
OBJ=GObject.o Window.o DisplayFile.o

%.o: lib/%.cpp
	$(CC) -std=c++11 -c $< -I $(INCLUDES) $(CFLAGS)

all: $(OBJ)
	$(CC) -std=c++11 $(OBJ) src/*.cpp -o cg -I $(INCLUDES) $(CFLAGS) `pkg-config --cflags --libs gtkmm-3.0`

test:
	echo "Nothing yet to do"

clean:
	rm *.o -f
	rm cg -f

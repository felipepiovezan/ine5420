CC=g++
INCLUDES=include/
CFLAGS=-Wall
OBJ=GObject.o Point.o

%.o: lib/%.cpp
	$(CC) -c $< -I $(INCLUDES) $(CFLAGS)

all: $(OBJ)
	$(CC) $(OBJ) src/main.cpp -o cg -I $(INCLUDES) $(CFLAGS)

test:
	echo "Nothing yet to do"

clean:
	rm *.o -f
	rm cg -f

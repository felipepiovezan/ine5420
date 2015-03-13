CC=g++
INCLUDES=include/
CFLAGS=-Wall
OBJ=GObject.o Point.o GPoint.o GLine.o GPolygon.o Window.o DisplayFile.o

%.o: lib/%.cpp
	$(CC) -c $< -I $(INCLUDES) $(CFLAGS)

all: $(OBJ)
	$(CC) $(OBJ) src/*.cpp -o cg -I $(INCLUDES) $(CFLAGS) `pkg-config --cflags --libs gtkmm-3.0`

test:
	echo "Nothing yet to do"

clean:
	rm *.o -f
	rm cg -f

all:
	g++ -Wall -Iengine -Iio -Imaze -I. engine/*.cpp io/*.cpp maze/*.cpp main.cpp -lncurses -o release/maze.out

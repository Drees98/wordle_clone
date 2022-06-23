all: compile link

compile:
	g++ -I src/include -c wordle.cpp

link:
	g++ wordle.o -o wordle -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -mwindows
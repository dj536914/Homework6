all: othello main.o game.o othello.o archive
othello: main.o game.o othello.o
	g++ -o othello main.o game.o othello.o
main.o: main.cc
	g++ -c main.cc
game.o: game.h game.cc
	g++ -c game.cc
othello.o: othello.h othello.cc
	g++ -c othello.cc
archive:
	tar -cf archive.tar colors.h game.cc game.h main.cc Makefile othello.cc \
		othello.h piece.h
clean:
	\rm *.o archive.tar

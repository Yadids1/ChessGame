CPP = g++
FLAGS = -c -std=c++11 -Wextra -Wall -g

run: chess
	./chess

Piece.o: Piece.cpp Piece.h
	$(CPP) $(FLAGS) -c Piece.cpp

Board.o: Board.cpp Board.h
	$(CPP) $(FLAGS) Board.cpp -o Board.o

chess.o: chess.cpp Board.h Piece.h
	$(CPP) $(FLAGS) chess.cpp -o chess.o 
	
Pawn.o: Piece.h Pawn.cpp
	$(CPP) $(FLAGS) Pawn.cpp -o Pawn.o

Knight.o:  Piece.h Knight.cpp
	$(CPP) $(FLAGS) Knight.cpp -o Knight.o

King.o : Piece.h King.cpp
	$(CPP) $(FLAGS) King.cpp -o King.o

Queen.o: Piece.h Queen.cpp
	$(CPP) $(FLAGS) Queen.cpp -o Queen.o

Bishop.o: Piece.h Bishop.cpp
	$(CPP) $(FLAGS) Bishop.cpp -o Bishop.o

Rook.o: Piece.h Rook.cpp
	$(CPP) $(FLAGS) Rook.cpp -o Rook.o

chess: chess.o Piece.o Board.o Pawn.o Knight.o King.o Queen.o Bishop.o Rook.o
	$(CPP) Board.o Piece.o Pawn.o Knight.o King.o Queen.o Bishop.o Rook.o chess.o -o chess

tar:
	tar -cvf ex2.tar Board.h Piece.h Board.cpp Piece.cpp Pawn.cpp Knight.cpp King.cpp Queen.cpp Bishop.cpp Rook.cpp chess.cpp

all: 
	make chess

clean:
	-rm -f *.o Board.o Piece.o chess.o Ex2


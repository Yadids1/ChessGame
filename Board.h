
#ifndef EX2_CHESS_BOARD_H
#define EX2_CHESS_BOARD_H

#include <iostream>
#include "Piece.h"

/**
 * represent a chess board with 64 squares arranged in an eight-by-eight grid
 */
class Board
{
private:
    /* piece chess unicode */
    char unicodePieces[1][6][4] =
            {
                    { "\u265A", "\u265B", "\u265C", "\u265D", "\u265E", "\u265F" }
            };

    /* vector of vectors of pieces - represent the chess board */
    std::vector<std::vector<Piece*>> thisBoard;

    /* pointer to the white king piece */
    Piece* _whiteKing;

    /* pointer to the black king piece */
    Piece* _blackKing;

    /**
     * this function give a number for each piece type;
     * @param type of the piece
     * @return 0 for king, 1 for queen, 2 for rook, 3 for bishop, 4 knight, 5 pawn, -1 otherwise
     */
    int _hashPiece(std::string type);

public:
    /* include all the current white pieces in the board */
    std::vector<Piece*> whitePieces;

    /* include all the current black pieces in the board */
    std::vector<Piece*> blackPieces;

    /**
     * constructor of the board
     */
    Board();

    /**
     * destructor of the board
     */
    ~Board();

    /**
     * get slot position destination and Piece, and check if this piece can land in that slot
     * @param sourcePiece - the piece
     * @param row - row destination
     * @param col - column destination
     * @param color - the piece color
     * @param isDiagaonalPawn - indicate if this piece is pawn and that move is diagonaly
     * @return true if the land on this slot is legal, false otherwise
     */
    bool checkDestinationMove(Piece* sourcePiece, int row, int col, char color, bool isDiagaonalPawn);

    /**
     * get piece and vector of position and determine if that piece can leap over this slots;
     * @param slotToCheck - the slots lost composed from pairs of row and column.
     * @return true if the piece can leap over this slots, false otherwise
     */
    bool checkMoveLeggality(std::vector<int> slotToCheck);

    /**
     * get a slot and return the piece exist in it or a null pointer if this slot is empty
     * @param row - row position
     * @param col - column position
     * @return the piece exist in it or a null pointer if this slot is empty
     */
    Piece* getPiece(int row, int col);

    /**
     * init new game board. Each player begins the game with 16 pieces: one king, one queen,
     * two rooks, two knights, two bishops, and eight pawns
     */
    void initBoard();

    /**
     * print the game board to the screen
     */
    void printBoard();

    /**
     * print one slot in the board (with a piece or empty)
     * @param row - row position
     * @param col  - column position
     */
    void printSlot(int row, int col);

    /**
     * get position and remove the piece exist on this slot
     * @param row - row position
     * @param col  - column position
     * @param color - the piece color
     */
    void eatPiece(int row, int col, char color);

    /**
     * get slot position when a pawn advances to the eighth rank, as a part of the move it is
     * promoted and exchanged this pawn for queen,
    * @param row - row position
     * @param col  - column position
     */
    void setQueen(int row, int col);

    /**
     * get a piece and new destination slot and make the movement
     * @param myPiece - this piece
     * @param destRow - row destination
     * @param destCol - column destination
     */
    void move(Piece* myPiece, int destRow, int destCol);

    /**
     * get piece and slot position, and put this piece in this slot
     * @param myPiece - this piece
     * @param row - row position
     * @param col  - column position
     */
    void putPiece(Piece* myPiece, int row, int col);

    /**
     * @return the white king piece
     */
    Piece* getWhiteKing();

    /**
     * @return the black king piece
     */
    Piece* getBlackKing();

};

#endif //EX2_CHESS_BOARD_H

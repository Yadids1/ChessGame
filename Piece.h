/**
 * This class represent piece in a chess board
 * there is 6 types of pieces: pawn, king, queen, knight, bishop and rook.
 * each type have represented by derived class inherit piece class.
 * all the pieces have common characteristics: color, position and type.
 * Each of the six piece types moves differently therfore each derive class implement
 * 2 virtual method differently.
 */
#ifndef EX2_CHESS_PIECE_H
#define EX2_CHESS_PIECE_H

#include <iostream>
#include <vector>

class Piece
{
private:
    /* the piece color - white or black */
    char _color;
    /* piece row position */
    int _rowPos;
    /* piece column position */
    int _colPos;
    /* piece type */
    std::string _type;
    /* indicate if the rook or the king is in their first rank */
    bool _makeFirstMove = false;

public:
    /**
     * @brief virtual destructor of piece
     */
    virtual ~Piece();

    /**
     * piece constructor
     * @param color - piece color - white or black
     * @param rowPos - piece first row position
     * @param colPos - piece first column position
     * @param type - piece type
     */
    Piece(char color, int rowPos, int colPos, std::string type);

    /**
     *
     * @return this piece color: 'W' - for white piece, 'B' - for black piece
     */
    char getColor();

    /**
     * @return this piece row position;
     */
    int getRowPos();

    /**
     * @return this piece column position;
     */
    int getColPos();

    /**
     * @return this piece type: pawn, king, queen, knight, bishop or rook.
     */
    std::string getType();

    /**
     * set new position for this piece
     * @param newRow - destination row
     * @param newCol - destination column
     */
    void setPos(int newRow, int newCol);

    /**
     * check if row and col input is inside board borders
     * @param destRow - row input
     * @param destCol - column input
     * @return true if the position is legal, false otherwise
     */
    bool isSlotOutOfBoard(int destRow, int destCol);

    /**
     * @return true if the piece already moved, false otherwise
     */
    bool getFirstMove();

    /**
     * update that the piece make his first move
     */
    void setFirstMove();

    /**
     * check if this piece can move to particular new position.
     * @param destRow - row of new position
     * @param destCol - column of new position
     * @return true if the movement is legal for this piece, false otherwise
     */
    virtual bool isLegalMove(int destRow, int destCol) = 0;

    /**
     * get a position, and find all the slots that this piece need to skip over in order to arrive
     * to the new position
     * @param destRow - row new position
     * @param destCol - column new position
     * @return vector included the slots position in pairs, firstly row position
     * and after the column position.
     */
    virtual std::vector<int> slotsInTheWay(int destRow, int destCol) = 0;
};

/**
 * represent king piece
 */
class King : public Piece
{
public:
    /**
     * king piece constructor
     * @param color - piece color - white or black
     * @param rowPos - piece first row position
     * @param colPos - piece first column position
     * @param type - piece type
     */
    King(char color, int rowPos, int colPos, std::string type);

/**
    * check if the input position is legal for the king.
     * The king moves one square in any direction.
     * @param destRow - row new position
     * @param destCol - column new position
     * @return true if this movement is legal, false otherwise
     */
    bool isLegalMove(int destRow, int destCol);

/**
     * get a position, and find all the slots that this piece need to skip over in order to arrive
     * to the new position
     * @param destRow - row new position
     * @param destCol - column new position
     * @return empty vector - the king cant leap more than one slot (except castling)
     */
    std::vector<int> slotsInTheWay(int destRow, int destCol);
};

/**
 * represent Knight piece
 */
class Knight : public Piece
{
public:
    /**
     * knight piece constructor
     * @param color - piece color - white or black
     * @param rowPos - piece first row position
     * @param colPos - piece first column position
     * @param type - piece type
     */
    Knight(char color, int rowPos, int colPos, std::string type);

    /**
    * check if the input position is legal for the Knight.
     * The knight moves to any of the closest squares that are not on the same rank, file, or
     * diagonal, thus the move forms an "L"-shape: two squares vertically and one square horizontally,
     * or two squares horizontally and one square vertically.
     * @param destRow - row new position
     * @param destCol - column new position
     * @return true if this movement is legal, false otherwise
     */
    bool isLegalMove(int destRow, int destCol);

    /**
     * get a position, and find all the slots that this piece need to skip over in order to arrive
     * to the new position
     * @param destRow - row new position
     * @param destCol - column new position
     * @return empty vector - The knight is the only piece that can leap over other pieces.
     */
    std::vector<int> slotsInTheWay(int destRow, int destCol);
};

/**
 * represent Queen piece
 */
class Queen : public Piece
{
public:
    /**
     * Queen piece constructor
     * @param color - piece color - white or black
     * @param rowPos - piece first row position
     * @param colPos - piece first column position
     * @param type - piece type
     */
    Queen(char color, int rowPos, int colPos, std::string type);

    /**
    * check if the input position is legal for the Queen.
     * The queen combines the power of the rook and bishop and can move any number of squares
     * along rank, file, or diagonal
     * @param destRow - row new position
     * @param destCol - column new position
     * @return true if this movement is legal, false otherwise
     */
    bool isLegalMove(int destRow, int destCol);

    /**
     * get a position, and find all the slots that this piece need to skip over in order to arrive
     * to the new position
     * @param destRow - row new position
     * @param destCol - column new position
     * @return vector included the slots position in pairs, firstly row position
     * and after the column position.
     */
    std::vector<int> slotsInTheWay(int destRow, int destCol);
};

/**
 * represent Rook piece
 */
class Rook : public Piece
{
public:
    /**
     * Rook piece constructor
     * @param color - piece color - white or black
     * @param rowPos - piece first row position
     * @param colPos - piece first column position
     * @param type - piece type
     */
    Rook(char color, int rowPos, int colPos, std::string type);

    /**
    * check if the input position is legal for the Rook.
     * The rook can move any number of squares along any rank or file
     * @param destRow - row new position
     * @param destCol - column new position
     * @return true if this movement is legal, false otherwise
     */
    bool isLegalMove(int destRow, int destCol);

    /**
     * get a position, and find all the slots that this piece need to skip over in order to arrive
     * to the new position
     * @param destRow - row new position
     * @param destCol - column new position
     * @return vector included the slots position in pairs, firstly row position
     * and after the column position.
     */
    std::vector<int> slotsInTheWay(int destRow, int destCol);
};


/**
 * represent Pawn piece
 */
class Pawn : public Piece
{
public:
    /**
     * Pawn piece constructor
     * @param color - piece color - white or black
     * @param rowPos - piece first row position
     * @param colPos - piece first column position
     * @param type - piece type
     */
    Pawn(char color, int rowPos, int colPos, std::string type);

    /**
    * check if the input position is legal for the Pawn,
     *The pawn may move forward to the unoccupied square immediately in front of it on the same file,
     * or on its first move it may advance two squares along the same file provided both squares
     * are unoccupied, or the pawn may capture an opponent's piece on a square diagonally in front
     * of it on an adjacent file.
     * @param destRow - row new position
     * @param destCol - column new position
     * @return true if this movement is legal, false otherwise
     */
    bool isLegalMove(int destRow, int destCol);

    /**
     * get a position, and find all the slots that this piece need to skip over in order to arrive
     * to the new position
     * @param destRow - row new position
     * @param destCol - column new position
     * @return vector included the slots position in pairs, firstly row position
     * and after the column position.
     */
    std::vector<int> slotsInTheWay(int destRow, int destCol);
};

/**
 * represent Bishop piece
 */
class Bishop : public Piece
{
public:
    /**
     * Bishop piece constructor
     * @param color - piece color - white or black
     * @param rowPos - piece first row position
     * @param colPos - piece first column position
     * @param type - piece type
     */
    Bishop(char color, int rowPos, int colPos, std::string type);

    /**
    * check if the input position is legal for the Bishop,
     * The bishop can move any number of squares diagonally,
     * @param destRow - row new position
     * @param destCol - column new position
     * @return true if this movement is legal, false otherwise
     */
    bool isLegalMove(int destRow, int destCol);

    /**
     * get a position, and find all the slots that this piece need to skip over in order to arrive
     * to the new position
     * @param destRow - row new position
     * @param destCol - column new position
     * @return vector included the slots position in pairs, firstly row position
     * and after the column position.
     */
    std::vector<int> slotsInTheWay(int destRow, int destCol);
};

#endif //EX2_CHESS_PIECE_H

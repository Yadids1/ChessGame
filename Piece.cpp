/**
 * This class represent piece in a chess board
 * there is 6 types of pieces: pawn, king, queen, knight, bishop and rook.
 * each type have represented by derived class inherit piece class.
 * all the pieces have common characteristics: color, position and type.
 * Each of the six piece types moves differently therfore each derive class implement
 * 2 virtual method differently.
 */
#include "Piece.h"

/**
     * piece constructor
     * @param color - piece color - white or black
     * @param rowPos - piece first row position
     * @param colPos - piece first column position
     * @param type - piece type
     */
Piece::Piece(char color, int rowPos, int colPos, std::string type)
{
    _color = color;
    _rowPos = rowPos;
    _colPos = colPos;
    _type = type;
}

/**
     * @brief virtual destructor of piece
     */
Piece::~Piece()
{
}

/**
   *
   * @return this piece color: 'W' - for white piece, 'B' - for black piece
   */
char Piece::getColor()
{
    return _color;
}

/**
    * @return this piece row position;
    */
int Piece::getRowPos()
{
    return _rowPos;
}

/**
    * @return this piece column position;
    */
int Piece::getColPos()
{
    return _colPos;
}

/**
     * @return this piece type: pawn, king, queen, knight, bishop or rook.
     */
std::string Piece::getType()
{
    return _type;
}

/**
     * set new position for this piece
     * @param newRow - destination row
     * @param newCol - destination column
     */
void Piece::setPos(int newRow, int newCol)
{
    _colPos = newCol;
    _rowPos = newRow;
}

/**
     * check if row and col input is inside board borders
     * @param destRow - row input
     * @param destCol - column input
     * @return true if the position is legal, false otherwise
     */
bool Piece::isSlotOutOfBoard(int destRow, int destCol)
{
    if (destRow < 0 || destRow > 7 || destCol < 0 || destCol > 7)
    {
        return false;
    }
    return true;
}

/**
     * @return true if the piece already moved, false otherwise
     */
bool Piece::getFirstMove()
{
    return _makeFirstMove;
}

/**
     * update that the piece make his first move
     */
void Piece::setFirstMove()
{
    _makeFirstMove = true;
}

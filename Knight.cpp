/**
 * represent Knight piece
 */
#include <assert.h>
#include "Piece.h"

/**
    * knight piece constructor
    * @param color - piece color - white or black
    * @param rowPos - piece first row position
    * @param colPos - piece first column position
    * @param type - piece type
    */
    Knight::Knight(char color, int rowPos, int colPos, std::string type) :
            Piece(color, rowPos, colPos, type)
    {
    }

/**
    * check if the input position is legal for the Knight.
     * The knight moves to any of the closest squares that are not on the same rank, file, or
     * diagonal, thus the move forms an "L"-shape: two squares vertically and one square horizontally,
     * or two squares horizontally and one square vertically.
     * @param destRow - row new position
     * @param destCol - column new position
     * @return true if this movement is legal, false otherwise
     */
    bool Knight::isLegalMove(int destRow, int destCol)
    {
        if (!isSlotOutOfBoard(destRow, destCol))
        {
            return false;
        }
        if (getColPos() == destCol && getRowPos() == destRow)
        {
            return false;
        }
        if ((std::abs(getRowPos() - destRow) == 2 && std::abs(getColPos() - destCol) == 1))
        {
            return true;
        }
            else if (std::abs(getRowPos() - destRow) == 1 && std::abs(getColPos() - destCol) == 2)
            {
                return true;
            }
        return false;
    }

/**
    * get a position, and find all the slots that this piece need to skip over in order to arrive
    * to the new position
    * @param destRow - row new position
    * @param destCol - column new position
    * @return empty vector - The knight is the only piece that can leap over other pieces.
    */
    std::vector<int> Knight::slotsInTheWay(int destRow, int destCol)
    {
        std::vector<int> slots;
        return slots;
        assert(destRow);
        assert(destCol);
    }
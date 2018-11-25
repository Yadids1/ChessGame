/**
 * represent king piece
 */
#include <stdlib.h>
#include <assert.h>
#include "Piece.h"

/**
     * king piece constructor
     * @param color - piece color - white or black
     * @param rowPos - piece first row position
     * @param colPos - piece first column position
     * @param type - piece type
     */
King::King(char color, int rowPos, int colPos, std::string type) :
            Piece(color, rowPos, colPos, type)
    {
    }

/**
    * check if the input position is legal for the king.
     * The king moves one square in any direction.
     * @param destRow - row new position
     * @param destCol - column new position
     * @return true if this movement is legal, false otherwise
     */
    bool King::isLegalMove(int destRow, int destCol)
    {
        if (!isSlotOutOfBoard(destRow, destCol))
        {
            return false;
        }
        if (getColPos() == destCol && getRowPos() == destRow)
        {
            return false;
        }
        if (std::abs(getRowPos() - destRow) <= 1)
        {
            if (std::abs(getColPos() - destCol) <= 1)
            {
                return true;
            }
        }
        return false;
    }

/**
     * get a position, and find all the slots that this piece need to skip over in order to arrive
     * to the new position
     * @param destRow - row new position
     * @param destCol - column new position
     * @return empty vector - the king cant leap more than one slot (except castling)
     */
    std::vector<int> King::slotsInTheWay(int destRow, int destCol)
    {
        std::vector<int> slots;
        return slots;
        assert(destRow);
        assert(destCol);
    }
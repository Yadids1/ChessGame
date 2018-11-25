/**
 * represent Bishop piece
 */
#include "Piece.h"

/**
* Bishop piece constructor
* @param color - piece color - white or black
* @param rowPos - piece first row position
* @param colPos - piece first column position
* @param type - piece type
*/
    Bishop::Bishop(char color, int rowPos, int colPos, std::string type) :
            Piece(color, rowPos, colPos, type)
    {
    }

/**
   * check if the input position is legal for the Bishop,
    * The bishop can move any number of squares diagonally,
    * @param destRow - row new position
    * @param destCol - column new position
    * @return true if this movement is legal, false otherwise
    */
    bool Bishop::isLegalMove(int destRow, int destCol)
    {
        if (!isSlotOutOfBoard(destRow, destCol))
        {
            return false;
        }
        if (getColPos() == destCol && getRowPos() == destRow)
        {
            return false;
        }
        if (std::abs(getRowPos() - destRow) == std::abs(getColPos() - destCol))
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
     * @return vector included the slots position in pairs, firstly row position
     * and after the column position.
     */
    std::vector<int> Bishop::slotsInTheWay(int destRow, int destCol)
    {
        std::vector<int> slots;
        for (int i = 1 ; i < std::abs(getRowPos() - destRow); i++)
        {
            if (getRowPos() > destRow && getColPos() > destCol)
            {
                slots.push_back(getRowPos() - i);
                slots.push_back(getColPos() - i);
            }
            else if (getRowPos() > destRow && getColPos() < destCol)
            {
                slots.push_back(getRowPos() - i);
                slots.push_back(getColPos() + i);
            }
            else if (getRowPos() < destRow && getColPos() < destCol)
            {
                slots.push_back(getRowPos() + i);
                slots.push_back(getColPos() + i);
            }
            else if (getRowPos() < destRow && getColPos() > destCol)
            {
                slots.push_back(getRowPos() + i);
                slots.push_back(getColPos() - i);
            }
        }
        return slots;
    }
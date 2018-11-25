/**
 * represent Rook piece
 */
#include "Piece.h"

/**
     * Rook piece constructor
     * @param color - piece color - white or black
     * @param rowPos - piece first row position
     * @param colPos - piece first column position
     * @param type - piece type
     */
    Rook::Rook(char color, int rowPos, int colPos, std::string type) :
            Piece(color, rowPos, colPos, type)
    {
    }

/**
   * check if the input position is legal for the Rook.
    * The rook can move any number of squares along any rank or file
    * @param destRow - row new position
    * @param destCol - column new position
    * @return true if this movement is legal, false otherwise
    */
    bool Rook::isLegalMove(int destRow, int destCol)
    {
        if (!isSlotOutOfBoard(destRow, destCol))
        {
            return false;
        }
        if (getRowPos() == destRow || getColPos() == destCol)
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
    std::vector<int> Rook::slotsInTheWay(int destRow, int destCol)
    {
        std::vector<int> slots;
        for (int i = 1; i < std::abs(getRowPos() - destRow + getColPos() - destCol); i++)
        {
            if (getRowPos() == destRow)
            {
                slots.push_back(getRowPos());
                if (getColPos() > destCol)
                {
                    slots.push_back(getColPos() - i);
                }
                else
                {
                    slots.push_back(getColPos() + i);
                }
            }
            else
            {
                if (getRowPos() > destRow)
                {
                    slots.push_back(getRowPos() - i);
                }
                else
                {
                    slots.push_back(getRowPos() + i);
                }
                slots.push_back(getColPos());
            }
        }
        return slots;
    }
/**
 * represent Queen piece
 */
#include "Piece.h"

/**
    * Queen piece constructor
    * @param color - piece color - white or black
    * @param rowPos - piece first row position
    * @param colPos - piece first column position
    * @param type - piece type
    */
    Queen::Queen(char color, int rowPos, int colPos, std::string type) :
            Piece(color, rowPos, colPos, type)
    {
    }

/**
  * check if the input position is legal for the Queen.
   * The queen combines the power of the rook and bishop and can move any number of squares
   * along rank, file, or diagonal
   * @param destRow - row new position
   * @param destCol - column new position
   * @return true if this movement is legal, false otherwise
   */
    bool Queen::isLegalMove(int destRow, int destCol)
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
        if (getRowPos() == destRow || getColPos() == destCol)
        {
            return true;
        }
        if (std::abs(getRowPos() - destRow) <= 1 && std::abs(getColPos() - destCol) <= 1)
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
    std::vector<int> Queen::slotsInTheWay(int destRow, int destCol)
    {
        std::vector<int> slots;
        if (std::abs(getRowPos() - destRow) <= 1 && std::abs(getColPos() - destCol) <= 1)
        {
            return slots;
        }
        else if (getRowPos() == destRow || getColPos() == destCol)
        {
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
        }
        else
        {
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
        }
        return slots;
    }


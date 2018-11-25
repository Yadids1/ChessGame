
/**
 * represent Pawn piece
 */
#include "Piece.h"

/**
    * Pawn piece constructor
    * @param color - piece color - white or black
    * @param rowPos - piece first row position
    * @param colPos - piece first column position
    * @param type - piece type
    */
    Pawn::Pawn(char color, int rowPos, int colPos, std::string type) :
            Piece(color, rowPos, colPos, type)
    {
    }

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
    bool Pawn::isLegalMove(int destRow, int destCol)
    {
        if (!isSlotOutOfBoard(destRow, destCol))
        {
            return false;
        }
        if (getColor() == 'W')
        {
            if (destRow == getRowPos() + 1 && std::abs(destCol - getColPos()) == 1) //eat other piece
            {
                return true;
            }
            if (getRowPos() == 1)
            {
                return (destCol == getColPos() && (destRow == 2 || destRow == 3));
            }
            if (getRowPos() > 1 && getRowPos() < 7)
            {
                return (destRow == getRowPos() + 1 && (destCol == getColPos() ||
                        std::abs(getColPos() - destCol) == 1));
            }
        }
        else if (getColor() == 'B')
        {
            if (destRow == getRowPos() - 1 && std::abs(destCol - getColPos()) == 1) //eat other piece
            {
                return true;
            }
            if (getRowPos() == 6)
            {
                return (destCol == getColPos() && (destRow == 4 || destRow == 5));
            }
            if (getRowPos() > 0 && getRowPos() < 6)
            {
                return (destRow == getRowPos() - 1 && (destCol == getColPos() ||
                        std::abs(getColPos() - destCol) == 1));
            }
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
    std::vector<int> Pawn::slotsInTheWay(int destRow, int destCol)
    {
        std::vector<int> slots;
        if(getColPos() == destCol && std::abs(getRowPos() - destRow) == 2)
        {
            slots.push_back((getRowPos() + destRow) / 2);
            slots.push_back(destCol);
        }
        return slots;
    }

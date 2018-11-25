#include "Board.h"

#define PAWN "Pawn"
#define ROOK "Rook"
#define KNIGHT "Knight"
#define BISHOP "Bishop"
#define QUEEN "Queen"
#define KING "king"
#define WHITE 'W'
#define BLACK 'B'
#define COL_NUM "  ABCDEFGH\n"
#define OPEN "\33["
#define CLOSE "\33[0m"
#define GREEN_BKGR ";42m"
#define BLUE_BKGR ";46m"
#define WHITE_CODE "37"
#define BLACK_CODE "30"

using namespace std;

/**
     * constructor of the board
     */
Board::Board()
{
    initBoard();
}

/**
    * destructor of the board
    */
Board::~Board()
{
    for (Piece* myPiece : whitePieces)
    {
        delete(myPiece);
    }
    for (Piece* myPiece : blackPieces)
    {
        delete(myPiece);
    }
}

/**
     * init new game board. Each player begins the game with 16 pieces: one king, one queen,
     * two rooks, two knights, two bishops, and eight pawns
     */
void Board::initBoard()
{
    for(int i = 0; i < 8; i++)
    {
        std::vector<Piece*> row;
        thisBoard.push_back(row);
    }
    for (int j = 2; j < 6; j++)
    {
        for (int k = 0; k < 8 ; k++)
        {
            thisBoard[j].push_back(nullptr);
        }
    }
    for (int i = 0; i < 8; i++)
    {
        thisBoard[6].push_back(new Pawn(BLACK, 6, i, PAWN));
        thisBoard[1].push_back(new Pawn(WHITE, 1, i, PAWN));
        blackPieces.push_back(thisBoard[6][i]);
        whitePieces.push_back(thisBoard[1][i]);
    }
    thisBoard[7].push_back(new Rook(BLACK, 7, 0, ROOK));
    thisBoard[7].push_back(new Knight(BLACK, 7, 1, KNIGHT));
    thisBoard[7].push_back(new Bishop(BLACK, 7, 2, BISHOP));
    thisBoard[7].push_back(new Queen(BLACK, 7, 3, QUEEN));
    _blackKing = new King(BLACK, 7, 4, KING);
    thisBoard[7].push_back(_blackKing);
    thisBoard[7].push_back(new Bishop(BLACK, 7, 5, BISHOP));
    thisBoard[7].push_back(new Knight(BLACK, 7, 6, KNIGHT));
    thisBoard[7].push_back(new Rook(BLACK, 7, 7, ROOK));
    thisBoard[0].push_back(new Rook(WHITE, 0, 0, ROOK));
    thisBoard[0].push_back(new Knight(WHITE, 0, 1, KNIGHT));
    thisBoard[0].push_back(new Bishop(WHITE, 0, 2, BISHOP));
    thisBoard[0].push_back(new Queen(WHITE, 0, 3, QUEEN));
    _whiteKing = new King(WHITE, 0, 4, KING);
    thisBoard[0].push_back(_whiteKing);
    thisBoard[0].push_back(new Bishop(WHITE, 0, 5, BISHOP));
    thisBoard[0].push_back(new Knight(WHITE, 0, 6, KNIGHT));
    thisBoard[0].push_back(new Rook(WHITE, 0, 7, ROOK));
    for (int j = 0; j < 8; j++)
    {
        whitePieces.push_back(thisBoard[0][j]);
        blackPieces.push_back(thisBoard[7][j]);
    }
}

/**
     * get a slot and return the piece exist in it or a null pointer if this slot is empty
     * @param row - row position
     * @param col - column position
     * @return the piece exist in it or a null pointer if this slot is empty
     */
Piece* Board::getPiece(int row, int col)
{
    return thisBoard[row][col];
}

/**
     * this function give a number for each piece type;
     * @param type of the piece
     * @return 0 for king, 1 for queen, 2 for rook, 3 for bishop, 4 knight, 5 pawn, -1 otherwise
     */
int Board::_hashPiece(std::string type)
{
    if (type == KING)
    {
        return 0;
    }
    if (type == QUEEN)
    {
        return 1;
    }
    if (type == ROOK)
    {
        return 2;
    }
    if (type == BISHOP)
    {
        return 3;
    }
    if (type == KNIGHT)
    {
        return 4;
    }
    if (type == PAWN)
    {
        return 5;
    }
    return -1;
}


/**
 * print one slot in the board (with a piece or empty)
 * @param row - row position
 * @param col  - column position
 */
void Board::printSlot(int row, int col)
{
    Piece* myPiece = getPiece(row, col);
    string slotColor;
    if ((row + col) % 2 == 0)
    {
        slotColor = GREEN_BKGR;
    }
    else
    {
        slotColor = BLUE_BKGR;
    }
    if (myPiece == nullptr)
    {
        cout << OPEN << 0 << slotColor << " " << CLOSE;
    }
    else
    {
        string pieceColor;
        if (myPiece->getColor() == 'W')
        {
            pieceColor = WHITE_CODE;
        }
        else
        {
            pieceColor = BLACK_CODE;
        }
        string typeSlot;
        typeSlot = unicodePieces[0][_hashPiece(myPiece->getType())];
        cout << OPEN << pieceColor << slotColor << typeSlot << CLOSE;
    }
}

/**
     * print the game board to the screen
     */
void Board::printBoard()
{
    cout << COL_NUM << endl;
    for (int i = 7; i >= 0; i--)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < 8; j++)
        {
            printSlot(i, j);
        }
        cout << " " << i + 1 << endl;
    }
    cout <<  endl << COL_NUM << endl;
}

/**
     * get a piece and new destination slot and make the movement
     * @param myPiece - this piece
     * @param destRow - row destination
     * @param destCol - column destination
     */
void Board::move(Piece* myPiece, int destRow, int destCol)
{
    thisBoard[myPiece->getRowPos()][myPiece->getColPos()] = nullptr;
    putPiece(myPiece, destRow, destCol);
}

/**
     * get position and remove the piece exist on this slot
     * @param row - row position
     * @param col  - column position
     * @param color - the piece color
     */
void Board::eatPiece(int row, int col, char color)
{
    int index = 0;
    if (color == WHITE)
    {
        for (Piece* pieceToRemove : whitePieces)
        {
            if (pieceToRemove->getColPos() == col && pieceToRemove->getRowPos() == row)
            {
                delete(pieceToRemove);
                whitePieces.erase(whitePieces.begin() + index);
                break;
            }
            index++;
        }
    }
    else
    {
        for (Piece* pieceToRemove : blackPieces)
        {
            if (pieceToRemove->getColPos() == col && pieceToRemove->getRowPos() == row)
            {
                delete(pieceToRemove);
                blackPieces.erase(blackPieces.begin() + index);
                break;
            }
            index++;
        }
    }
    thisBoard[row][col] = nullptr;
}

/**
     * get slot position destination and Piece, and check if this piece can land in that slot
     * @param sourcePiece - the piece
     * @param row - row destination
     * @param col - column destination
     * @param color - the piece color
     * @param isDiagaonalPawn - indicate if this piece is pawn and that move is diagonaly
     * @return true if the land on this slot is legal, false otherwise
     */
bool Board::checkDestinationMove(Piece* sourcePiece, int row, int col, char color,
                                 bool isDiagaonalPawn)
{
    Piece* myPiece = getPiece(row, col);
    if (myPiece == nullptr && !isDiagaonalPawn)
    {
        return true;
    }
    else if (isDiagaonalPawn && myPiece == nullptr)
    {
        return false;
    }
    else if (myPiece->getColor() == color)
    {
        return false;
    }
    else if (myPiece != nullptr && sourcePiece->getType() == PAWN && !isDiagaonalPawn)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
    * get slot position when a pawn advances to the eighth rank, as a part of the move it is
    * promoted and exchanged this pawn for queen,
   * @param row - row position
    * @param col  - column position
    */
void Board::setQueen(int row, int col)
{
    if (row == 7)
    {
        Piece* newQueen = new Queen(WHITE, row, col, QUEEN);
        thisBoard[row][col] = newQueen;
        whitePieces.push_back(newQueen);
    }
    else if (row == 0)
    {
        Piece* newQueen = new Queen(BLACK, row, col, QUEEN);
        thisBoard[row][col] = newQueen;
        blackPieces.push_back(newQueen);
    }
}

/**
     * get piece and vector of position and determine if that piece can leap over this slots;
     * @param slotToCheck - the slots lost composed from pairs of row and column.
     * @return true if the piece can leap over this slots, false otherwise
     */
bool Board::checkMoveLeggality(std::vector<int> slotToCheck)
{
    if (slotToCheck.empty())
    {
        return true;
    }
    else
    {
        while (!slotToCheck.empty())
        {
            int row = slotToCheck[0];
            int col = slotToCheck[1];
            Piece* myPiece = getPiece(row, col);
            if (myPiece != nullptr)
            {
                return false;
            }
            slotToCheck.erase(slotToCheck.begin(), slotToCheck.begin() + 2);
        }
    }
    return true;
}

/**
 * get piece and slot position, and put this piece in this slot
 * @param myPiece - this piece
 * @param row - row position
 * @param col  - column position
 */
void Board::putPiece(Piece* myPiece, int row, int col)
{
    thisBoard[row][col] = myPiece;
    if (myPiece != nullptr)
    {
        myPiece->setPos(row, col);
    }
}

/**
    * @return the white king piece
    */
Piece* Board::getWhiteKing()
{
    return _whiteKing;
}

/**
     * @return the black king piece
     */
Piece* Board::getBlackKing()
{
    return _blackKing;
}


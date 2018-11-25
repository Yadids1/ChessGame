/**
 * this class contain the main chess game code
 * using board class and piece classes
 */
#include <iostream>
#include "Board.h"

#define PAWN "Pawn"
#define ROOK "Rook"
#define KNIGHT "Knight"
#define BISHOP "Bishop"
#define QUEEN "Queen"
#define KING "king"
#define WHITE 'W'
#define BLACK 'B'
#define PLAYER1MSG "Enter white player name:"
#define PLAYER2MSG "Enter black player name:"
#define CLEAN "\33[2J"
#define CHESS_MSG "\33[37;41mCheck!\33[0m"
#define MOVE_MSG ": Please enter your move:"
#define WON_MSG " won!"
#define ILLEGAL_MOVE "\33[37;41millegal move\33[0m"

using namespace std;

/* the chess board */
Board *gameBoard;

/* player 1 name */
string player1Name;

/* player 2 name */
string player2Name;

/* represent the current player in this turn */
string curPlayer;

/* boolean variable indicate if the game is over (checkmate) */
bool wasCheckMate = false;

/**
 * get the input movement, and check if this validate move struction
 * @param input the string inpur
 * @param r1 put in it the source row
 * @param c1 put in in the source column
 * @param r2  put in it the row destination
 * @param c2 put in in the column destination
 * @return true if the move is valid, false otherwise
 */
bool inputProccess(string input, int& r1, int& c1, int& r2, int& c2)
{
    if (input.length() != 4)
    {
        return false;
    }
    c1 = input[0] - 'A';
    c2 = input[2] - 'A';
    r1 = input[1] - '1';
    r2 = input[3] - '1';
    if (r1 > 7 || r2 > 7 || c1 > 7 || c2 > 7)
    {
        return false;
    }
    if (r1 < 0 || r2 < 0 || c1 < 0 || c2 < 0)
    {
        return false;
    }
    return true;
}

/**
 * get a piece and slot destination, and determine if is legal movement in this board
 * @param myPiece the piece
 * @param destRow row destination
 * @param destCol column destination
 * @return true if the movement is legal, false otherwise
 */
bool isPossibleMove(Piece* myPiece, int destRow, int destCol)
{
    if (!myPiece->isLegalMove(destRow, destCol))
    {
        return false;
    }
    std::vector<int> slotToCheck = myPiece->slotsInTheWay(destRow, destCol);
    if (!gameBoard->checkMoveLeggality(slotToCheck))
    {
        return false;
    }
    bool isDiagonalPawn = false;
    if (myPiece->getColPos() != destCol && myPiece->getType() == PAWN)
    {
        isDiagonalPawn = true;
    }
    if (!gameBoard->checkDestinationMove(myPiece, destRow, destCol,
        myPiece->getColor(), isDiagonalPawn))
    {
        return false;
    }
    return true;
}

/**
 * get a color player, and return if there is a chess threat of this color king.
 * @param color white or black
 * @return true if this color in chess situation, false otherwise
 */
bool checkCheck(char color)
{
    int rowPos;
    int colPos;
    std::vector<Piece*> thisVector;
    if (color == WHITE)
    {
        rowPos = gameBoard->getWhiteKing()->getRowPos();
        colPos = gameBoard->getWhiteKing()->getColPos();
        thisVector = gameBoard->blackPieces;
    }
    else
    {
        rowPos = gameBoard->getBlackKing()->getRowPos();
        colPos = gameBoard->getBlackKing()->getColPos();
        thisVector = gameBoard->whitePieces;
    }
    for (Piece* myPiece : thisVector)
    {
        if (isPossibleMove(myPiece, rowPos, colPos))
        {
            return true;
        }
    }
    return false;
}

/**
 * get a piece and destination position, and determine if this movement cause a check to
 * the king of this player
 * @param myPiece the piece
 * @param destRow row destination
 * @param destCol column destination
 * @param color piece color
 * @return
 */
bool causeCheck(Piece *myPiece, int destRow, int destCol, char color)
{
    bool chess = false;
    int r1 =  myPiece->getRowPos(), c1 =  myPiece->getColPos();
    Piece* sourceDestPiece = gameBoard->getPiece(destRow, destCol);
    gameBoard->putPiece(myPiece, destRow, destCol);
    gameBoard->putPiece(nullptr, r1, c1);
    if (checkCheck(color))
    {
        chess = true;
    }
    gameBoard->putPiece(myPiece, r1, c1);
    gameBoard->putPiece(sourceDestPiece, destRow, destCol);
    return chess;
}

/**
 * determine if there is a checkmate namely when one of the kings is in check,
 * and there is no legal way to remove it from attack.
 * @param color - the color of underattack king
 * @return true if there is checkmate, false if there is a legal way to exit from the attack
 */
bool checkMate(char color)
{
    int rowPos;
    int colPos;
    Piece* curKing;
    if (color == WHITE)
    {
        rowPos = gameBoard->getWhiteKing()->getRowPos();
        colPos = gameBoard->getWhiteKing()->getColPos();
        curKing = gameBoard->getWhiteKing();
    }
    else
    {
        rowPos = gameBoard->getBlackKing()->getRowPos();
        colPos = gameBoard->getBlackKing()->getColPos();
        curKing = gameBoard->getBlackKing();
    }
    if (isPossibleMove(curKing, rowPos + 1, colPos + 1) && !causeCheck(curKing, rowPos + 1, colPos + 1, color))
    {
        return false;
    }
    if (isPossibleMove(curKing, rowPos + 1, colPos) && !causeCheck(curKing, rowPos + 1, colPos, color))
    {
        return false;
    }
    if (isPossibleMove(curKing, rowPos + 1, colPos - 1) && !causeCheck(curKing, rowPos + 1, colPos - 1, color))
    {
        return false;
    }
    if (isPossibleMove(curKing, rowPos, colPos + 1) && !causeCheck(curKing, rowPos, colPos + 1, color))
    {
        return false;
    }
    if (isPossibleMove(curKing, rowPos, colPos - 1) && !causeCheck(curKing, rowPos, colPos - 1, color))
    {
        return false;
    }
    if (isPossibleMove(curKing, rowPos - 1, colPos + 1) && !causeCheck(curKing, rowPos - 1, colPos + 1, color))
    {
        return false;
    }
    if (isPossibleMove(curKing, rowPos - 1, colPos - 1) && !causeCheck(curKing, rowPos - 1, colPos - 1, color))
    {
        return false;
    }
    if (isPossibleMove(curKing, rowPos - 1, colPos) && !causeCheck(curKing, rowPos - 1, colPos, color))
    {
        return false;
    }
    return true;

}

/**
 * get a piece and destination slot, and make the move
 * @param myPiece the piece
 * @param destRow row destination
 * @param destCol column destination
 */
void makeMove(Piece* myPiece, int destRow, int destCol)
{
    char otherColor;
    if (myPiece->getColor() == WHITE)
    {
        otherColor = BLACK;
    }
    else
    {
        otherColor = WHITE;
    }
    if ((destRow == 7 && myPiece->getType() == PAWN && myPiece->getColor() == WHITE) ||
        (destRow == 0 && myPiece->getType() == PAWN && myPiece->getColor() == BLACK))
    {
        if (gameBoard->getPiece(destRow, destCol) != nullptr)
        {
            gameBoard->eatPiece(destRow, destCol, otherColor);
        }
        gameBoard->eatPiece(myPiece->getRowPos(), myPiece->getColPos(), myPiece->getColor());
        gameBoard->setQueen(destRow, destCol);
    }
    else
    {
        if (gameBoard->getPiece(destRow, destCol) != nullptr)
        {
            gameBoard->eatPiece(destRow, destCol, otherColor);
        }
        gameBoard->move(myPiece, destRow, destCol);
    }
    if ((myPiece->getType() == KING || myPiece->getType() == ROOK) && !myPiece->getFirstMove())
    {
        myPiece->setFirstMove();
    }
}

/**
 * preocess the input movement when the player want to make castling
 * @param input - the string movement input
 * @param r1 put in it the king sourse row position
 * @param c1 put in it the king sourse column position
 * @param r2 put in it the king destination row position
 * @param c2 put in it the king destination column position
 * @param r3 put in it the rook sourse row position
 * @param c3 put in it the rook sourse column position
 * @param r4 put in it the rook destination row position
 * @param c4 put in it the rook destination column position
 * @return true if this input represent valid castling, false otherwise
 */
bool castlingInput(string input, int& r1, int& c1, int& r2, int& c2, int& r3, int& c3, int& r4, int& c4)
{
    if (input.length() == 3 && input == "0-0")
    {
        c1 = 4, c2 = 6, c3 = 7, c4 = 5;
        if (curPlayer == player1Name)
        {
            r1 = 0, r2 = 0, r3 = 0, r4 = 0;
        }
        else
        {
            r1 = 7, r2 = 7, r3 = 7, r4 = 7;
        }
        return true;
    }
    else if (input.length() == 5 && input == "0-0-0")
    {
        c1 = 4, c2 = 2, c3 = 0, c4 = 3;
        if (curPlayer == player1Name)
        {
            r1 = 0, r2 = 0, r3 = 0, r4 = 0;
        }
        else
        {
            r1 = 7, r2 = 7, r3 = 7, r4 = 7;
        }
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * this method check if castling is legal in the board
 * @param myPiece1 the king
 * @param myPiece2  the rook
 * @param r1 king row position
 * @param c1 king column position
 * @param c2 king column destination
 * @param curColor current player color
 * @return true if the castling is legal in the board
 */
bool makeCastling(Piece* myPiece1, Piece* myPiece2, const int r1, const int c1, const int c2, char curColor)
{
    bool goodMove = true;
    if (myPiece1->getFirstMove() || myPiece2->getFirstMove())
    {
        goodMove = false;
    }
    if (checkCheck(curColor))
    {
        goodMove = false;
    }
    Piece* myPiece3;
    int nextSlotCol;
    if (c2 > c1)
    {
        nextSlotCol = c1 + 1;
    }
    else
    {
        nextSlotCol = c1 - 1;
    }
    myPiece3 = gameBoard->getPiece(r1, nextSlotCol);
    if (myPiece3 != nullptr)
    {
        goodMove = false;
    }
    else
    {
        gameBoard->putPiece(myPiece1, r1, nextSlotCol);
        if (checkCheck(curColor))
        {
            goodMove = false;
        }
        gameBoard->putPiece(nullptr, r1, nextSlotCol);
        if (goodMove)
        {
            if (nextSlotCol > c1)
            {
                nextSlotCol++;
            }
            else
            {
                nextSlotCol--;
            }
            myPiece3 = gameBoard->getPiece(r1, nextSlotCol);
            if (myPiece3 != nullptr)
            {
                goodMove = false;
            }
            else
            {
                gameBoard->putPiece(myPiece1, r1, nextSlotCol);
                if (checkCheck(curColor))
                {
                    goodMove = false;
                }
                gameBoard->putPiece(nullptr, r1, nextSlotCol);
            }
        }
        if (goodMove && nextSlotCol < c1)
        {
            nextSlotCol--;
            myPiece3 = gameBoard->getPiece(r1, nextSlotCol);
            if (myPiece3 != nullptr)
            {
                goodMove = false;
            }
            else
            {
                gameBoard->putPiece(myPiece1, r1, nextSlotCol);
                if (checkCheck(curColor))
                {
                    goodMove = false;
                }
                gameBoard->putPiece(nullptr, r1, nextSlotCol);
            }
        }
        gameBoard->putPiece(myPiece1, r1, c1);
    }
    return goodMove;
}

/**
 * this method represent one round of one player in the chess game.
 * the method read an input movement from the player,
 * check if it is a legal movement and if indeed make the movement.
 * in addition the method check if one of the kings is under attack and announce
 * to the player.
 */
void oneRound()
{
    cout << CLEAN;
    gameBoard->printBoard();
    char curColor;
    if (curPlayer == player1Name)
    {
        curColor = WHITE;
    }
    else
    {
        curColor = BLACK;
    }
    if (checkCheck(curColor))
    {
        if (checkMate(curColor))
        {
            if (curPlayer == player1Name)
            {
                curPlayer = player2Name;
            }
            else
            {
                curPlayer = player1Name;
            }
            cout << curPlayer << WON_MSG << endl;
            wasCheckMate = true;
            return;
        }
        cout << CHESS_MSG << endl;
    }
    string input;
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    bool goodMove = false;
    while (!goodMove)
    {
        cout << curPlayer << MOVE_MSG << endl;
        cin >> input;
        if (input[0] != '0')
        {
            goodMove = inputProccess(input, r1, c1, r2, c2);
            while (!goodMove)
            {
                cout << ILLEGAL_MOVE << endl;
                cout << CLEAN;
                gameBoard->printBoard();
                cin >> input;
                goodMove = inputProccess(input, r1, c1, r2, c2);
            }
            Piece* myPiece = gameBoard->getPiece(r1, c1);
            if (myPiece == nullptr || myPiece->getColor() != curColor)
            {
                goodMove = false;
            }
            if (goodMove && !isPossibleMove(myPiece, r2, c2))
            {
                goodMove = false;
            }
            if (goodMove)
            {
                goodMove = !causeCheck(myPiece, r2, c2, curColor);
            }
            if (goodMove)
            {
                makeMove(gameBoard->getPiece(r1, c1), r2, c2);
                gameBoard->putPiece(nullptr, r1, c1);
            }
        }
        else
        {
            int r3 = 0, c3 = 0, r4 = 0, c4 = 0;
            goodMove = castlingInput(input, r1, c1, r2, c2, r3, c3, r4, c4);
            if (goodMove)
            {
                Piece *myPiece1 = gameBoard->getPiece(r1, c1); //king
                Piece *myPiece2 = gameBoard->getPiece(r3, c3);  //rook
                goodMove = makeCastling(myPiece1, myPiece2, r1, c1, c2, curColor);
                if (goodMove)
                {
                    makeMove(myPiece1, r2, c2);
                    makeMove(myPiece2, r4, c4);
                }
            }
        }
        if (!goodMove)
        {
            cout << ILLEGAL_MOVE << endl;
            cout << CLEAN;
            gameBoard->printBoard();
        }
    }
}

/**
 * the main method. get the player names, and use oneRound method to make the game
 * @return
 */
int main()
{
    gameBoard = new Board();
    cout << PLAYER1MSG << endl;
    cin >> player1Name;
    cout << PLAYER2MSG << endl;
    cin >> player2Name;
    curPlayer = player1Name;
    while (!wasCheckMate)
    {
        oneRound();
        if (curPlayer == player1Name)
        {
            curPlayer = player2Name;
        }
        else
        {
            curPlayer = player1Name;
        }
    }
    delete(gameBoard);
    return 0;
}


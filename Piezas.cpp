#include "Piezas.h"
#include <vector>
#include <iostream>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    turn = X;
    reset();
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    board.clear();
    board.resize(BOARD_COLS);
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    Piece currentTurn;
    currentTurn = turn;
    // change turn
    (turn == X) ? turn = O : turn = X;
    // if column out of bounds
    if (column >= BOARD_COLS || column < 0 ) {
        return Invalid;
    }
    if (board[column].size() < BOARD_ROWS) {
        // place piece
        board[column].push_back(currentTurn);
        return currentTurn;
    }  else {
        // do not place if column is full
        return Blank;
    }
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
     // if out of bounds
    if ((column >= BOARD_COLS || column < 0) || (row >= BOARD_ROWS || row < 0)) {
        return Invalid;
    }
     if (board[column].empty()) {
        return Blank;
    }
    if (board[column][row] == X || board[column][row] == O) {
        return board[column][row];
    }
    return Blank;
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    // // if game not over, return invalid
    for (int i = 0; i < BOARD_COLS; i++) {
        if(board[i].size() != BOARD_ROWS) {
            return Invalid;
        }
    }
    // game is filled
    // check for winner
    int maxXCount = 0;
    int maxOCount = 0;
    // check vertical
    for(int i = 0; i < BOARD_COLS; i++) {
        int xCounter = 0;
        int oCounter = 0;
        Piece lastPiece = board[i][0];
        for (int j = 0; j < BOARD_ROWS; j++) {
            // if first piece, also set to lastPiece
            if (board[i][j] == X) {
                oCounter = 0;
                if (lastPiece == X) {
                    xCounter++;
                    if (xCounter > maxXCount) {
                        maxXCount = xCounter;
                    }
                }
                lastPiece = X;
            } else if (board[i][j] == O) {
                xCounter = 0;
                if (lastPiece == O) {
                    oCounter++;
                    if (oCounter > maxOCount) {
                        maxOCount = oCounter;
                    }
                }
                lastPiece = O;
            }
        }
    }
    // // check horizontal
    for (int i = 0; i < BOARD_ROWS; i++) {
        int xCounter = 0;
        int oCounter = 0;
        Piece lastPiece = board[0][i];
        for (int j = 0; j < BOARD_COLS; j++) {
            // if first piece, also set to lastPiece
            if (board[j][i] == X) {
                oCounter = 0;
                 if (lastPiece == X) {
                    xCounter++;
                    if (xCounter > maxXCount) {
                        maxXCount = xCounter;
                    }
                }
                lastPiece = X;
            }
            if (board[j][i] == O){
                xCounter = 0;
                  if (lastPiece == O) {
                    oCounter++;
                    if (oCounter > maxOCount) {
                        maxOCount = oCounter;
                    }
                }
                lastPiece = O;
            }
        }
    }
    // if tie return Blank
    if (maxXCount == maxOCount) {
        return Blank;
    }
    Piece winner = (maxOCount > maxXCount) ? O : X;
    return (winner);
}
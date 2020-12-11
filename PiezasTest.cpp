/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, dropPieceGetTurnValid)
{
	Piezas board;
	board.dropPiece(1);
	ASSERT_TRUE(board.dropPiece(1) == O);
}

TEST(PiezasTest, dropPieceOutOfBounds)
{
	Piezas board;
	int outOfBounds = BOARD_COLS + 3;
	ASSERT_TRUE(board.dropPiece(outOfBounds) == Invalid);
}

TEST(PiezasTest, dropPieceFullColumn)
{
	Piezas board;
	for(int i = 0; i < BOARD_ROWS; i++) {
		// fill column 1
		board.dropPiece(1);
	}
	ASSERT_TRUE(board.dropPiece(1) == Blank);
}

TEST(PiezasTest, dropPieceValid)
{
	Piezas board;
	ASSERT_TRUE(board.dropPiece(1) == X);
}


TEST(PiezasTest, pieceAtInvalidColumn) 
{
	Piezas board;
	ASSERT_TRUE(board.pieceAt(0, BOARD_COLS) == Invalid);
	ASSERT_TRUE(board.pieceAt(0, BOARD_COLS + 2) == Invalid);
}
TEST(PiezasTest, pieceAtInvalidRow) 
{
	Piezas board;
	ASSERT_TRUE(board.pieceAt(BOARD_ROWS, 0) == Invalid);
	ASSERT_TRUE(board.pieceAt(BOARD_ROWS + 2, 0) == Invalid);
}

TEST(PiezasTest, pieceAtBlankSameColumn) 
{
	Piezas board;
	board.dropPiece(1);
	board.dropPiece(1);
	// board at 0,1 and 1,1 filled
	ASSERT_TRUE(board.pieceAt(2,1) == Blank);
}

TEST(PiezasTest, pieceAtBlankDifferrentColumn) 
{
	Piezas board;
	board.dropPiece(1);
	board.dropPiece(1);
	// board at 0,1 and 1,1 filled
	ASSERT_TRUE(board.pieceAt(1,2) == Blank);
}

TEST(PiezasTest, pieceAtNoPlacement) 
{
	Piezas board;
	// board at 0,1 and 1,1 filled
	ASSERT_TRUE(board.pieceAt(1,2) == Blank);
}

TEST(PiezasTest, pieceAtOFilled) 
{
	Piezas board;
	board.dropPiece(1);
	board.dropPiece(1);
	ASSERT_TRUE(board.pieceAt(1,1) == O);
}

TEST(PiezasTest, pieceAtXFilled) 
{
	Piezas board;
	board.dropPiece(1);
	board.dropPiece(1);
	ASSERT_TRUE(board.pieceAt(1,0) == X);
}

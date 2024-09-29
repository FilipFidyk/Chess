#ifndef BOARD_H
#define BOARD_H

#define BOARD_VERTICES_NUMBER 4*4*64
#define BOARD_INDICES_NUMBER 3*2*64

#define WHITE_PAWN 1
#define WHITE_ROOK 2
#define WHITE_KNIGHT 3
#define WHITE_BISHOP 4
#define WHITE_QUEEN 5
#define WHITE_KING 6

#define BLACK_PAWN -1
#define BLACK_ROOK -2
#define BLACK_KNIGHT -3
#define BLACK_BISHOP -4
#define BLACK_QUEEN -5
#define BLACK_KING -6

float* createBoardVertices();
unsigned int* createBoardIndices();
int** initChessBoard();

#endif //BOARD_H
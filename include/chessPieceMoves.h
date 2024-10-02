#ifndef CHESS_PIECE_MOVES_H
#define CHESS_PIECE_MOVES_H

#define LEFT_EDGE 2
#define RIGHT_EDGE 9

void whitePawn(int **board, unsigned int xCoord, unsigned int yCoord);
void blackPawn(int **board, unsigned int xCoord, unsigned int yCoord);
void rook(int **board, unsigned int xCoord, unsigned int yCoord, int blackOrWhite);
void bishop(int **board, unsigned int xCoord, unsigned int yCoord, int blackOrWhite);
void knight(int **board, unsigned int xCoord, unsigned int yCoord, int blackOrWhite);
void queen(int **board, unsigned int xCoord, unsigned int yCoord, int blackOrWhite);
void king(int **board, unsigned int xCoord, unsigned int yCoord, int blackOrWhite);

#endif //CHESS_PIECE_MOVES_H
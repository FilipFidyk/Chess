#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H

#define PIECE_VERTICES_NUMBER 4*6*12
#define PIECE_INDICES_NUMBER 3*2*12

#define BLACK 0
#define WHITE 1

float* createPieceVertices(int **chessPieces);
unsigned int* createPieceIndices(int **chessPieces);
void FindPiece(int **board, int* coordDest, double xpos, double ypos);
int MovePiece(int **board, double nxpos, double nypos, int xCoord, int yCoord);
void cleanUpBoard(int **board);
unsigned int pixelToCoord(double val);

#endif //CHESS_PIECES_H

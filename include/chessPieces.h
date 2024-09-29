#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H

#define PIECE_VERTICES_NUMBER 4*6*12
#define PIECE_INDICES_NUMBER 3*2*12

float* createPieceVertices(int **chessPieces);
unsigned int* createPieceIndices(int **chessPieces);
void FindPiece(int **board, int* coordDest, double xpos, double ypos);
void MovePiece(int **board, double nxpos, double nypos, int xCoord, int yCoord);
void setAvailableMoves(int **board, unsigned int xCoord, unsigned int yCoord);
unsigned int pixelToCoord(double val);

#endif //CHESS_PIECES_H

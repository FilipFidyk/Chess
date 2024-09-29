#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H

#define PIECE_VERTICES_NUMBER 4*6*12
#define PIECE_INDICES_NUMBER 3*2*12

float* createPieceVertices(int **chessPieces);
unsigned int* createPieceIndices(int **chessPieces);
void FindPiece(int* coordDest, double xpos, double ypos);
void MovePiece(double nxpos, double nypos, int xCoord, int yCoord);
unsigned int pixelToCoord(double val);

#endif //CHESS_PIECES_H

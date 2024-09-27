#include <stdlib.h>
#include <stdio.h>
#include "chessPieces.h"

extern unsigned int firstClickCoords[2];
extern unsigned int **board;
extern unsigned int screenWidth;
extern unsigned int screenHeight;

//Create the 4 vertices per chess piece, each vertex has 5 attributes hence 4*5*pieces 
float* createPieceVertices(unsigned int **chessPieces)
{   
    float *pieceVertices = (float*)calloc(PIECE_VERTICES_NUMBER, sizeof(float));

    unsigned int vertexAttribute = 0;
    for (int i = 0; i<8;i++)
    {
        for (int j = 0; j<8; j++)
        {
            if (chessPieces[i][j])
            {
                //top left vertex
                pieceVertices[vertexAttribute++] = -1.0f + (j *  0.25f);
                pieceVertices[vertexAttribute++] =  1.0f + (i * -0.25f);
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 1.0f;

                //top right vertex
                pieceVertices[vertexAttribute++] = -1.0f + ((j+1) *  0.25f);
                pieceVertices[vertexAttribute++] =  1.0f + (i * -0.25f);
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 1.0f;
                pieceVertices[vertexAttribute++] = 1.0f;

                //bottom right vertex
                pieceVertices[vertexAttribute++] = -1.0f + ((j+1) *  0.25f);
                pieceVertices[vertexAttribute++] =  1.0f + ((i+1) * -0.25f);
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 1.0f;
                pieceVertices[vertexAttribute++] = 0.0f;

                //bottom left vertex
                pieceVertices[vertexAttribute++] = -1.0f + (j *  0.25f);
                pieceVertices[vertexAttribute++] =  1.0f + ((i+1) * -0.25f);
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 0.0f;
            }
        }
    }

    for (int i = 0; i <20; i+=5 )
        printf("%f %f %f %f %f\n", pieceVertices[i+0], pieceVertices[i+1], pieceVertices[i+2], pieceVertices[i+3], pieceVertices[i+4]);
    return pieceVertices;
}

//Create the indicesfor the pieces, 2 triangles per piece, 3 points per triangle, hence 3*2*pieces
/*
Chesspiece vertices are generated around the piece in the order: topleft, topright, bottomright, bottomleft
To create the indices we also chesspiece location:
    Column coordinate means an offset of a multiple of 4
    row coordinate means an offset of a multiple of 32

    Then add a value 0,1,2 or 3 to match which corner we want
*/
unsigned int* createPieceIndices(unsigned int **chessPieces)
{
    unsigned int *pieceIndices = (unsigned int*)calloc(PIECE_INDICES_NUMBER, sizeof(unsigned int));
    unsigned int indicesIndex = 0;

    /*
    for (int i = 0; i<8;i++)
    {
        for (int j = 0; j<8; j++)
        {
            if (chessPieces[i][j])
            {
                //Top right triangle
                pieceIndices[indicesIndex++] = (32 * i) + (4 * j);
                pieceIndices[indicesIndex++] = (32 * i) + (4 * j) + 1;
                pieceIndices[indicesIndex++] = (32 * i) + (4 * j) + 2;

                //Bottom left triangle
                pieceIndices[indicesIndex++] = (32 * i) + (4 * j);
                pieceIndices[indicesIndex++] = (32 * i) + (4 * j) + 2;
                pieceIndices[indicesIndex++] = (32 * i) + (4 * j) + 3;
            }
        }
    }
    */

    pieceIndices[0] = 0;
    pieceIndices[1] = 1;
    pieceIndices[2] = 2;
    pieceIndices[3] = 0;
    pieceIndices[4] = 2;
    pieceIndices[5] = 3;

    if (indicesIndex > PIECE_INDICES_NUMBER)
    {
        printf("INDICES ADDED INCORRECTLY");
    }

    for (int i = 0; i <6; i+=3 )
        printf("%d %d %d\n", pieceIndices[i+0], pieceIndices[i+1], pieceIndices[i+2]);
   return pieceIndices;
}

void FindPiece(int* coordDest, double xpos, double ypos)
{
    unsigned int xCoord = pixelToCoord(xpos), yCoord = pixelToCoord(ypos);
    if (board[yCoord][xCoord])
    {
        coordDest[0] = xCoord;
        coordDest[1] = yCoord;
    }
    else{
        coordDest[0] = -1;
        coordDest[1] = -1;
    }
}

void MovePiece(double nxpos, double nypos, int xCoord, int yCoord)
{
    unsigned int nxCoord = pixelToCoord(nxpos), nyCoord = pixelToCoord(nypos);
    
    if (xCoord != nxCoord || yCoord != nyCoord)
    {
        board[nyCoord][nxCoord] = board[yCoord][xCoord];
        board[yCoord][xCoord] = 0;
    }

    for (int i = 0;i<8;i++)
        printf("%d %d %d %d %d %d %d %d\n", board[i][0], board[i][1], board[i][2], board[i][3], board[i][4], board[i][5], board[i][6], board[i][7]);
}

unsigned int pixelToCoord(double val)
{
    double coord = val / ((double)screenWidth / 8);
    if (coord >= 8)
    {
        coord = 7;
    }
    
    printf("%d\n", (unsigned int)coord);

    return (unsigned int)coord;
}
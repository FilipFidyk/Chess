#include <stdlib.h>
#include <stdio.h>
#include "chessPieces.h"

extern unsigned int **board;
extern unsigned int screenWidth;
extern unsigned int screenHeight;

/*
Create the 4 vertices per chess piece, each vertex has 5 attributes hence 4*5*pieces attributes
Chesspiece vertices are generated around the piece in the order: topleft, topright, bottomright, bottomleft
*/
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
    return pieceVertices;
}


/*
Create the indices for the pieces
To create the indices we also use chesspiece location:
    The column coordinate means an offset of a multiple of 4
    THe row    coordinate means an offset of a multiple of 32

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
   return pieceIndices;
}

//Checks if a chess piece exists where the user clicked
//If so it outputs the coordinates of the piece and if not outputs -1 as coords
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

//Checks if where the user clicked for the second time isn't the same as the first
//If so then nothing happens, if not then we move the piece in the 2D array
void MovePiece(double nxpos, double nypos, int xCoord, int yCoord)
{
    unsigned int nxCoord = pixelToCoord(nxpos), nyCoord = pixelToCoord(nypos);
    
    if (xCoord != nxCoord || yCoord != nyCoord)
    {
        board[nyCoord][nxCoord] = board[yCoord][xCoord];
        board[yCoord][xCoord] = 0;
    }
}

/*
Converts the pixels given by glfwGetCursorPos() to a coordinate that can be used in the 2D board array
Divides the pixel number by an eighth of the width or height depends on figuring the x or y 
coordinate respectively
Exception is if someone clicks perfectly on the edge of the screen we output 7
*/
unsigned int pixelToCoord(double val)
{
    double coord = val / ((double)screenWidth / 8);
    if (coord >= 8)
    {
        coord = 7;
    }

    return (unsigned int)coord;
}
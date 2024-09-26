#include <stdlib.h>
#include <stdio.h>
#include "chessPieces.h"

//Create the 4 vertices per chess piece, each vertex has 5 attributes hence 4*5*pieces 
float* createPieceVertices(unsigned int **chessPieces)
{   
    float *pieceVertices = (float*)calloc(4*5*1, sizeof(float));

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

//Create the indices for the pieces, 2 triangles per piece, 3 points per triangle, hence 3*2*pieces
/*
Chesspiece vertices are generated around the piece in the order: topleft, topright, bottomright, bottomleft
To create the indices we also chesspiece location:
    Column coordinate means an offset of a multiple of 4
    row coordinate means an offset of a multiple of 32

    Then add a value 0,1,2 or 3 to match which corner we want
*/
unsigned int* createPieceIndices(unsigned int **chessPieces)
{
    unsigned int *pieceIndices = (unsigned int*)calloc(3*2*1, sizeof(unsigned int));

    unsigned int indicesIndex = 0;

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

    if (indicesIndex > 3*2*1)
    {
        printf("INDICES ADDED INCORRECTLY");
    }
   return pieceIndices;
}
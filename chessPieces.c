#include <stdlib.h>
//#include <stdio.h>
//#include "chessPieces.h"

//Create the 4 vertices per chess piece, each vertex has 5 attributes hence 4*5*pieces 
float* createPieceVertices(unsigned int **chessPieces)
{
    float *pieceVertices = (float*)calloc(4*5*1, sizeof(float));

    unsigned int vertexAttribute = 0;
    for (int i = 0; i<8;i++)
    {
        for (int j = 0; j<8; j++)
        {
            if (chessPieces[i][j] == 1)
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
                pieceVertices[vertexAttribute++] = 1.0f;
            }
        }
    }
    return pieceVertices;
/*
    for (int i = 0; i < 20; i+=5)
    {
        printf ("%d %d %d %d %d\n",pieceVertices[i] ,pieceVertices[i+1] ,pieceVertices[i+2] ,pieceVertices[i+3] ,pieceVertices[i+4]);
    }*/
}

//Create the indices for the pieces, 2 triangles per piece, 3 points per triangle, hence 3*2*pieces
unsigned int* createPieceIndices(unsigned int **chessPieces)
{
    unsigned int *pieceIndices = (unsigned int*)calloc(3*2*1, sizeof(unsigned int));

    unsigned int indicesIndex = 0;

    /*for (int i = 0; i<8;i++)
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
    }*/

    pieceIndices[0] = 0;
    pieceIndices[1] = 1;
    pieceIndices[2] = 2;
    pieceIndices[3] = 0;
    pieceIndices[4] = 2;
    pieceIndices[5] = 3;
/*
    for (int i = 0; i < 6; i+=3)
    {
        printf ("%d %d %d\n",pieceIndices[i] ,pieceIndices[i+1] ,pieceIndices[i+2]);
    }*/

   return pieceIndices;
}
#include <stdlib.h>
#include <stdio.h>

/*
This function creates a lattice of vertices that forms 9 vertical and 9 horizontal lines.
Each vertex has 3 coordinates so the total num is 3*81
They're generated on the horizontal line then the next and so on
*/
float* createBoardVertices()
{
    float *vertices = (float*)calloc(3*81, sizeof(float));
    int vertexIndex = 0;
    
    //OpenGL screen does coordinates from -1.0,-1.0 (topleft) to 1.0,1.0 (bottom right)
    //So the coordinates are set at those limits and 0.25 intervals
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            vertices[vertexIndex++] = -1.0f + (x * 0.25f); // X position
            vertices[vertexIndex++] = 1.0f - (y * 0.25f); // Y position
            vertices[vertexIndex++] = 1.0f; // Z position
        }
    }

    //Quick check we didn't overfill the array, when vertexIndex is 3*81 it means the last modified index was (3*81)-1
    if (vertexIndex > 3*81)
    {
        printf("ERROR::BOARD VERTICES BUFFER OVERFLOW");
    }

    return vertices;
}

/*
Creates the indices that will be used to draw the coloured triangles that form squares on the board
Forms the topright triangle then the bottom left and skips to the next square which should be 2 vertices away
    Exceptions are vertices 17, 35 and 53 - row ends without a coloured square and the next one doesn't
    start with one
*/
unsigned int* createBoardIndices()
{
    //8 triangles per row, 8 columns so 64 triangles, each made of 3 vertices, hence 3*64 entries
    unsigned int *indices = (unsigned int*)calloc(3*64, sizeof(unsigned int));

    int trianglesFirstVertexIndex = 1;
    for (int i = 0; i < 3*64; i += 6)
    {
        if (trianglesFirstVertexIndex == 17 || trianglesFirstVertexIndex == 35 || trianglesFirstVertexIndex == 53)
        {
            trianglesFirstVertexIndex += 2;
        }
        indices[i] = trianglesFirstVertexIndex;
        indices[i+1] = trianglesFirstVertexIndex + 1;
        indices[i+2] = trianglesFirstVertexIndex + 10;
        indices[i+3] = trianglesFirstVertexIndex;
        indices[i+4] = trianglesFirstVertexIndex + 9;
        indices[i+5] = trianglesFirstVertexIndex + 10;
        trianglesFirstVertexIndex += 2;
    }

    //No need to check as the loop stops when i becomes 3*64, meaning the last changed index was the one before

    return indices;
}

//Creates the 2d array in the heap and ----TODO---- inserts all the pieces into it
unsigned int** initChessBoard()
{
    unsigned int **chessPieces;
    chessPieces = (unsigned int**)calloc(8, sizeof(unsigned int*));
    for (int i = 0; i < 8; i++)
    {
        chessPieces[i] = (unsigned int*)calloc(8, sizeof(unsigned int));
    }

    chessPieces[0][0] = 1;
    chessPieces[0][1] = 2;

    return chessPieces;
}
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "board.h"

/*
This function creates a corner vertices for square on the checkered board.
Each vertex has 3 coordinates and 1 colour attribute so the total num is 4*4*64
They're generated from top-left to bottom-right
*/
float* createBoardVertices(int **board)
{
    float *vertices = (float*)calloc(BOARD_VERTICES_NUMBER, sizeof(float));
    int vertexIndex = 0, colourSelectFlag = 1;
    
    //OpenGL screen does coordinates from -1.0,-1.0 (topleft) to 1.0,1.0 (bottom right)
    //So the coordinates are set at those limits and then offset by a multiple of 0.25
    for (int y = 0; y < 8; y++) {
        //The initialise colour is set in the shader but to choose the right one we have a flag that flips polarity
        colourSelectFlag *= -1;
        for (int x = 0; x < 8; x++) {

            //top left
            vertices[vertexIndex++] = -1.0f + (x * 0.25f);      // X position
            vertices[vertexIndex++] = 1.0f - (y * 0.25f);       // Y position
            vertices[vertexIndex++] = 1.0f;                     // Z position
            if(board[y][x] == 10)
            {
                vertices[vertexIndex++] = 2.0f;
            }
            else if (board[y][x] > 10 || board[y][x] < -10)
            {
                vertices[vertexIndex++] = 3.0f;
            }
            else 
            {
                vertices[vertexIndex++] = colourSelectFlag;         // Colour Selector
            }

            //top right
            vertices[vertexIndex++] = -1.0f + ((x+1) * 0.25f);  // X position
            vertices[vertexIndex++] = 1.0f - (y * 0.25f);       // Y position
            vertices[vertexIndex++] = 1.0f;                     // Z position
            if(board[y][x] == 10)
            {
                vertices[vertexIndex++] = 2.0f;
            }
            else if (board[y][x] > 10 || board[y][x] < -10)
            {
                vertices[vertexIndex++] = 3.0f;
            }
            else 
            {
                vertices[vertexIndex++] = colourSelectFlag;         // Colour Selector
            }

            //bottom right
            vertices[vertexIndex++] = -1.0f + ((x+1) * 0.25f);  // X position
            vertices[vertexIndex++] = 1.0f - ((y+1) * 0.25f);   // Y position
            vertices[vertexIndex++] = 1.0f;                     // Z position
            if(board[y][x] == 10)
            {
                vertices[vertexIndex++] = 2.0f;
            }
            else if (board[y][x] > 10 || board[y][x] < -10)
            {
                vertices[vertexIndex++] = 3.0f;
            }
            else 
            {
                vertices[vertexIndex++] = colourSelectFlag;         // Colour Selector
            }

            //bottom left
            vertices[vertexIndex++] = -1.0f + (x * 0.25f);      // X position
            vertices[vertexIndex++] = 1.0f - ((y+1) * 0.25f);   // Y position
            vertices[vertexIndex++] = 1.0f;                     // Z position
            if(board[y][x] == 10)
            {
                vertices[vertexIndex++] = 2.0f;
            }
            else if (board[y][x] > 10 || board[y][x] < -10)
            {
                vertices[vertexIndex++] = 3.0f;
            }
            else 
            {
                vertices[vertexIndex++] = colourSelectFlag;         // Colour Selector
            }

            colourSelectFlag *= -1;
        }
        
    }

    //Quick check we didn't overfill the array, when vertexIndex is 3*81 it means the last modified index was (3*81)-1
    if (vertexIndex > BOARD_VERTICES_NUMBER)
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
    //64 squares, 2 triangles each and 3 indices each, hence 2*3*64 entries
    unsigned int *boardIndices = (unsigned int*)calloc(BOARD_INDICES_NUMBER, sizeof(unsigned int));
    unsigned int vertexOffset=0;

    //Generated for every box, so an offset of a multiple of 4
    for (int i = 0; i < BOARD_INDICES_NUMBER; i += 6)
    {
            //Top right triangle
            boardIndices[i] = vertexOffset;
            boardIndices[i+1] = vertexOffset+1;
            boardIndices[i+2] = vertexOffset+2;

            //Bottom left triangle
            boardIndices[i+3] = vertexOffset;
            boardIndices[i+4] = vertexOffset+2;
            boardIndices[i+5] = vertexOffset+3;
            vertexOffset+=4;
    }
    
    //No need to check i as it finished at BOARD_INDICES_NUMBER so the last assignments are in range 
    return boardIndices;
}

//Creates the 2d array in the heap and ----TODO---- inserts all the pieces into it
int** initChessBoard()
{
    int **chessPieces;
    chessPieces = (int**)calloc(8, sizeof(int*));
    for (int i = 0; i < 8; i++)
    {
        chessPieces[i] = (int*)calloc(8, sizeof(int));
    }

    chessPieces[5][0] = WHITE_PAWN;
    chessPieces[7][1] = WHITE_ROOK;
    chessPieces[7][2] = WHITE_KNIGHT;
    chessPieces[7][3] = WHITE_BISHOP;
    chessPieces[7][4] = WHITE_QUEEN;
    chessPieces[7][5] = WHITE_KING;

    chessPieces[5][1] = BLACK_PAWN;
    chessPieces[0][1] = BLACK_ROOK;
    chessPieces[0][2] = BLACK_KNIGHT;
    chessPieces[0][3] = BLACK_BISHOP;
    chessPieces[0][4] = BLACK_QUEEN;
    chessPieces[0][5] = BLACK_KING;


    return chessPieces;
}
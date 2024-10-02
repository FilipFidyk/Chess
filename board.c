#include <stdlib.h>
#include <stdio.h>
#include "board.h"

/*
    This function creates corner vertices for the squares on the checkered board.
    Each vertex has 3 coordinates and 1 colour attribute so the total num is 4*4*64
    They're generated from top-left to bottom-right

    OpenGL screen does coordinates from (-1.0,-1.0) (topleft) to (1.0,1.0) (bottom right)
    so the coordinates are set at those limits and then offset by a multiple of 0.25
    
    Also a colour id is set depending on value in the board
    0 - The colour will be set to either cream (-1) or lilac (1) decided by a flag that flips between 1 and -1
*/
float* createBoardVertices(int **board)
{
    float *vertices = (float*)calloc(BOARD_VERTICES_NUMBER, sizeof(float));
    int vertexIndex = 0, colourSelectFlag = 1;
    
    for (int i = 2; i < 10; i++)
    {
        //The colour flag is flipped at the start of every iteration of both loops, double flip at the end of a row
        colourSelectFlag *= -1;
        for (int j = 2; j < 10; j++) 
        {    
            //Necessary offset as originally coords were multiplies but now coordinates of pieces are from (2,2) to (9,9)
            //instead of (0,0) to (7,7)
            int nj = j-2, ni = i-2;
            
            //---------------------------------------------------------------------------------------------------
            //top left
            vertices[vertexIndex++] = -1.0f + (nj * 0.25f);      // X position
            vertices[vertexIndex++] = 1.0f - (ni * 0.25f);       // Y position
            vertices[vertexIndex++] = 1.0f;                      // Z position
            if(board[i][j] == 10)                                //Colour Selector
            {
                vertices[vertexIndex++] = 2.0f;
            }
            else if (board[i][j] > 10 || board[i][j] < -10)
            {
                vertices[vertexIndex++] = 3.0f;
            }
            else 
            {
                vertices[vertexIndex++] = colourSelectFlag;
            }

            //---------------------------------------------------------------------------------------------------
            //top right
            vertices[vertexIndex++] = -1.0f + ((nj+1) * 0.25f);  // X position
            vertices[vertexIndex++] = 1.0f - (ni * 0.25f);       // Y position
            vertices[vertexIndex++] = 1.0f;                      // Z position
            if(board[i][j] == 10)                                //Colour Selector
            {
                vertices[vertexIndex++] = 2.0f;
            }
            else if (board[i][j] > 10 || board[i][j] < -10)
            {
                vertices[vertexIndex++] = 3.0f;
            }
            else 
            {
                vertices[vertexIndex++] = colourSelectFlag;
            }

            //---------------------------------------------------------------------------------------------------
            //bottom right
            vertices[vertexIndex++] = -1.0f + ((nj+1) * 0.25f);  // X position
            vertices[vertexIndex++] = 1.0f - ((ni+1) * 0.25f);   // Y position
            vertices[vertexIndex++] = 1.0f;                      // Z position
            if(board[i][j] == 10)                                //Colour Selector
            {
                vertices[vertexIndex++] = 2.0f;
            }
            else if (board[i][j] > 10 || board[i][j] < -10)
            {
                vertices[vertexIndex++] = 3.0f;
            }
            else 
            {
                vertices[vertexIndex++] = colourSelectFlag;
            }

            //---------------------------------------------------------------------------------------------------
            //bottom left
            vertices[vertexIndex++] = -1.0f + (nj * 0.25f);      // X position
            vertices[vertexIndex++] = 1.0f - ((ni+1) * 0.25f);   // Y position
            vertices[vertexIndex++] = 1.0f;                      // Z position
            if(board[i][j] == 10)                                //Colour Selector
            {
                vertices[vertexIndex++] = 2.0f;
            }
            else if (board[i][j] > 10 || board[i][j] < -10)
            {
                vertices[vertexIndex++] = 3.0f;
            }
            else 
            {
                vertices[vertexIndex++] = colourSelectFlag;
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
    Vertices are generated around a square 4*(squareNumber - 1) + 0 or 1 or 2 or 3 
    Always the same number of indices necessary and the vertices are in the same places we don't need any variation
*/
unsigned int* createBoardIndices()
{
    unsigned int *boardIndices = (unsigned int*)calloc(BOARD_INDICES_NUMBER, sizeof(unsigned int));
    unsigned int vertexOffset=0;

    //Generated for every box, so a vertex offset of a multiple of 4
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
    chessPieces = (int**)calloc(12, sizeof(int*));
    for (int i = 0; i < 12; i++)
    {
        chessPieces[i] = (int*)calloc(12, sizeof(int));
    }

    chessPieces[8][3] = WHITE_PAWN;
    chessPieces[9][3] = WHITE_ROOK;
    chessPieces[9][4] = WHITE_KNIGHT;
    chessPieces[9][5] = WHITE_BISHOP;
    chessPieces[9][6] = WHITE_QUEEN;
    chessPieces[9][7] = WHITE_KING;

    chessPieces[7][2] = BLACK_PAWN;
    chessPieces[2][3] = BLACK_ROOK;
    chessPieces[7][4] = BLACK_KNIGHT;
    chessPieces[2][5] = BLACK_BISHOP;
    chessPieces[2][6] = BLACK_QUEEN;
    chessPieces[2][7] = BLACK_KING;


    return chessPieces;
}
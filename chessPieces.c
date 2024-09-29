#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "chessPieces.h"
#include "board.h"

//extern int **board;
extern unsigned int screenWidth;
extern unsigned int screenHeight;
extern unsigned int takeNumber;

/*
Create the 4 vertices per chess piece, each vertex has 6 attributes hence 4*6*pieces attributes
Chesspiece vertices are generated around the piece in the order: topleft, topright, bottomright, bottomleft
*/
float* createPieceVertices(int **board)
{   
    float *pieceVertices = (float*)calloc(PIECE_VERTICES_NUMBER-(24*takeNumber), sizeof(float));

    unsigned int vertexAttribute = 0;
    for (int i = 2; i<10;i++)
    {
        for (int j = 2; j<10; j++)
        {
            int nj = j-2, ni = i-2;
            if (board[i][j])
            {
                //top left vertex
                pieceVertices[vertexAttribute++] = -1.0f + (nj *  0.25f);
                pieceVertices[vertexAttribute++] =  1.0f + (ni * -0.25f);
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 1.0f;
                if(board[i][j] >= 10)
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j] - 10.0f;
                }
                else if (board[i][j] < -10)
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j] + 10.0f;
                }
                else 
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j];     
                }

                //top right vertex
                pieceVertices[vertexAttribute++] = -1.0f + ((nj+1) *  0.25f);
                pieceVertices[vertexAttribute++] =  1.0f + (ni * -0.25f);
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 1.0f;
                pieceVertices[vertexAttribute++] = 1.0f;
                if(board[i][j] >= 10)
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j] - 10.0f;
                }
                else if (board[i][j] < -10)
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j] + 10.0f;
                }
                else 
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j];     
                }

                //bottom right vertex
                pieceVertices[vertexAttribute++] = -1.0f + ((nj+1) *  0.25f);
                pieceVertices[vertexAttribute++] =  1.0f + ((ni+1) * -0.25f);
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 1.0f;
                pieceVertices[vertexAttribute++] = 0.0f;
                if(board[i][j] >= 10)
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j] - 10.0f;
                }
                else if (board[i][j] < -10)
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j] + 10.0f;
                }
                else 
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j];     
                }

                //bottom left vertex
                pieceVertices[vertexAttribute++] = -1.0f + (nj *  0.25f);
                pieceVertices[vertexAttribute++] =  1.0f + ((ni+1) * -0.25f);
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 0.0f;
                pieceVertices[vertexAttribute++] = 0.0f;
                if(board[i][j] >= 10)
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j] - 10.0f;
                }
                else if (board[i][j] < -10)
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j] + 10.0f;
                }
                else 
                {
                    pieceVertices[vertexAttribute++] = (float)board[i][j];     
                }
            }
        }
    }

    return pieceVertices;
}


/*
Create the indices for the pieces
To create the indices we use chesspiece order:
    Everything textures is sorted at the vertex level
    Vertices are set at chesspiece location but that does mean that there is no pattern but instead there is an order
    Top most left most are created first and as the loops travel right then down the pieces are added
    If we follow that iteration we will obviously encounter the same pattern

    So generating correct indices is as simple as multiplying the location of the piece in that order by 4
    Then add a value 0,1,2 or 3 to match which corner we want
*/
unsigned int* createPieceIndices(int **chessPieces)
{
    unsigned int *pieceIndices = (unsigned int*)calloc(PIECE_INDICES_NUMBER-(6*takeNumber), sizeof(unsigned int));
    unsigned int indicesIndex = 0, pieceCounter = 0;


    for (int i = 2; i<10;i++)
    {
        for (int j = 2; j<10; j++)
        {
            if (chessPieces[i][j])
            {
                //Top right triangle
                pieceIndices[indicesIndex++] = (pieceCounter*4);
                pieceIndices[indicesIndex++] = (pieceCounter*4)+1;
                pieceIndices[indicesIndex++] = (pieceCounter*4)+2;

                //Bottom left triangle
                pieceIndices[indicesIndex++] = (pieceCounter*4);
                pieceIndices[indicesIndex++] = (pieceCounter*4)+2;
                pieceIndices[indicesIndex++] = (pieceCounter*4)+3;

                pieceCounter++;
            }
        }
    }

    if (indicesIndex > PIECE_INDICES_NUMBER)
    {
        printf("INDICES ADDED INCORRECTLY");
    }
   return pieceIndices;
}

//Checks if a chess piece exists where the user clicked
//If so it outputs the coordinates of the piece and if not outputs -1 as coords
void FindPiece(int **board, int* coordDest, double xpos, double ypos)
{
    unsigned int xCoord = pixelToCoord(xpos), yCoord = pixelToCoord(ypos);

    if (board[yCoord][xCoord])
    {
        coordDest[0] = xCoord;
        coordDest[1] = yCoord;

        /* Adjust the board to find available places*/
        setAvailableMoves(board, xCoord, yCoord);
        /* for (int i = 0;i<12;i++){
            printf("%d %d %d %d %d %d %d %d %d %d %d %d\n", board[i][0], board[i][1], board[i][2], board[i][3], board[i][4], board[i][5], board[i][6], board[i][7], board[i][8], board[i][9], board[i][10], board[i][11]);
        } */
    }
    else{
        coordDest[0] = -1;
        coordDest[1] = -1;
    }
}

//Checks if where the user clicked for the second time isn't the same as the first
//If so then nothing happens, if not then we move the piece in the 2D array
int MovePiece(int **board, double nxpos, double nypos, int xCoord, int yCoord)
{
    unsigned int nxCoord = pixelToCoord(nxpos), nyCoord = pixelToCoord(nypos);
    int flag = 0;
    
    if (xCoord != nxCoord || yCoord != nyCoord)
    {
        if (board[nyCoord][nxCoord] >= 10 || board[nyCoord][nxCoord] < -10)
        {
            flag = board[nyCoord][nxCoord]; 
            board[nyCoord][nxCoord] = board[yCoord][xCoord];
            board[yCoord][xCoord] = 0;
            cleanUpBoard(board);
            
            return (flag == 10) ? 1 : 2;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        cleanUpBoard(board);
        return 1;
    }
}

void cleanUpBoard(int **board)
{
    for (int i = 2; i < 10; i++)
    {
        for (int j = 2; j < 10; j++)
        {
            if (board[i][j] >= 10)
            {
                board[i][j] -= 10;
            }
            else if(board[i][j] < -10)
            {
                board[i][j] += 10;
            }
        }
    }
}


/*
Sets Legal Moves on the table 
    A free box that piece can move into is set as a box
    a legal take changes the value of the piece by a set amount, positive for white, negative for black

 */
void setAvailableMoves(int **board, unsigned int xCoord, unsigned int yCoord)
{
    switch (board[yCoord][xCoord])
    {
    case WHITE_PAWN:
        //SETTING LEGAL MOVES
        //If the square ahead is free set it to available and check the next one as well
        if (!board[yCoord-1][xCoord])
        {
            board[yCoord-1][xCoord] = FREE_BOX;
            
            //Check if it is the first move and if the second box is free
            if (yCoord == 6)
            {
                if (!board[yCoord-2][xCoord])
                {
                    board[yCoord-2][xCoord] = FREE_BOX;  
                } 
            }
        }

        //SETTING LEGAL TAKES
        //Edge case when the pawn is on the far right
        if (xCoord == 7)
        {
            if (board[yCoord-1][xCoord-1] < 0)
            {
                board[yCoord-1][xCoord-1] -= 10;
            }
        }
        //Edge case when the pawn is on the far left
        else if (xCoord == 0)
        {
            if (board[yCoord-1][xCoord+1] < 0)
            {
                board[yCoord-1][xCoord+1] -= 10;
            }
        }
        //Regular case of the pawn in the middle
        else
        {
            if (board[yCoord-1][xCoord-1] < 0)
            {
                board[yCoord-1][xCoord-1] -= 10;
            }

            if (board[yCoord-1][xCoord+1] < 0)
            {
                board[yCoord-1][xCoord+1] -= 10;
            }
        }
        break;
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
    double coord = (val / ((double)screenWidth / 8)) +2;
    if (coord >= 10.0)
    {
        coord = 9.0;
    }

    return (unsigned int)coord;
}
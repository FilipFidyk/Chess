#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "board.h"
#include "chessPieces.h"
#include "chessPieceMoves.h"

//Imported global variables
extern unsigned int screenWidth;
extern unsigned int screenHeight;
extern unsigned int takeNumber;

/*
    Chesspiece vertices are generated around the piece in the order: topleft, topright, bottomright, bottomleft
    Each vertex has 6 attributes:
     - X Coordinate 
     - Y Coordinate
     - Z Coordinate - in 2D treated as depth
     - Texture X Coordinate
     - Texture Y Coordinate
     - Texture ID



*/
float* createPieceVertices(int **board)
{   
    //Have to consider the number of takes when generating piece vertices
    float *pieceVertices = (float*)calloc(PIECE_VERTICES_NUMBER-(24*takeNumber), sizeof(float));

    unsigned int vertexAttribute = 0;
    for (int i = 2; i<10;i++)
    {
        for (int j = 2; j<10; j++)
        {
            //Offset due to visible board having coordinates (2,2) to (9,9)
            int nj = j-2, ni = i-2;

            //If there is a non-zero value at (j, i) in board generate piece vertices
            if (board[i][j])
            {
                //---------------------------------------------------------------------------
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

                //---------------------------------------------------------------------------
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

                //---------------------------------------------------------------------------
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

                //---------------------------------------------------------------------------
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
         - Everything textures is sorted at the vertex level
         - Vertices are set at chesspiece location but that does mean that there is no pattern but instead there is an order
         - Top most left most pieces are created first and as the loop travels (right then down) the pieces are added
         - If we follow that iteration we will obviously encounter the same pattern

    So generating correct indices is as simple as multiplying the location of the piece in that order by 4
    Then add a value 0,1,2 or 3 to match which corner we want
*/
unsigned int* createPieceIndices(int **chessPieces)
{
    //Have to consider the number of takes when generating piece indices
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

/*
    Checks if a chess piece exists where the user clicked
    If so it sets the global first click coordinates of the piece and if not sets them to (-1, -1)
    Also changes the board to set legal moves and takes
     - Legal move board location becomes 10
     - Legal take of a white piece increases the piece value by 10
     - Legal take of a black piece decreases the piece value by -10
*/
void FindPiece(int **board, int* coordDest, double xpos, double ypos)
{
    unsigned int xCoord = pixelToCoord(xpos), yCoord = pixelToCoord(ypos);

    if (board[yCoord][xCoord])
    {
        coordDest[0] = xCoord;
        coordDest[1] = yCoord;

        /* Adjust the board to find available places*/
        switch (board[yCoord][xCoord])
        {
        case WHITE_PAWN:
            whitePawn(board, xCoord, yCoord);
            break;
        case BLACK_PAWN:
            blackPawn(board, xCoord, yCoord);
            break;
        case WHITE_ROOK:
            rook(board, xCoord, yCoord, WHITE);
            break;
        case BLACK_ROOK:
            rook(board, xCoord, yCoord, BLACK);
            break;
        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            //knight(board, xCoord, yCoord);
            break;
        case WHITE_BISHOP:
        case BLACK_BISHOP:
            //bishop(board, xCoord, yCoord);
            break;
        case WHITE_QUEEN:
        case BLACK_QUEEN:
            //queen(board, xCoord, yCoord);
            break;
        case WHITE_KING:
        case BLACK_KING:
            //king(board, xCoord, yCoord);
            break;
        }
    }
    else{
        coordDest[0] = -1;
        coordDest[1] = -1;
    }
}

/*
    Checks if where the user clicked for the second time isn't the same as the first
    If so then nothing happens, if not then we move the piece in the 2D array. 
    Nested ifs as there are plenty of types of possible moves:
     - Piece is deselected - same square is clicked - return 1 and only clean the board
     - Legal move          - board location = 10    - return 1, execute move and clean the board
     - Legal take          - board location >= |10| - return 2, execute take and clean the board
     - Illegal move        - board location = 0     - return 0, don't do anything we want the board as it is

*/
int MovePiece(int **board, double nxpos, double nypos, int xCoord, int yCoord)
{
    unsigned int nxCoord = pixelToCoord(nxpos), nyCoord = pixelToCoord(nypos);
    int flag = 0;
    
    //Checks if different coordinates
    if (xCoord != nxCoord || yCoord != nyCoord)
    {
        //Check board location for a legal move/take
        if (board[nyCoord][nxCoord] >= 10 || board[nyCoord][nxCoord] < -10)
        {
            //Move the pieces accordingly
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

//Any values that are 10 or above in the visible board need to be reduced by a magnitude of 10 
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
#include <math.h>
#include <stdio.h>
#include "board.h"
#include "chessPieceMoves.h"

void whitePawn(int **board, unsigned int xCoord, unsigned int yCoord)
{
    //SETTING LEGAL MOVES
    //If the square ahead is free set it to available and check the next one as well
    if (!board[yCoord-1][xCoord])
    {
        board[yCoord-1][xCoord] = FREE_BOX;
        
        //Check if it is the first move and if the second box is free
        if (yCoord == 8)
        {
            if (!board[yCoord-2][xCoord])
            {
                board[yCoord-2][xCoord] = FREE_BOX;  
            } 
        }
    }

    //SETTING LEGAL TAKES
    //Due to 12x12 board behind the scenes we can check squares outside the visible board
    if (board[yCoord-1][xCoord-1] < 0)
    {
        board[yCoord-1][xCoord-1] -= 10;
    }

    if (board[yCoord-1][xCoord+1] < 0)
    {
        board[yCoord-1][xCoord+1] -= 10;
    }

}

void blackPawn(int **board, unsigned int xCoord, unsigned int yCoord)
{
    printf("4");
    //SETTING LEGAL MOVES
    //If the square ahead is free set it to available and check the next one as well
    if (!board[yCoord+1][xCoord])
    {
        board[yCoord+1][xCoord] = FREE_BOX;
        
        //Check if it is the first move and if the second box is free
        if (yCoord == 3)
        {
            if (!board[yCoord+2][xCoord])
            {
                board[yCoord+2][xCoord] = FREE_BOX;  
            } 
        }
    }

    //SETTING LEGAL TAKES
    //Due to 12x12 board behind the scenes we can check squares outside the visible board
    if (board[yCoord+1][xCoord-1] > 0)
    {
        board[yCoord+1][xCoord-1] += 10;
    }

    if (board[yCoord+1][xCoord+1] > 0)
    {
        board[yCoord+1][xCoord+1] += 10;
    }
}

void rook(int **board, unsigned int xCoord, unsigned int yCoord, int blackOrWhite)
{
    int counter = 1;
    int flag = 0;

    //East
    while (xCoord + counter < 10 && !flag)
    {
        if (board[yCoord][xCoord+counter] == 0)
        {
            board[yCoord][xCoord+counter] = FREE_BOX;
        }
        else if (board[yCoord][xCoord+counter] > 0)
        {
            if(!blackOrWhite)
            {
                board[yCoord][xCoord+counter] += 10;
            }
            flag++;
        }
        else if (board[yCoord][xCoord+counter] < 0)
        {
            if(blackOrWhite)
            {
                board[yCoord][xCoord+counter] -= 10;
            }
            flag++;
        }
        counter++;
    }

    counter = 1; flag = 0;
    while (xCoord - counter > 1 && !flag)
    {
        if (board[yCoord][xCoord-counter] == 0)
        {
            board[yCoord][xCoord-counter] = FREE_BOX;
        }
        else if (board[yCoord][xCoord-counter] > 0)
        {
            if(!blackOrWhite)
            {
                board[yCoord][xCoord-counter] += 10;
            }
            flag++;
        }
        else if (board[yCoord][xCoord-counter] < 0)
        {
            if(blackOrWhite)
            {
                board[yCoord][xCoord-counter] -= 10;
            }
            flag++;
        }
        counter++;
    }

    counter = 1; flag = 0;
    while (yCoord + counter < 10 && !flag)
    {
        if (board[yCoord+counter][xCoord] == 0)
        {
            board[yCoord+counter][xCoord] = FREE_BOX;
        }
        else if (board[yCoord+counter][xCoord] > 0)
        {
            if(!blackOrWhite)
            {
                board[yCoord+counter][xCoord] += 10;
            }
            flag++;
        }
        else if (board[yCoord+counter][xCoord] < 0)
        {
            if(blackOrWhite)
            {
                board[yCoord+counter][xCoord] -= 10;
            }
            flag++;
        }
        counter++;
    }

    counter = 1; flag = 0;
    while (yCoord - counter > 1 && !flag)
    {
        if (board[yCoord-counter][xCoord] == 0)
        {
            board[yCoord-counter][xCoord] = FREE_BOX;
        }
        else if (board[yCoord-counter][xCoord] > 0)
        {
            if(!blackOrWhite)
            {
                board[yCoord-counter][xCoord] += 10;
            }
            flag++;
        }
        else if (board[yCoord-counter][xCoord] < 0)
        {
            if(blackOrWhite)
            {
                board[yCoord-counter][xCoord] -= 10;
            }
            flag++;
        }
        counter++;
    }


    
}
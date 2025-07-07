#ifndef MOVE_GEN
#define MOVE_GEN
#include <Arduino.h>

int64_t generateKingMoves(const int8_t board[64], int8_t position)
{
   
    bool colour = board[position]>0; // true (1) = white, false (0) = black 
    
    static const int8_t directions[8][2] = 
    {
        {  1,  0 }, 
        {  1,  1 }, 
        {  0,  1 }, 
        { -1,  1 }, 
        { -1,  0 }, 
        { -1, -1 }, 
        {  0, -1 },
        {  1, -1 }  
    };
    int64_t moves = 0LL;

    for(auto* pos: directions)
    {
        int8_t row = position / 8;
        int8_t col = position % 8;
        
        row += pos[0];
        col += pos[1];

        int8_t pos1D = row*8 + col;

        Serial.print(row);
        Serial.print(" ");
        Serial.print(col);
        Serial.print(" ");
        Serial.print(pos1D);
        Serial.print("\n");
        
        // 2 checks here
        // 1. within bounds of the board
        // 2. checks if the space to move to is either empty OR the enemy colour
        if (row >= 0 && row <= 7 && col >= 0 && col <= 7 && (board[pos1D] == 0 || (board[pos1D] > 0) != colour))
        {            
            //bitwise or to update the move int64
            moves |= 1LL << pos1D;
        }
    }
    
    return moves;
}

int64_t generatePawnMoves(const int8_t board[64], int8_t position)
{
    int8_t row = position / 8;
    int8_t col = position % 8;
    bool colour = board[position]>0; // true (1) = white, false (0) = black 

    int8_t forward = colour ? -1 : 1;
    int8_t startRow = colour ? 6 : 1;

    int64_t moves = 0LL;

    int8_t nextPos1D = (row+forward)*8 + col;
    if (row >= 0 && row <= 7 && col >= 0 && col <= 7)
    {

        if(board[nextPos1D] == 0)
        {
            moves |= 1LL << nextPos1D;
            if (row == startRow)
            {
                int8_t nextPos1D = (row+(forward*2))*8 + col;
                if (row >= 0 && row <= 7 && col >= 0 && col <= 7 && board[nextPos1D] == 0)
                {
                    moves |= 1LL << nextPos1D;
                }
            }
        }
    }
    
    // check attacks
    nextPos1D = (row+forward)*8 + (col+1);
    if (row >= 0 && row <= 7 && col >= 0 && col <= 7 &&  (board[nextPos1D] > 0) != colour && board[nextPos1D] != 0)
    {
        moves |= 1LL << nextPos1D;
    }
    nextPos1D = (row+forward)*8 + (col-1);
    if (row >= 0 && row <= 7 && col >= 0 && col <= 7 && (board[nextPos1D] > 0) != colour && board[nextPos1D] != 0)
    {
        moves |= 1LL << nextPos1D;
    }
    return moves;
}





int64_t generateEnemyAttacks(const int8_t board[64], bool colour){
    
}

#endif
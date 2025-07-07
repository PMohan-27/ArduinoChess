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
        
        if (row >= 0 && row <= 7 && col >= 0 && col <= 7 && (board[pos1D] == 0 || (board[pos1D] >0) != colour))
        {            
            moves |= 1LL << pos1D;
        }
    }
    

    return moves;
}


#endif
#include <Arduino.h>
#include <FastLED.h>
#include <limits.h>

#include "moveGenerator.hpp"



int8_t board1D[BOARD_SIZE] = {
    r, n, b, q, k, b, n, r,   // 8th rank (top)
    p, p, p, p, p, p, p, p,   // 7th rank
    0, 0, 0, 0, q, 0, 0, 0,   // 6th rank
    0, 0, 0, 0, R, 0, 0, 0,   // 5th rank
    0, 0, K, 0, 0, 0, 0, 0,   // 4th rank
    0, 0, 0, 0, 0, 0, 0, 0,   // 3rd rank
    P, P, P, P, P, P, P, P,   // 2nd rank
    R, N, B, Q, 0, B, N, R    // 1st rank (bottom)
};

int64_t moves = 0LL;

void printLongLong(int64_t move);
void setup() 
{
  Serial.begin(9600);

  int8_t row = 3;
  int8_t col = 4;
  int8_t testpos = row*8 + col;
  moves = generateRookMoves(board1D,testpos);
  whiteKingPosition = (4*8) +2;
  Serial.print("\n");
  moves = moveLegalizer(board1D,testpos,moves);

  printLongLong(moves);
  Serial.print("\n");

  // Serial.println("\n");
  // moves = generateKingMoves(board1D,whiteKingPosition);
  // moves = generateKingMoves(board1D,blackKingPosition);

}
void loop() 
{

}


/*

00000000
00000000
10110101
00010000
11101111
00011000
00010000
00000000

*/
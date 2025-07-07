#define SUPPORT_LONGLONG
#include <Arduino.h>
#include <FastLED.h>
#include <limits.h>

#include "moveGenerator.hpp"

#define P 1
#define B 2
#define N 3
#define R 4
#define Q 5
#define K 6
#define p -1
#define b -2
#define n -3
#define r -4
#define q -5
#define k -6

int8_t board1D[64] = {
    r, n, b, q, k, b, n, r,   // 8th rank (top)
    p, p, p, p, p, p, p, p,   // 7th rank
    0, 0, 0, 0, 0, 0, 0, 0,   // 6th rank
    0, 0, 0, 0, 0, 0, 0, 0,   // 5th rank
    0, 0, 0, 0, 0, 0, 0, 0,   // 4th rank
    0, 0, 0, 0, 0, 0, 0, 0,   // 3rd rank
    P, P, P, P, P, P, P, P,   // 2nd rank
    R, N, B, Q, K, B, N, R    // 1st rank (bottom)
};

int64_t moves = 0LL;
uint8_t whiteKingPosition = 60;
uint8_t blackKingPosition = 4;

void setup() 
{
  Serial.begin(9600);

  moves = generateKingMoves(board1D,39);
  Serial.print("\n");
  for(int i = 0; i <=63; i++)
  {
    if (i%8 == 0)
    {
      Serial.print("\n");
    }
    Serial.print(int((moves >> i) & 1LL));
  }

  // Serial.println("\n");
  // moves = generateKingMoves(board1D,whiteKingPosition);
  // moves = generateKingMoves(board1D,blackKingPosition);

}
void loop() 
{

}
/*
00010100
00011100
00000000
00000000
00000000
00000000
00000000
00000000


00000000
00000000
00000000
00000000
00000000
00000000
00000011
10000010
*/
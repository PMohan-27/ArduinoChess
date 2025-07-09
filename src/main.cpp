#include <Arduino.h>
#include <FastLED.h>
#include <limits.h>

#include "moveGenerator.hpp"

constexpr int8_t P = 1;
constexpr int8_t B = 2;
constexpr int8_t N = 3;
constexpr int8_t R = 4;
constexpr int8_t Q = 5;
constexpr int8_t K = 6;

constexpr int8_t p = -1;
constexpr int8_t b = -2;
constexpr int8_t n = -3;
constexpr int8_t r = -4;
constexpr int8_t q = -5;
constexpr int8_t k = -6;

constexpr uint8_t WHITE_KING_START_POS = 60;  // e1
constexpr uint8_t BLACK_KING_START_POS = 4;   // e8



int8_t board1D[BOARD_SIZE] = {
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
uint8_t whiteKingPosition = WHITE_KING_START_POS;
uint8_t blackKingPosition = BLACK_KING_START_POS;
void printLongLong(int64_t move);
void setup() 
{
  Serial.begin(9600);

  int8_t row = 4;
  int8_t col = 1;
  int8_t testpos = row*8 + col;
  board1D[testpos] = n;
  moves = generateKnightMoves(board1D, testpos);
  Serial.print("\n");
  printLongLong(moves);

  // Serial.println("\n");
  // moves = generateKingMoves(board1D,whiteKingPosition);
  // moves = generateKingMoves(board1D,blackKingPosition);

}
void loop() 
{

}

void printLongLong(int64_t move){
for(int i = 0; i <=63; i++)
  {
    if (i%8 == 0)
    {
      Serial.print("\n");
    }
    Serial.print(int((moves >> i) & 1LL));
  }
}